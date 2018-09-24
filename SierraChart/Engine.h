#pragma once
#ifndef ENGINE_H
#define ENGINE_H

// MACROS FOR HEADERS
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0600 // Windows Vista or newer


#include "use_future_helpers.hpp"
#include "boost/asio/ssl.hpp"
#include <atomic>
#include <deque>
#include "DTCProtocol.h"
#include "DTCTools.h"
#include "Inflator.h"
#include <Windows.h>
#include "zorro_include/trading.h"


// MACROS FOR PLUGIN
#define PLUGIN_VERSION 2

// buffer sizing
#define HISTORY_MAXIMUM_TICKS 20000	// Assuming 1 year of 1M ticks, round up to 400k.
#define READ_BUFFER_SIZE 4096

// timing settings
#define TIMEOUT_S 10			// seconds of inactivity from a socket until it is automatically closed.
#define BROKERPROGRESS_MS 10	// milliseconds between BrokerProgress() calls.
#define HEARTBEAT1_S 5			// main socket, heartbeat will be sent every five seconds
#define HEARTBEAT2_S 0			// historical data socket, zero for no heartbeats


// default network settings
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT1 "11099"
#define DEFAULT_PORT2 "11097"
#define DEFAULT_USERNAME "_"
#define DEFAULT_PASSWORD "_"
#define DEFAULT_ACCOUNT "Sim1"
#define DEFAULT_TLS_ENABLED true
#define DEFAULT_ZLIB_ENABLED false

// new BROKERCOMMANDS
#define SET_DIVIDEND_ADJ 140 // Input 1 to enable dividend adjusted history, 0 for no dividend adjustment
#define GET_DTCSECURITYDEF 69 
typedef struct DTCSECURITYDEF
{
	char Symbol[64];
	char Exchange[16];
	int SecurityType;					// See DTC SecurityTypeEnum
	char Description[64];
	float MinPriceIncrement;
	int PriceDisplayFormat;				// see DTC PriceDisplayFormatEnum
	float CurrencyValuePerIncrement;
	float FloatToIntPriceMultiplier;
	float IntToFloatPriceDivisor;
	char UnderlyingSymbol[32];
	bool UpdatesBidAskOnly;
	float StrikePrice;
	int PutOrCall;						// 0: unset, 1: call, 2: put
	unsigned int ShortInterest;
	unsigned int SecurityExpirationDate;
	float BuyRolloverInterest;
	float SellRolloverInterest;
	float EarningsPerShare;
	unsigned int SharesOutstanding;
	float IntToFloatQuantityDivisor;
	bool HasMarketDepthData;
	float DisplayPriceMultiplier;
	char ExchangeSymbol[64];
	float InitialMarginRequirement;
	float MaintenanceMarginRequirement;
	char Currency[8];
} DTCSECURITYDEF;

// BROKERCOMMAND setting definitions
#define PRICETYPE_ASKBID			1
#define PRICETYPE_TRADES			2
#define VOLTYPE_SESSION_NO_VOLUME	1
#define VOLTYPE_SESSION_VOLUME		-4	// Real trading volume for "this session". "This session" is emulated for historical. Starts from zero and counts up. Resets occasionally.
#define VOLTYPE_SESSION_NUMTRADES	-2	// Number of trades made for "this session".  Like above, but more useful for decentralized no-volume securities.
#define ORDERTYPE_FILLORKILL		0
#define ORDERTYPE_IMMEDIATEORCANCEL 1
#define ORDERTYPE_GOODTILLCANCELED  2

#define PATCH_BALANCE_EQUITY		(1<<0)
#define PATCH_TRADEPROFIT_OPEN		(1<<1)
#define PATCH_TRADEPROFIT_ALL		(1<<2)
#define PATCH_SERVERTIME			(1<<3)
#define PATCH_ROLLOVER_COMMISSION	(1<<4)

enum enum_status
{
	status_terminated = 0,
	status_satisfied = 1, // also use for reject messages
	status_unsatisfied = 2,
	status_error_msg = 3,
};

