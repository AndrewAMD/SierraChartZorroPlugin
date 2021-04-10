#include "pch.h"
#include "framework.h"
#include "StrBufs.h"


#include "asio.hpp"
#include "Handle.h"
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include "SierraChart2.h"


#include <chrono>
namespace cro = std::chrono;
using clo = cro::steady_clock;


#include "client.h"

#include "banned.h" //must include last

namespace net = asio;            // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using asio::error_code;

//------------------------------------------------------------------------------

const char* const FeedNames[NUM_FEEDS] = { "M", "H" }; // shorthand for main & hist

void fail(t_feedid id, error_code ec, char const* what){
    zprintf("%s: %s: %s", FeedNames[id], what, ec.message().c_str());
}
void fail2(t_feedid id, char const* what) {
    zprintf("%s: %s", FeedNames[id], what);
}



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// https://www.boost.org/doc/libs/1_75_0/libs/beast/example/websocket/client/async/websocket_client_async.cpp
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




struct cl_instance : public std::enable_shared_from_this<cl_instance> {
    t_feedid id_;
    bool stopped;
    char inbuf[MAX_DTC_MESSAGE_SIZE];
    net::mutable_buffer buffer;
    net::io_context& ioc_;
    cro::steady_clock::time_point next_heartbeat;
    tcp::socket s;
    cl_instance(t_feedid id, net::io_context& ioc) :
        id_(id),
        ioc_(ioc),
        buffer{ &inbuf[0], sizeof(inbuf) },
        next_heartbeat(clo::now()+cro::seconds(HEARTBEAT_SECONDS)),
        stopped{ false },
        s{ ioc}//,
    {
    }
    ~cl_instance() {
        cl_shutdown(this->id_);
    }
};


net::io_context ioc;
std::shared_ptr<cl_instance> pS[NUM_FEEDS]; // 


t_fpUnblockContition ubc = NULL;
t_feedid ubc_nFeedId = 0;
int32_t ubc_nReqId = 0;
void* ubc_pAux = NULL;
bool g_isReal = false;



int32_t new_request_id() {
    static int32_t last_req_num = 0;
    last_req_num = max(1, last_req_num + 1);
    return last_req_num;
}
uint32_t new_symbol_id() {
    static uint32_t last_req_num = 0;
    last_req_num = max(1, last_req_num + 1);
    return last_req_num;
}


void clear_ubc() {
    ubc = NULL;
    ubc_nFeedId = 0;
    ubc_nReqId = 0;
    ubc_pAux = NULL;
}

void readloop_do(std::shared_ptr<cl_instance> self);
void readloop_handler1(std::shared_ptr<cl_instance> self, const error_code& ec, std::size_t bytes_written);
void readloop_handler2(std::shared_ptr<cl_instance> self, const error_code& ec, std::size_t bytes_written);

void readloop_do(std::shared_ptr<cl_instance> self) {
    if (cl_is_stopped(self->id_)) return;
    self->buffer = asio::mutable_buffer(self->inbuf, sizeof(s_Header));
    asio::async_read(self->s, self->buffer, [self](const error_code& ec, std::size_t bytes_written1)->void {
        readloop_handler1(self, ec, bytes_written1); });
}
void readloop_handler1(std::shared_ptr<cl_instance> self, const error_code& ec, std::size_t bytes_written) {
    if (cl_is_stopped(self->id_)) return;
    if (ec) {
        cl_shutdown(self->id_);
        return fail(self->id_, ec, "readloop_handler1");
    }
    s_Header* pHdr = (s_Header*)self->inbuf;
    auto len = pHdr->Size;
    if (len > MAX_DTC_MESSAGE_SIZE || len < sizeof(s_Header)) {
        cl_shutdown(self->id_);
        return fail2(self->id_, strf("readloop_handler1: Bad DTC msg size: %d", len));
    }

    self->buffer = asio::mutable_buffer(&self->inbuf[sizeof(s_Header)], len - sizeof(s_Header));
    asio::async_read(self->s, self->buffer, [self](const error_code& ec, std::size_t bytes_written1)->void {
        readloop_handler2(self, ec, bytes_written1); });
}
void readloop_handler2(std::shared_ptr<cl_instance> self, const error_code& ec, std::size_t bytes_written) {
    if (cl_is_stopped(self->id_)) return;
    if (ec) {
        cl_shutdown(self->id_);
        return fail(self->id_, ec, "readloop_handler2");
    }
    s_Header* pHdr = (s_Header*)self->inbuf;
    std::size_t len = (std::size_t)pHdr->Size;
    if (len != (sizeof(s_Header)+bytes_written)) {
        cl_shutdown(self->id_);
        return fail2(self->id_, strf("readloop_handler2: Unexpected number of bytes received"));
    }
    handle_msg(self->id_, self->inbuf, pHdr->Type);
    if (ubc) {
        if (ubc(self->id_, self->inbuf, pHdr->Type, ubc_nReqId, ubc_pAux)) {
            clear_ubc();
        }
    }
    readloop_do(self);
}

void cl_check_heartbeat(t_feedid id) {
    if (cl_is_stopped(id)) return;
    auto self = pS[id];
    if (clo::now() > self->next_heartbeat) {
        self->next_heartbeat = clo::now() + cro::seconds(HEARTBEAT_SECONDS);
        s_Heartbeat hb;
        cl_send(id, &hb, hb.Size);
    }
}


