#include "Engine.h"
#include <algorithm>

namespace asio = boost::asio;
namespace cro = std::chrono;
using boost::system::error_code;
using asio::ip::tcp;
#undef max

using namespace DTC;
using namespace DTCTools;

client::client(socket_config config) :
	b(
		[&](const std::string& error_msg) {err(error_msg); },
		[&]() {zt_print_errors(); },
		conf
	),
	conf(config),
	io(),
	ctx(asio::ssl::context::tlsv12_client),
	timeout(io),
	next_heartbeat(io),
	ssl_shutdown_timer(io),
	io_keepalive(io),
	reg_socket(io),
	tls_socket(reg_socket, ctx),
	stopped(false),
	errors_ready(false),
	inflate_mode(false)
{
	ctx.set_options(boost::asio::ssl::context::default_workarounds);
	tls_socket.set_verify_mode(asio::ssl::verify_none);

	err("#Launching thread...");
	t = std::make_unique<std::thread>(std::thread([&]() {
		ssl_shutdown_timer.expires_at(cro::steady_clock::now());
		io_keepalive.expires_at(cro::steady_clock::time_point::max());
		io_keepalive.async_wait([](const error_code ec_ignored) {});
		io.run();
	}));
}

client::~client()
{
	err("#Joining thread...");
	stop();
	std::this_thread::sleep_for(cro::milliseconds(200));
	io_keepalive.expires_at(cro::steady_clock::now());
	if (t->joinable()) t->join();
	t.reset();
}

int client::zt_BrokerLogin(char* Accounts)
{
	if (!can_connect()) { err("Connect failure."); return 0; }
	if (!can_login()) { err("Login failure."); return 0; }

	if (!can_confirm_trade_account(Accounts)) { err("Confirm tradeaccount failure."); return 0; }
	if (!can_sync_account_balance()) { err("Sync balance failure."); return 0; }
	if (!can_sync_orders_hist()) {err("Sync hist orders failure."); return 0; }
	if (!can_sync_orders_open()) { err("Sync open orders failure."); return 0; }
	if (!can_sync_positions()) { err("Sync positions failure."); return 0; }

	// These are just some tests to check if SC has implemented futures and options listing.
	// As of Jan 2019, futures implemented but not options.
	//print_exchanges();
	//print_symbols_for_underlying("F.US.EP", SECURITY_TYPE_FUTURES);
	//print_symbols_for_underlying("F.US.EDA", SECURITY_TYPE_FUTURES);
	//print_symbols_for_underlying("F.US.JY6", SECURITY_TYPE_FUTURES);
	//print_symbols_for_underlying("ES", SECURITY_TYPE_FUTURES);
	//print_symbols_for_underlying("DY", SECURITY_TYPE_FUTURES);
	//print_symbols_for_underlying("B6", SECURITY_TYPE_FUTURES);
	//print_symbols_for_underlying("J7", SECURITY_TYPE_FUTURES);




	return 1;
}

int client::zt_BrokerHistory2(DTC::s_SecurityDefinitionResponse* def, DATE tStart, DATE tEnd, int nTickMinutes, int nTicks, T6* ticks)
{
	if (!can_connect()) { err("Connect failure."); return 0; }
	if (!can_login()) { err("Login failure."); return 0; }

	if (!is_historical()) {
		err("Cannot get historical data from a non-historical socket.");
		stop(); return 0;
	}
	if (is_hist_integer())
	{
		err("Integer historical data not supported.");
		stop(); return 0;
	}

	return can_get_history(def, tStart, tEnd, nTickMinutes, nTicks, ticks);
}
bool client::is_historical()
{
	return maybe_post_return([&]()->bool {
		if (server_settings.GetHistoricalPriceDataSupported())
			return true;
		else return false;
	});
}
bool client::is_hist_integer()
{
	return maybe_post_return([&]()->bool {
		if (server_settings.GetUseIntegerPriceOrderMessages())
			return true;
		else return false;
	});
}

bool client::has_security_definitions()
{
	return maybe_post_return([&]()->bool {
		if (server_settings.GetSecurityDefinitionsSupported())
			return true;
		else return false;
	});
}