enum enum_Solicit
{
	sol_Null = 0,
	sol_EncodingResponse = 1,
	sol_LogonResponse = 2,
	sol_MarketDataSnapshot_SymbolID = 3,
	sol_MarketDepthSnapshot_SymbolID = 4,
	sol_OrderUpdate_RequestID = 5, // checking for all open orders
	sol_OrderUpdate_ClientOrderID = 6, // upon order submission
	sol_OrderUpdate_ServerOrderID = 7, // upon zorro follow-up
	sol_HistoricalOrderFillResponse_RequestID = 8,
	sol_PositionUpdate_RequestID = 9,
	sol_TradeAccountsResponse_RequestID = 10,
	sol_ExchangeListResponse_RequestID = 11,
	sol_SecurityDefinitionResponse_RequestID = 12,
	sol_AccountBalanceUpdate_RequestID = 13,
	sol_HistoricalPriceData_RequestID = 14,
	sol_SocketConnect = 99, // special case - attempting to open a TCP connection (and handshake, if applicable)
};

class zt_blocker
{
public:
	zt_blocker(std::function<void(const std::string&)> fp_err, std::function<void(void)> fp_zt_print_errors);
	~zt_blocker();
	bool block_is_good();
	void unblock(bool good);
private:
	void reset_for_expect();
public:
	void timeout_do();
	void timeout_handler(const boost::system::error_code& ec);
	void brokerprogress_do();
	void brokerprogress_handler(const boost::system::error_code& ec);
	void expect(enum_Solicit expect);
	void expect(enum_Solicit expect, uint32_t id);
	void expect(enum_Solicit expect, std::string solicit_ClientOrderID);
private:
	std::atomic<bool> stopped;
	std::atomic<bool> is_good;
	std::function<void(const std::string&)> err;
	std::function<void(void)> zt_print_errors;

	boost::asio::io_context ztio;
	boost::asio::steady_timer timeout;
	boost::asio::steady_timer next_brokerprogress;

public:
	// receiving variables 
	std::atomic<enum_Solicit> solicit;
	std::atomic<uint32_t> solicit_ID;
	std::string solicit_OrderID;

};

class Market
{
public:
	bool can_get(DTC::s_MarketDataSnapshot& snapshot, uint32_t SymbolID);

	void Snapshot(DTC::s_MarketDataSnapshot* snapshot);
	DTC::s_MarketDataSnapshot* get_snapshot(uint32_t SymbolID);
private:
	std::deque<DTC::s_MarketDataSnapshot> snapshots_;
};

class UnsatisfiedClosure
{
public:
	std::string ServerID;
	std::string DTCSymbol;  // not ZorroAsset because we already have the security definition
	int ZorroAmount; // not DTC qty (double) because int is preferred for checking matches
};

class per_trade_account
{
public:
	DTC::s_AccountBalanceUpdate balance;
	std::deque<DTC::s_OrderUpdate> orders_open;
	std::deque<DTC::s_HistoricalOrderFillResponse> orders_hist;
	std::deque<DTC::s_PositionUpdate> positions;
	std::deque<UnsatisfiedClosure> unsatisfied_closures;
};


class socket_config
{
public:
	uint8_t id = 0;
	std::string host = "";
	std::string port = "";
	std::string tradeaccount = "";
	bool ssl = true;
	bool zlib = false;
	unsigned int timeout_ms = 10000;
	unsigned int hb_interval_s = 5;
	DTC::s_LogonRequest logon_request;
};