void cl_drain() {
    try {

        if (!refresh()) return;
        if (cl_is_stopped(FEED_MAIN)) return;
        for (int i = 0; i < NUM_FEEDS; i++) { cl_check_heartbeat(i); }
        //drain any other incomplete tasks, nonblocking
        while (ioc.poll_one()) {
            if (cl_is_stopped(FEED_MAIN)) return;
        }
    }
    catch (std::exception const& e) {
        zprintf("cl_drain error: %s", e.what());
    }
}
void cl_block(t_fpUnblockContition fpUnblockContition, t_feedid id, int32_t nReqId, void* pAuxiliary) {
    try {
        if (cl_is_stopped(id)) return;
        set_timeout(NETWORK_TIMEOUT_MS);
        ubc = fpUnblockContition;
        ubc_nFeedId = id;
        ubc_nReqId = nReqId;
        ubc_pAux = pAuxiliary;

        //blocking
        while (ubc) {
            if (!refresh()) return;
            if (cl_is_stopped(id)) return;
            if (timed_out()) {
                zprintf("block timed out!");
                cl_shutdown(id);
                return;
            }
            ioc.run_one_for(cro::milliseconds(100));
        }
        cl_drain();
    }
    catch (std::exception const& e) {
        zprintf("cl_block error: %s", e.what());
    }
}


void cl_loiter() {
    try {
        if (cl_is_stopped(FEED_MAIN)) return;
        ioc.run_one_for(cro::milliseconds(100));
        cl_drain();
    } 
    catch (std::exception const& e) {
        zprintf("cl_loiter error: %s", e.what());
    }
}

void cl_wait_for(int ms) {
    clo::time_point time_to_return = clo::now() + cro::milliseconds(ms);
    while (clo::now() < time_to_return) {
        cl_loiter();
    }
}


void cl_connect(t_feedid id, const char* host, const char* port) {
    pS[id].reset();
    pS[id] = std::make_shared<cl_instance>(id,ioc);
    if (!pS[id]) {
        zprintf("shared_ptr failure!");
        cl_shutdown(id);
        return;
    }
    error_code ec;

    auto self = pS[id];

    // Look up the domain name    
    tcp::resolver resolver{self->ioc_};
    auto const results = resolver.resolve(host, port, ec);
    if (ec) {
        cl_shutdown(id);
        return fail(id, ec, "resolve");
    }

    // Make the connection on the IP address we get from a lookup
    auto ep = net::connect(self->s, results, ec);
    if (ec) {
        cl_shutdown(id);
        return  fail(id, ec, "connect");
    }

    //Launch the read loop
    readloop_do(self);
    cl_enable_asyncselect(id);
}


bool cl_is_stopped(t_feedid id) {
    if (!pS[id]) return true;
    return pS[id]->stopped;
}


void cl_reset_all() {
    try {
        for (int i = 0; i < NUM_FEEDS; i++) {
            cl_shutdown(i);
            pS[i].reset();
        }
        ioc.stop();
        ioc.restart();
        while (ioc.poll_one()) {};
    }
    catch (std::exception const& e) {
        zprintf("s_reset_all error: %s", e.what());
    }
}

void cl_shutdown(t_feedid id) {
    try {
        if (cl_is_stopped(id)) return;
        auto self = pS[id];
        self->stopped = true;
        error_code ec;

        // https://stackoverflow.com/questions/1993216/boostasio-cleanly-disconnecting
        // Gracefully shutdown socket
        while (ioc.poll_one()) {};// drain tasks
        pS[id]->s.shutdown(tcp::socket::shutdown_both,ec);
        if (ec) {
            //fail(id, ec, "shutdown rawsock"); //ignore error code
        }
        while (ioc.poll_one()) {};// drain tasks
        // Close the socket
        pS[id]->s.close(ec);
        if (ec) {
            //fail(id, ec, "close rawsock"); //ignore error code
        }
        while (ioc.poll_one()) {};// drain tasks
    }
    catch (std::exception const& e) {
        zprintf("s_shutdown error: %s", e.what());
    }
}


namespace cro = std::chrono;
typedef cro::steady_clock clo;
clo::time_point Deadline;
void set_timeout(int timeout_ms) {
    Deadline = clo::now() + cro::milliseconds(timeout_ms);
}
bool timed_out() {
    if (!refresh()) return true;
    if (clo::now() > Deadline) return true;
    return false;
}



void s_send_handler(std::shared_ptr<cl_instance> self, const error_code& ec, std::size_t bytes_transferred) {
    if (cl_is_stopped(self->id_)) return;
    if (ec) {
        cl_shutdown(self->id_);
        return fail(self->id_, ec, "send_handler");
    }
}

void cl_send(t_feedid id, void* pMsg, size_t len) {
    if (cl_is_stopped(id)) return;

    char* pOutBuf = (char*)strf("");
    memcpy_s(pOutBuf, LEN_STRBUF, pMsg, len);

    auto self = pS[id];
    asio::async_write(self->s, net::buffer(pOutBuf, len), [self](const error_code& ec, std::size_t bytes_transferred)->void {
        s_send_handler(self, ec, bytes_transferred); });
    //s_drain(); // we deliberately do not send immediately so that we can set up an unblock condition first.
}


HWND g_WindowsHandle = NULL;
void cl_set_hwnd(HWND handle) {
    g_WindowsHandle = handle;
    for (int id = 0; id < NUM_FEEDS; id++) {
        cl_enable_asyncselect(id);
    }
}
void cl_enable_asyncselect(t_feedid id) {
    if (cl_is_stopped(id)) return;
    if (!g_WindowsHandle) return;
    auto self = pS[id];
    SOCKET s = self->s.native_handle();
    if (!s) return;
    WSAAsyncSelect(s, g_WindowsHandle, WM_APP + 1, FD_READ | FD_CLOSE);
}