void emulate_session_volume(T6* pt6, const int& nEntries)
{
	// We will now emulate session volume.
	// From oldest to newest ticks, volume will increase from zero.
	// From a zorro script, bar volume is acquired by measuring changes in this value.
	// If the change is negative, this means you are reading a different "session".
	// But since it restarted at zero, assume that the given value is the bar's value.
	// Example:
	//	10000
	//	10100 change is 100, bar volume is 100
	//  10250 change is 150, bar volume is 150
	//    135 change is -10115.  We are reading a new session, bar volume is 135.
	//    200 change is  65, bar volume is  65
	// ... and so on.
	
	float lastvol = 0; 
	const float max = pow((float)10, (float)10); // arbitrary high float number, 10^10
	for (int i = (nEntries - 1); i >= 0; i--)
	{
		if (max < (lastvol + pt6[i].fVol)) // need a session volume reset
		{
			lastvol = 0;
		}
		pt6[i].fVol = (lastvol += pt6[i].fVol);
	}
}

//#include <fstream>      // std::ofstream
//void save_to_file(T6* pt6, const int& nEntries)
//{
//	static int i = 0;
//	std::string filename = ".\\test" + std::to_string(++i) + ".t6";
//	
//	std::ofstream ofs;
//	ofs.open(filename, std::ofstream::out | std::ofstream::app);
//
//	ofs.write((const char*)pt6, nEntries);
//
//	ofs.close();
//}

