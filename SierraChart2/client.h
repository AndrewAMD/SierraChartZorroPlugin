#pragma once

#include "UnblockConditions.h"


#define MAX_DTC_MESSAGE_SIZE 2048 //max known message size = 688

#define NUM_FEEDS   2

// Feed Identifiers (by socket interface)
#define FEED_MAIN  0  // Main socket.
#define FEED_HIST  1  // Historical socket
extern const char* const FeedNames[NUM_FEEDS];

typedef int t_feedid;


extern bool g_isReal;

void cl_reset_all();
void cl_connect(t_feedid id, const char* host, const char* port);
bool cl_is_stopped(t_feedid id);
void cl_shutdown(t_feedid id);
void cl_drain();
//void cl_send(t_feedid id, const char* pStr);

void cl_send(t_feedid id, void* pMsg, size_t len);

//template <typename T>
//inline void cl_send(t_feedid id, const T* pMsg) {
//	cl_send_rawdata(id, pMsg, sizeof(T));
//}


//t_ReqId cl_request(const char* sMethod, const char* sParams);
int32_t new_request_id();
uint32_t new_symbol_id();


void cl_block(t_fpUnblockContition fpUnblockContition, t_feedid id, int32_t nReqId, void* pAuxiliary);
void cl_loiter(); //up to 100ms of sleep while still listening for messages on the websocket
void cl_wait_for(int ms);



#define NETWORK_TIMEOUT_MS 600000  // 10 minutes
void set_timeout(int timeout_ms); // deadline is TIMEOUT_MS milliseconds from now
bool timed_out();
//t_ReqId new_request_id();

void clear_ubc();

#include <Windows.h>
void cl_set_hwnd(HWND handle);
void cl_enable_asyncselect(t_feedid id);