class client
{
public:
	client(socket_config config); 
	~client();
	int zt_BrokerLogin(char* Accounts);
	int zt_BrokerAsset(char* ZorroAsset, double *pPrice, double *pSpread, double *pVolume, double *pPip, double *pPipCost, double *pLotAmount, double *pMarginCost, double *pRollLong, double *pRollShort);
	int zt_BrokerHistory2(DTC::s_SecurityDefinitionResponse* def, DATE tStart, DATE tEnd, int nTickMinutes, int nTicks, T6* ticks);
	int zt_BrokerAccount(char* Account, double *pBalance, double *pTradeVal, double *pMarginVal);
	int zt_BrokerBuy2(char* ZorroAsset, int Amount, double StopDist, double Limit, double *pPrice, int *pFill);
	int zt_BrokerTrade(int nTradeID, double *pOpen, double *pClose, double *pRoll, double *pProfit);
	double zt_get_position(char* ZorroAsset);
	std::atomic<bool> stopped;
	void stop();
	
private:
	bool can_connect(); // configuration must be set
	bool can_login();
	bool can_confirm_trade_account(char* Accounts);
	bool can_sync_account_balance();
	bool can_sync_orders_hist();
	bool can_sync_orders_open();
	bool can_sync_positions();
	bool is_historical();
	bool is_hist_integer();
	bool has_security_definitions();
	int can_get_history(DTC::s_SecurityDefinitionResponse* def, DATE tStart, DATE tEnd, int nTickMinutes, int nTicks, T6* pT6_ticks);

	// asynchronous ops
	template<typename T>
	void write_async(T s_message)
	{
		boost::asio::post(io, [s_message, this]() {
			if (conf.ssl) boost::asio::async_write(tls_socket, boost::asio::buffer((char*)&s_message, sizeof(s_message)), [](const boost::system::error_code& ec_ignored, size_t s) {});
			else boost::asio::async_write(reg_socket, boost::asio::buffer((char*)&s_message, sizeof(s_message)), [](const boost::system::error_code& ec_ignored, size_t s) {});
		});

	}
	void timeout_adjust();
	void timeout_do();
	void timeout_handler(const boost::system::error_code& ec);

	void read_do();
	void read_handler(const boost::system::error_code& ec, size_t sz);
	void heartbeat_do();
	void heartbeat_handler(const boost::system::error_code& ec);


	// read buffers
	std::vector<char> cv_from_socket;	 // New bytes received from socket, uncompressed or compressed
	std::vector<char> cv_queue_raw;		 // Buffer yet to be interpreted. May or may not be compressed.
	std::vector<char> cv_queue_inflated; // Buffer after zlib inflation.
	std::vector<char> scratch_buffer;    // a scratch buffer for zlib
	std::atomic<bool> inflate_mode;
	std::unique_ptr<Inflator> inf;

	socket_config conf;
	DTCTools::RequestIDList rid;
	DTCTools::SymbolIDList sid;


	// error message handling
	std::deque<std::string> errors;
public:
	void zt_print_errors();
private:
	void BackendError(const std::string& error_msg);
	void err(const std::string& error_msg);
	std::atomic<bool> errors_ready;

	// Asset and Exchange tracking
	void print_exchanges();
	void print_security_info(std::string Symbol);
	void print_underlying_symbols_for_exchange(std::string Exchange);
	void print_symbols_for_underlying(std::string Underlying);
	void assets_test_print();
	bool can_parse_future(std::string ZorroAsset, std::string& Underlying, int& Expiry_YYYYMMDD);
	bool can_parse_option(std::string ZorroAsset, std::string& Underlying, int& Expiry_YYYYMMDD, double& StrikePrice, char& P_or_C);
	bool check_existing(std::string ZorroAsset, std::string& Symbol, std::string& Exchange);
	bool check_server_stock(std::string ZorroAsset, std::string& Symbol, std::string& Exchange); // check for ZorroAsset == Symbol
	bool check_server_future(std::string ZorroAsset, std::string& Symbol, std::string& Exchange); // pure futures only
	bool check_server_option(std::string ZorroAsset, std::string& Symbol, std::string& Exchange); // options & futures options only
	DTC::s_SecurityDefinitionResponse* can_define_local(std::string& Symbol);
	DTC::s_SecurityDefinitionResponse* can_define_local_hist(std::string& Symbol);
	DTC::s_SecurityDefinitionResponse* can_define_server(std::string& Symbol);
	DTC::s_SecurityDefinitionResponse* can_define_server_hist(std::string& Symbol);
public:
	DTC::s_SecurityDefinitionResponse* can_define(char* ZorroAsset);
private:
	bool can_subscribe(DTC::s_SecurityDefinitionResponse* def);
	bool can_update(DTC::s_SecurityDefinitionResponse* def, double *pPrice, double *pSpread, double *pVolume, double *pPip, double *pPipCost, double *pLotAmount, double *pMarginCost, double *pRollLong, double *pRollShort);