int client::can_get_history(DTC::s_SecurityDefinitionResponse* def, DATE tStart, DATE tEnd, 
	int nTickMinutes, int nTicks, T6* pt6)
{
	if (stopped) return 0;

	// we are logged in to historical server.
	s_HistoricalPriceDataRequest rq;
	int seconds_bar = 0;
	int max_days = 0;
	bool do_time_shift = false;
	switch (nTickMinutes)
	{
	case 0:
		rq.RecordInterval = INTERVAL_TICK;
		max_days = 7;
		// time = occurance of tick
		break;
	case 1:
		rq.RecordInterval = INTERVAL_1_MINUTE;
		max_days = 62;
		seconds_bar = 60; // zorro: 1M bar CLOSE, sierra: bar OPEN
		do_time_shift = true;
		break;
	case 1440:
		rq.RecordInterval = INTERVAL_1_DAY;
		max_days = 7000;
		seconds_bar = 1440 * 60;
		// zorro: daily bar OPEN, sierra: bar OPEN
		break;
	default:
		err("Error: Only tick and 1M historical data supported!");
		stop();
		return 0;
	}
	rq.StartDateTime = convertDate_1sec64bit(tStart);
	rq.EndDateTime = convertDate_1sec64bit(tEnd);
	rq.StartDateTime = std::max(rq.StartDateTime, rq.EndDateTime - (max_days * 24 * 60 * 60));
	rq.SetSymbol(def->GetSymbol());
	rq.SetExchange(def->GetExchange());
	
	if(conf.zlib) rq.UseZLibCompression = 1;
	else rq.UseZLibCompression = 0;
	if (dividend_adjusted)rq.RequestDividendAdjustedStockData = 1;
	else rq.RequestDividendAdjustedStockData = 0;
	rq.RequestID = rid.get_request_id(rq);
	b.expect(sol_HistoricalPriceData_RequestID, rq.RequestID);
	write_async(rq);
	if (!b.block_is_good())
	{
		stop(); return 0;
	}


	// Note: the DTC protocol necessarily delivers historical data
	//			from oldest to newest.
	// Thus, our approach:
	//		1) Read the input in the reverse order (.rbegin to .rend)
	//		2) If a tick is outside the date range, skip it.
	//		3) Output is from i=0 to (max - 1), direct to zorro T6 memory.

	return maybe_post_return([&]()->int {
		s_HistoricalPriceDataResponseHeader& hdr = h_header;
		if (hdr.GetNoRecordsToReturn()) { stop();  return 0; }
		else if (
			!hdr.GetRecordInterval() &&  // header indicates ticks
			(!server_settings.GetUseIntegerPriceOrderMessages()) && // prices are in double
			h_ticks.size() // The server indeed supplied ticks (NOT ALWAYS THE CASE!!!!)
			)
		{
			float value;
			auto dq_reit = h_ticks.rbegin();
			int i = 0; // T6 index
			for (; (dq_reit != h_ticks.rend()) && (i < HISTORY_MAXIMUM_TICKS); dq_reit++){
				auto vec_reit = dq_reit->rbegin();
				for (; (vec_reit != dq_reit->rend()) && (i < HISTORY_MAXIMUM_TICKS); vec_reit++) {
					// Here we skip invalid entries up front
					DATE t = convertTime(vec_reit->GetDateTime());
					if (t<tStart ||
						t>tEnd)
						continue;

					// we are cleared to make an entry
					value = (float)vec_reit->GetPrice();
					if (vec_reit->GetAtBidOrAsk() == AT_BID) value *= -1;
					pt6[i].time = t;
					pt6[i].fHigh = value;
					pt6[i].fLow = value;
					pt6[i].fOpen = value;
					pt6[i].fClose = value;
					pt6[i].fVal = 0; // not used
					if (voltype == VOLTYPE_SESSION_VOLUME)
						pt6[i].fVol = (float)vec_reit->GetVolume(); // real volume this tick (to be converted to session volume)
					else if (voltype == VOLTYPE_SESSION_NUMTRADES)
						pt6[i].fVol = (float)1; // tick volume this tick (to be converted to session tick frequency)
					else
						pt6[i].fVol = 0;


					// We only increment the T6 index if we are satisfied with our entry.
					i++;
				}
			}
			const int t6_qty = i;
			emulate_session_volume(pt6, t6_qty);
			return t6_qty;
		}
		else if (
			!hdr.GetRecordInterval() &&  // header indicates ticks
			(!server_settings.GetUseIntegerPriceOrderMessages()) && // prices are in double
			h_bars.size() // The server actually gave us bars instead!!!
			)
		{
			float value;
			auto dq_reit = h_bars.rbegin();
			int i = 0; // T6 index
			for (; (dq_reit != h_bars.rend()) && (i < HISTORY_MAXIMUM_TICKS); dq_reit++) {
				auto vec_reit = dq_reit->rbegin();
				for (; (vec_reit != dq_reit->rend()) && (i < HISTORY_MAXIMUM_TICKS); vec_reit++) {
					// Here we skip invalid entries up front
					DATE t = convertTime(vec_reit->GetStartDateTime());


					if (t<tStart ||
						t>tEnd)
						continue;

					// we are cleared to make an entry
					value = (float)vec_reit->GetLastPrice();
					if (!value) value = (float)vec_reit->GetOpenPrice();
					if (!value) continue; // nothing to do!!!
					// sanity check: is one volume being used and not the other?
					if(!vec_reit->GetAskVolume() && vec_reit->GetBidVolume()) // AT_BID
						value *= -1;
					pt6[i].time = t;
					pt6[i].fHigh = value;
					pt6[i].fLow = value;
					pt6[i].fOpen = value;
					pt6[i].fClose = value;
					pt6[i].fVal = 0; // not used
					if (voltype == VOLTYPE_SESSION_VOLUME)
						pt6[i].fVol = (float)vec_reit->GetVolume(); // real volume this tick (to be converted to session volume)
					else if (voltype == VOLTYPE_SESSION_NUMTRADES)
						pt6[i].fVol = (float)1; // tick volume this tick (to be converted to session tick frequency)
					else
						pt6[i].fVol = 0;

					// We only increment the T6 index if we are satisfied with our entry.
					i++;
				}
			}
			const int t6_qty = i;
			emulate_session_volume(pt6, t6_qty);
			return t6_qty;
		}
		else if (
			hdr.GetRecordInterval() &&  // header indicates bars
			(!server_settings.GetUseIntegerPriceOrderMessages()) // prices are in double
			)
		{
			auto dq_reit = h_bars.rbegin();
			int i = 0; // T6 index
			for (; (dq_reit != h_bars.rend()) && (i < HISTORY_MAXIMUM_TICKS); dq_reit++) {
				auto vec_reit = dq_reit->rbegin();
				for (; (vec_reit != dq_reit->rend()) && (i < HISTORY_MAXIMUM_TICKS); vec_reit++) {
					// Here we skip invalid entries up front
					// zorro: bar close, sierra: bar open
					int64_t dt = vec_reit->GetStartDateTime(); // dt is the moment the first tick is received in a bar. Unit: seconds
					dt /= seconds_bar; // now it's rounded down (minutes for 1M).  So we are at the beginning of the bar.
					dt *= seconds_bar; // back to seconds, beginning of the bar.
					if (do_time_shift) {
						dt += seconds_bar; // end of bar, per Zorro
					}
					DATE t = convertTime(dt);


					if (t<tStart ||
						t>tEnd)
						continue;

					pt6[i].time = t;
					pt6[i].fOpen = (float)vec_reit->GetOpenPrice();
					pt6[i].fHigh = (float)vec_reit->GetHighPrice();
					pt6[i].fLow = (float)vec_reit->GetLowPrice();
					pt6[i].fClose = (float)vec_reit->GetLastPrice();
					pt6[i].fVal = 0; //not used
					if (voltype == VOLTYPE_SESSION_VOLUME)
						pt6[i].fVol = (float)vec_reit->GetVolume(); // real volume this bar (to be converted to session volume)
					else if (voltype == VOLTYPE_SESSION_NUMTRADES)
						pt6[i].fVol = (float)vec_reit->GetNumTrades(); // tick volume this bar (to be converted to session tick frequency)
					else
						pt6[i].fVol = 0;

					// We only increment the T6 index if we are satisfied with our entry.
					i++;
				}
			}
			const int t6_qty = i;
			//save_to_file(pt6, t6_qty);
			emulate_session_volume(pt6, t6_qty);
			return t6_qty;
		}
		else
		{
			err("An unknown historical data type may have been received.");
			stop(); return 0;
		}
	});
}

