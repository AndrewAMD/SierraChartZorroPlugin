#include "Engine.h"
namespace cro = std::chrono;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;
using error_code = boost::system::error_code;

zt_blocker::zt_blocker(
	std::function<void(const std::string&)> fp_err, 
	std::function<void(void)> fp_zt_print_errors,
	socket_config config)
	:
	err(fp_err),
	zt_print_errors(fp_zt_print_errors),
	ztio(),
	timeout(ztio),
	next_brokerprogress(ztio),
	stopped(false),
	is_good(false)
{
}

zt_blocker::~zt_blocker()
{
}

bool zt_blocker::block_is_good()
{
	ztio.run(); // io needs to run regardless, to drain all tasks.
	zt_print_errors();
	return (bool)is_good;
}

void zt_blocker::unblock(bool good)
{
	stopped = true;
	solicit = sol_Null;
	is_good = good;
	next_brokerprogress.expires_at(cro::steady_clock::now());
	timeout.expires_at(cro::steady_clock::now());
}

void zt_blocker::reset_for_expect()
{
	stopped = false;
	is_good = false;
	timeout_do();
	brokerprogress_do();
	ztio.restart();
}

void zt_blocker::brokerprogress_do()
{
	if (stopped) return;
	zt_print_errors();
	next_brokerprogress.expires_at(cro::steady_clock::now() + cro::milliseconds(10));
	next_brokerprogress.async_wait([&](const boost::system::error_code& ec) {
		brokerprogress_handler(ec); });
}
void zt_blocker::brokerprogress_handler(const boost::system::error_code& ec)
{
	if (stopped) return;
	auto ret = BrokerProgress(1);
	if (ec || (!ret)) 
	{ 
		stopped = true; 
		is_good = false;
		timeout.cancel();
		return; 
	}
	brokerprogress_do();
}

void zt_blocker::timeout_do()
{
	if (stopped) return;
	timeout.expires_at(cro::steady_clock::now() + cro::milliseconds(conf.timeout_ms));
	timeout.async_wait([&](const boost::system::error_code& ec) {
		timeout_handler(ec); });
}
void zt_blocker::timeout_handler(const boost::system::error_code& ec)
{
	if (stopped) return;
	if (ec)
	{
		stopped = true;
		is_good = false;
		next_brokerprogress.cancel();
		return;
	}
	timeout_do();
}


void zt_blocker::expect(enum_Solicit expect)
{
	solicit = expect;
	reset_for_expect();
}

void zt_blocker::expect(enum_Solicit expect, uint32_t id)
{
	solicit = expect;
	solicit_ID = id;
	reset_for_expect();
}
void zt_blocker::expect(enum_Solicit expect, std::string ClientOrderID)
{
	solicit = expect;
	solicit_OrderID = ClientOrderID;
	reset_for_expect();
}