	// Server response tracking
	DTC::s_LogonResponse server_settings;
	Market market;

	// moved to per_trade_account
	//DTC::s_AccountBalanceUpdate balance;
	//std::deque<DTC::s_OrderUpdate> orders_open;
	//std::deque<DTC::s_HistoricalOrderFillResponse> orders_hist;
	//std::deque<DTC::s_PositionUpdate> positions;
	std::map<std::string, per_trade_account> m_pta;
	std::string this_ta;

	std::deque<DTC::s_TradeAccountResponse> trade_accounts;
	std::deque<DTC::s_ExchangeListResponse> exchanges;
	std::deque<DTC::s_SecurityDefinitionResponse> security_definitions;
	std::deque<DTC::s_SecurityDefinitionResponse> security_definitions_latest;
	bool next_is_new;

	DTC::s_HistoricalPriceDataResponseHeader h_header;
	std::deque<DTC::s_HistoricalPriceDataRecordResponse> h_bars;
	std::deque<DTC::s_HistoricalPriceDataTickRecordResponse> h_ticks;


	// receive and handle all messages from server
	void receive(const std::vector<char>& m);

	// overloads for all possible message types

	// Authentication and connection monitoring
	void receive(DTC::s_LogonResponse* m);
	void receive(DTC::s_Heartbeat* m);
	void receive(DTC::s_Logoff* m);
	void receive(DTC::s_EncodingResponse* m);

	// Market data
	void receive(DTC::s_MarketDataReject* m);
	void receive(DTC::s_MarketDataSnapshot* m);
	void receive(DTC::s_MarketDataSnapshot_Int* m);

	void receive(DTC::s_MarketDataUpdateTrade* m);
	void receive(DTC::s_MarketDataUpdateTradeCompact* m);
	void receive(DTC::s_MarketDataUpdateTrade_Int* m);
	void receive(DTC::s_MarketDataUpdateLastTradeSnapshot* m);
	void receive(DTC::s_MarketDataUpdateTradeWithUnbundledIndicator* m);

	void receive(DTC::s_MarketDataUpdateBidAsk* m);
	void receive(DTC::s_MarketDataUpdateBidAskCompact* m);
	void receive(DTC::s_MarketDataUpdateBidAsk_Int* m);

	void receive(DTC::s_MarketDataUpdateSessionOpen* m);
	void receive(DTC::s_MarketDataUpdateSessionOpen_Int* m);
	void receive(DTC::s_MarketDataUpdateSessionHigh* m);
	void receive(DTC::s_MarketDataUpdateSessionHigh_Int* m);
	void receive(DTC::s_MarketDataUpdateSessionLow* m);
	void receive(DTC::s_MarketDataUpdateSessionLow_Int* m);
	void receive(DTC::s_MarketDataUpdateSessionVolume* m);
	void receive(DTC::s_MarketDataUpdateOpenInterest* m);
	void receive(DTC::s_MarketDataUpdateSessionSettlement* m);
	void receive(DTC::s_MarketDataUpdateSessionSettlement_Int* m);
	void receive(DTC::s_MarketDataUpdateSessionNumTrades* m);
	void receive(DTC::s_MarketDataUpdateTradingSessionDate* m);

	void receive(DTC::s_MarketDepthReject* m);
	void receive(DTC::s_MarketDepthSnapshotLevel* m);
	void receive(DTC::s_MarketDepthSnapshotLevel_Int* m);
	void receive(DTC::s_MarketDepthUpdateLevel* m);
	void receive(DTC::s_MarketDepthUpdateLevelCompact* m);
	void receive(DTC::s_MarketDepthUpdateLevel_Int* m);
	void receive(DTC::s_MarketDepthFullUpdate10* m);
	void receive(DTC::s_MarketDepthFullUpdate20* m);