int client::zt_BrokerAsset(char* ZorroAsset, double *pPrice, double *pSpread, double *pVolume, double *pPip, double *pPipCost, double *pLotAmount, double *pMarginCost, double *pRollLong, double *pRollShort)
{

	s_SecurityDefinitionResponse* def = can_define(ZorroAsset);
	if (!def) {
		err("Asset: " + (std::string)ZorroAsset + " not defined");
		return 0;
	}

	// subscribe if needed
	if (!pPrice)
	{
		err("Subscribing to Symbol " + (std::string)def->Symbol + "...");
		if (!can_subscribe(def))
		{
			err((std::string)def->Symbol + ": subscription failed.");
			return 0;
		}
		else // good
		{
			if (can_subscribe_market_depth(def)) err("Market depth subscribed");
			else err("No market depth");
			return 1;
		}
	}

	// otherwise output asset status
	else
	{
		if (!can_update(def, pPrice, pSpread, pVolume, pPip, pPipCost, pLotAmount, pMarginCost, pRollLong, pRollShort))
		{
			err("Cannot update info for Symbol " + (std::string)def->Symbol);
			return 0;
		}
		else // good
			return 1;
	}

}

int client::zt_BrokerAccount(char* Account, 
	double *pBalance, double *pTradeVal, double *pMarginVal)
{
	if (Account) tradeaccount_selected = Account;
	if (!tradeaccount_selected.size()) tradeaccount_selected = tradeaccount_main;

	return maybe_post_return([&]() ->int {
		per_trade_account& pta = m_pta.find(tradeaccount_selected)->second;
		s_AccountBalanceUpdate& a = pta.balance;

		if (
			!a.GetNoAccountBalances() &&	// not a simulated account
			!(patch & PATCH_BALANCE_EQUITY) // balance/equity override is not enabled
			)
		{

			if (pBalance)
				*pBalance = a.GetCashBalance();
			if (pTradeVal)
				*pTradeVal = a.GetSecuritiesValue() - a.GetCashBalance();
			if (pMarginVal)
				*pMarginVal = a.GetMarginRequirement();
		}
		return 1;
	});
}