	void receive(DTC::s_MarketDataFeedStatus* m);
	void receive(DTC::s_MarketDataFeedSymbolStatus* m);

	// Trading related
	void receive(DTC::s_OpenOrdersReject* m);
	void receive(DTC::s_OrderUpdate* m);

	void receive(DTC::s_HistoricalOrderFillsReject* m);
	void receive(DTC::s_HistoricalOrderFillResponse* m);

	void receive(DTC::s_CurrentPositionsReject* m);
	void receive(DTC::s_PositionUpdate* m);

	// Account list
	void receive(DTC::s_TradeAccountResponse* m);

	// Symbol discovery and security definitions
	void receive(DTC::s_ExchangeListResponse* m);
	void receive(DTC::s_SecurityDefinitionResponse* m);
	void receive(DTC::s_SecurityDefinitionReject* m);

	// Account balance
	void receive(DTC::s_AccountBalanceReject* m);
	void receive(DTC::s_AccountBalanceUpdate* m);

	// Logging
	void receive(DTC::s_UserMessage* m);
	void receive(DTC::s_GeneralLogMessage* m);

	// Historical price data
	void receive(DTC::s_HistoricalPriceDataResponseHeader* m);
	void receive(DTC::s_HistoricalPriceDataReject* m);
	void receive(DTC::s_HistoricalPriceDataRecordResponse* m);
	void receive(DTC::s_HistoricalPriceDataTickRecordResponse* m);
	void receive(DTC::s_HistoricalPriceDataRecordResponse_Int* m);
	void receive(DTC::s_HistoricalPriceDataTickRecordResponse_Int* m);
	void receive(DTC::s_HistoricalPriceDataResponseTrailer* m);

	// asio objects
	boost::asio::io_context io;
	boost::asio::ssl::context ctx;
	boost::asio::ip::tcp::socket reg_socket;
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket&> tls_socket;
	
	boost::asio::steady_timer timeout;
	boost::asio::steady_timer next_heartbeat;
	boost::asio::steady_timer ssl_shutdown_timer; // special case timer
	boost::asio::steady_timer io_keepalive;
	
	// separate asio stuff for zorro thread
	zt_blocker b;

	std::unique_ptr<std::thread> t;

	// This function only posts the input function to an asio context if it is in fact in the background thread.
	// If it posts, it will wait for the input function to return a future value.
	// But if it's already in the backend thread, it will simply run the function and return its output.
	// This serves three purposes:
	// 1) To prevent deadlocks.
	//		(i.e. posting from the backend thread and blocking for a future will cause a deadlock.)
	// 2) To force the background thread to access backend memory elements.
	// 3) The programmer does not need to memorize whether he is in the zorro or backend thread.
	template <typename FuncWithReturnNoArgs>
	auto maybe_post_return(FuncWithReturnNoArgs f)
	{
		if (zt_id == std::this_thread::get_id())
		{
			if (stopped) return f();
			auto fu = post_use_future(io, [&]() {
				return f();
			});
			auto ret = fu.get();
			zt_print_errors();
			return ret;
		}
		else
		{
			return f();
		}
	}
};

namespace parsing
{
	void parse(std::string input);
	std::string to_lowercase(const std::string& input);
}


//globals
extern std::unique_ptr<client> c;  //main client
extern int(__cdecl *BrokerError)(const char* txt);
extern int(__cdecl *BrokerProgress)(const int percent);
extern std::string user, pw, h, p1, p2, tradeaccount_main, tradeaccount_selected;
extern bool isLive;
extern bool zlib_enabled;
extern bool dividend_adjusted;
extern HWND hWindow;
extern int pricetype, voltype, ordertype, patch;
extern std::thread::id zt_id;
extern std::string uuid, symbol;// ordertext;
//extern double bc_limit;


// helper functions
void market_trigger();
bool can_calc_LotAmount(DTC::s_SecurityDefinitionResponse* def, double& LotAmount);


#endif // ENGINE_H