bool client::can_connect()
{
	// our connection sequence is synchronous because asynchronous is completely unnecessary.

	tcp::resolver r(io);
	tcp::resolver::results_type endpoints = r.resolve(conf.host, conf.port);

	bool out = false;
	for (auto endpoint : endpoints)
	{
		{
			std::string str = "#Trying endpoint " + endpoint.host_name() + ":" + endpoint.service_name();
			if (conf.ssl) str += " (TLS 1.2)";
			else str += " (unencrypted)";
			err(str);
		}
		error_code ec;
		reg_socket.connect(endpoint, ec);
		if (reg_socket.is_open() && (!ec))
		{
			out = true;
			break;
		}
		else if (ec)
		{
			err(ec.message());
		}
		reg_socket.close(); // if there are multiple endpoints, need to close socket before trying next one.
	}
	if (!out)
	{
		stop();
		return false;
	}
	if (conf.ssl)
	{
		error_code ec;
		tls_socket.handshake(asio::ssl::stream_base::handshake_type::client, ec);
		if (ec)
		{
			err(ec.message());
			stop();
			return false;
		}
	}
	return true;
}

bool client::can_login()
{
	b.expect(sol_LogonResponse);
	write_async(conf.logon_request);
	timeout_do(); // launch async timeout
	read_do(); // launch async reader
	auto ret = b.block_is_good();

	if (!ret) return false;

	// logged in.
	heartbeat_do(); // launch heartbeats
	return true;
}

bool client::can_confirm_trade_account(char* Accounts)
{
	s_TradeAccountsRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	b.expect(sol_TradeAccountsResponse_RequestID, rq.RequestID);
	write_async(rq);
	if (!b.block_is_good())
	{
		err("Block error: confirm trade accounts");
		return 0;
	}

	// so far so good

	return maybe_post_return([&]() {
		bool match = false;

		std::deque<std::string> ta_list;

		// get list of trade accounts, move matching one to front
		for (auto it = trade_accounts.begin(); it != trade_accounts.end(); ++it)
		{
			std::string ta = it->GetTradeAccount();
			if (ta == "")
			{
				continue;
			}
			else if (ta == conf.tradeaccount)
			{
				match = true;
				ta_list.push_front(ta);
				this_ta = ta;
				m_pta[ta] = per_trade_account(); // map a blank pta entry.
			}
			else // not our tradeaccount
			{
				ta_list.push_back(ta);
				m_pta[ta] = per_trade_account(); // map a blank pta entry.
			}
		}


		// char* Accounts points to an array of 1024 elements
		// First, we will print the list of accounts using the below vector, using commas.
		// Then each comma will be converted to a null terminator. 
		// Finally, 1024 elmeents will be copied to Accounts.
		std::vector<char> str;
		str.reserve(1024);
		for (const auto& ta : ta_list)
		{
			if (str.size()) str.push_back(',');
			for (const auto& ch : ta)
			{
				str.push_back(ch);
			}
		}
		str.resize(1024, 0); // fill the rest with zeros

		if (ta_list.size())
		{
			err("TradeAccounts detected: " + ((std::string)str.data()));
		}
		else
		{
			err("No TradeAccounts detected");
		}

		if (match)
		{
			err("Using: " + conf.tradeaccount);
			for (auto& ch : str)
			{
				if (ch == ',') ch = '\0';
			}
			memcpy_s(Accounts, 1024, str.data(), str.size());
			return true;
		}
		else
		{
			err("No matching TradeAccounts found");
			return false;
		}

	});
}
bool client::can_sync_account_balance()
{
	s_AccountBalanceRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	b.expect(sol_AccountBalanceUpdate_RequestID, rq.RequestID);
	write_async(rq);
	if (!b.block_is_good())
	{
		err("Failed to confirm account balance.");
		return 0;
	}

	return maybe_post_return([&]() -> bool {
		per_trade_account& pta = m_pta.find(tradeaccount_main)->second;

		if (pta.balance.GetNoAccountBalances())
		{
			err("Warning: no balance for this account!");
			return true;
		}
		else if (((std::string)pta.balance.GetTradeAccount()) == conf.tradeaccount)
		{
			err("Balance synchronized.");
			return true;
		}
		else
		{
			err("Warning: no balance confirmed for this account!");
			return true;
		}
	});
	
}
bool client::can_sync_orders_hist()
{
	s_HistoricalOrderFillsRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	rq.NumberOfDays = 365; // Server: "NumberOfDays or StartDateTime fields must be non-zero."
	rq.SetTradeAccount(conf.tradeaccount.c_str());
	b.expect(sol_HistoricalOrderFillResponse_RequestID, rq.RequestID);
	write_async(rq);
	if (!b.block_is_good())
	{
		err("Failed to confirm historical orders");
		return 0;
	}
	return maybe_post_return([&]() -> bool {
		per_trade_account& pta = m_pta.find(tradeaccount_main)->second;

		int found = 0;
		for (auto a : pta.orders_hist)
		{
			std::string ta = a.GetTradeAccount();
			if (
				(ta == conf.tradeaccount) &&
				(a.GetRequestID() == rq.RequestID) &&
				!a.GetNoOrderFills()
				) found++;
		}
		err((std::to_string(found) + " historical orders detected.").c_str());
		return true;
	});
}
bool client::can_sync_orders_open()
{
	s_OpenOrdersRequest rq;
	rq.RequestAllOrders = 1;
	rq.SetTradeAccount(tradeaccount_main.c_str());
	rq.RequestID = rid.get_request_id(rq);
	b.expect(sol_OrderUpdate_RequestID, rq.RequestID);
	write_async(rq);
	if (!b.block_is_good())
	{
		err("Failed to confirm open orders");
		return 0;
	}

	return maybe_post_return ([&]() -> bool {
		per_trade_account& pta = m_pta.find(tradeaccount_main)->second;

		int found = 0;
		for (auto a : pta.orders_open)
		{
			std::string ta = a.GetTradeAccount();
			if (
				(ta == conf.tradeaccount) &&
				(a.GetRequestID() == rq.RequestID) &&
				((std::string)a.GetSymbol()).size()
				) found++;
		}
		err((std::to_string(found) + " open orders detected.").c_str());
		return true;
	});
}
bool client::can_sync_positions()
{
	s_CurrentPositionsRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	b.expect(sol_PositionUpdate_RequestID, rq.RequestID);
	write_async(rq);
	if (!b.block_is_good())
	{
		err("Failed to confirm open positions");
		return 0;
	}

	return maybe_post_return([&]()->bool {
		per_trade_account& pta = m_pta.find(tradeaccount_main)->second;

		int found = 0;
		for (auto a : pta.positions)
		{
			std::string ta = a.GetTradeAccount();
			if (
				(ta == conf.tradeaccount) &&
				(a.GetRequestID() == rq.RequestID) &&
				!a.GetNoPositions()
				) found++;
		}
		err((std::to_string(found) + " open positions detected.").c_str());
		return true;
	});
}


void client::timeout_adjust()
{
	if (stopped) return;
	timeout.expires_at(cro::steady_clock::now() + cro::milliseconds(conf.timeout_ms));
}


void client::timeout_do()
{
	if (stopped) return;
	timeout_adjust();
	timeout.async_wait([&](const boost::system::error_code& ec) {timeout_handler(ec); });
}

void client::timeout_handler(const boost::system::error_code& ec)
{
	if (stopped) return;

	// is now greater than timeout point? If so, stop.
	if (cro::steady_clock::now() > timeout.expiry())
	{
		std::ostringstream oss;
		oss << "Timed out.";
		err(oss.str());
		stop(); return;
	}

	// No problems detected.  Restart loop.
	timeout_do();
}

void client::read_do()
{
	if (stopped) return;

	// Elements are being moved from the front of this vector.
	// The remaining allocations are implementation-defined.
	if (cv_from_socket.size() < (READ_BUFFER_SIZE / 2))
		cv_from_socket.resize(READ_BUFFER_SIZE);
	//cv_from_socket.resize(1);


	//if (conf.ssl) asio::async_read(tls_socket, //_some
	if (conf.ssl) tls_socket.async_read_some( //_some
		asio::buffer(cv_from_socket.data(), cv_from_socket.size()),
		[&](const error_code& ec, size_t sz) {read_handler(ec, sz); });
	//else asio::async_read(reg_socket, //_some
	else reg_socket.async_read_some( //_some
		asio::buffer(cv_from_socket.data(), cv_from_socket.size()),
		[&](const error_code& ec, size_t sz) {read_handler(ec, sz); });

}

void client::read_handler(const error_code& ec, size_t sz)
{
	if (stopped) return;
	if (ec)
	{
		std::ostringstream oss;
		oss << "#Read error: " << ec.message(); // This is too verbose for historical connections
		err(oss.str());
		stop(); return;
	}
	if (!sz) read_do();
	timeout_adjust();

	// move elements to raw queue
	// ref: https://stackoverflow.com/questions/15004517/moving-elements-from-stdvector-to-another-one
	cv_queue_raw.insert(cv_queue_raw.end(),
		std::make_move_iterator(cv_from_socket.begin()),
		std::make_move_iterator(cv_from_socket.begin() + sz)
	);
	cv_from_socket.erase(cv_from_socket.begin(), cv_from_socket.begin() + sz);

	std::vector<char>* input = NULL;

	// read buffers until there is nothing left to read
	for (;;)
	{
		// do we need to inflate the raw buffer?
		if (inflate_mode) {
			input = &cv_queue_inflated;
			if (cv_queue_raw.size())
			{
				try {
					if (!inf)
						inf = std::make_unique<Inflator>();
					else if (inf->is_done()) {
						err("#resetting zlib");
						inf.reset();
						inf = std::make_unique<Inflator>();
					}
					inf->inf(cv_queue_raw, scratch_buffer);
					cv_queue_raw.clear();

					//move all elements from out to inflated queue
					auto it = std::next(scratch_buffer.begin(), scratch_buffer.size());
					std::move(scratch_buffer.begin(), it, std::back_inserter(cv_queue_inflated));  // ##
					scratch_buffer.erase(scratch_buffer.begin(), it);
				}
				catch (const std::runtime_error& rte)
				{
					err(rte.what());
					stop();
					return;
				}
			}
		}
		else input = &cv_queue_raw;

		if (input->size() < sizeof(s_Header)) break; // nothing to do.
		size_t msg_size = ((s_Header*)(input->data()))->Size;
		if (input->size() < msg_size) break; // nothing to do


		// move the message to its own char vector, and receive it.
		std::vector<char> msg;
		msg.insert(msg.end(),
			std::make_move_iterator(input->begin()),
			std::make_move_iterator(input->begin() + msg_size)
		);
		input->erase(input->begin(), input->begin() + msg_size);


		receive(msg);
	}

	read_do();

}

void client::heartbeat_do()
{
	if (stopped) return;
	if (!conf.hb_interval_s) return;

	next_heartbeat.expires_at(cro::steady_clock::now() + cro::seconds(conf.hb_interval_s));
	next_heartbeat.async_wait([&](const error_code& ec) {heartbeat_handler(ec); });
}

void client::heartbeat_handler(const error_code& ec)
{
	if (stopped) return;
	if (ec)
	{
		std::ostringstream oss;
		oss << "Heartbeat error: " << ec.message();
		err(oss.str());
		stop(); return;
	}

	s_Heartbeat hb;
	write_async(hb);

	heartbeat_do();
}

void client::stop()
{
	b.unblock(false);
	if (stopped) return;
	stopped = true;
	timeout.cancel();
	next_heartbeat.cancel();
	if (!conf.ssl) reg_socket.close();
	else
	{
		ssl_shutdown_timer.expires_at(cro::steady_clock::now() + cro::milliseconds(5));

		tls_socket.lowest_layer().cancel();
		tls_socket.async_shutdown([this](const error_code& ignored_ec) {});
		ssl_shutdown_timer.async_wait([&](const error_code& ignored_ec) {
			tls_socket.lowest_layer().close();
		});
	}
}

void client::zt_print_errors()
{
	if (zt_id != std::this_thread::get_id()) return; // safety check
	if (!errors_ready) return;

	std::deque<std::string> outs;
	auto fu = post_use_future(io, [&]() -> int {
		std::swap(outs, errors);
		errors_ready = false;
		return 0;
	});
	fu.get(); // block for post completion
	for (const auto& out : outs)
	{
		BrokerError(out.c_str());
	}
}

void client::BackendError(const std::string& error_msg)
{
	errors.push_back(error_msg);
	errors_ready = true;
}



void client::err(const std::string& error_msg)
{
	std::string msg;
	if (error_msg[0] == '#')
		msg = "#" + std::to_string((int)conf.id) + ": " + error_msg.substr(1);
	else
		msg = std::to_string((int)conf.id) + ": " + error_msg;
	if (zt_id == std::this_thread::get_id())
		BrokerError(msg.c_str());
	else
		BackendError(msg);
}
