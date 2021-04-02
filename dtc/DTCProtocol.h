
// Data and Trading Communications Protocol (DTC Protocol)

// This protocol is in the public domain and freely usable by anyone.

// Documentation: http://DTCprotocol.org/index.php?page=doc_DTCMessageDocumentation.php

// The uint8_t ordering is little endian. 

#pragma once

#include <cstdint>

using std::int16_t;   //   signed 16-bit integer
using std::int32_t;   //   signed 32-bit integer
using std::int64_t;   //   signed 64-bit integer
using std::uint16_t;  // unsigned 16-bit integer
using std::uint32_t;  // unsigned 32-bit integer
using std::uint64_t;  // unsigned 64-bit integer

typedef unsigned char uint8_t;


namespace DTC
{
// In general because these structures are placed into a stream of data 
// and the beginning position of the structure in the stream is variable 
// and not to any particular boundary, structure member alignment here is 
// not beneficial. So this could be changed to #pragma pack(1). It is 
// maintained at 8 since there is a reliance on that alignment for existing
// compiled code.
#pragma pack(push, 8)

	// DTC protocol version
	const int32_t CURRENT_VERSION = 8;

	// Text string lengths when using fixed length string binary encoding. 
	const int32_t USERNAME_PASSWORD_LENGTH = 32;
	const int32_t SYMBOL_EXCHANGE_DELIMITER_LENGTH = 4;
	const int32_t SYMBOL_LENGTH = 64;
	const int32_t EXCHANGE_LENGTH = 16;
	const int32_t UNDERLYING_SYMBOL_LENGTH = 32;
	const int32_t SYMBOL_DESCRIPTION_LENGTH = 64;
	const int32_t EXCHANGE_DESCRIPTION_LENGTH = 48;
	const int32_t ORDER_ID_LENGTH = 32;
	const int32_t TRADE_ACCOUNT_LENGTH = 32;
	const int32_t TEXT_DESCRIPTION_LENGTH = 96;
	const int32_t TEXT_MESSAGE_LENGTH = 256;
	const int32_t ORDER_FREE_FORM_TEXT_LENGTH = 48;
	const int32_t CLIENT_SERVER_NAME_LENGTH = 48;
	const int32_t GENERAL_IDENTIFIER_LENGTH = 64;
	const int32_t CURRENCY_CODE_LENGTH = 8;
	const int32_t ORDER_FILL_EXECUTION_LENGTH = 64;

	//----Message types----

	// Authentication and connection monitoring
	const uint16_t LOGON_REQUEST = 1;
	const uint16_t LOGON_RESPONSE = 2;
	const uint16_t HEARTBEAT = 3;
	const uint16_t LOGOFF = 5;
	const uint16_t ENCODING_REQUEST = 6;
	const uint16_t ENCODING_RESPONSE = 7;

	// Market data
	const uint16_t MARKET_DATA_REQUEST = 101;
	const uint16_t MARKET_DATA_REJECT = 103;
	const uint16_t MARKET_DATA_SNAPSHOT = 104;
	const uint16_t MARKET_DATA_SNAPSHOT_INT = 125;

	const uint16_t MARKET_DATA_UPDATE_TRADE = 107;
	const uint16_t MARKET_DATA_UPDATE_TRADE_COMPACT = 112;
	const uint16_t MARKET_DATA_UPDATE_TRADE_INT = 126;
	const uint16_t MARKET_DATA_UPDATE_LAST_TRADE_SNAPSHOT = 134;
	const uint16_t MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR = 137;
	const uint16_t MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR_2 = 146;
	const uint16_t MARKET_DATA_UPDATE_TRADE_NO_TIMESTAMP = 142;

	const uint16_t MARKET_DATA_UPDATE_BID_ASK = 108;
	const uint16_t MARKET_DATA_UPDATE_BID_ASK_COMPACT = 117;
	const uint16_t MARKET_DATA_UPDATE_BID_ASK_INT = 127;
	const uint16_t MARKET_DATA_UPDATE_BID_ASK_NO_TIMESTAMP = 143;
	const uint16_t MARKET_DATA_UPDATE_BID_ASK_FLOAT_WITH_MICROSECONDS = 144;

	const uint16_t MARKET_DATA_UPDATE_SESSION_OPEN = 120;
	const uint16_t MARKET_DATA_UPDATE_SESSION_OPEN_INT = 128;
	const uint16_t MARKET_DATA_UPDATE_SESSION_HIGH = 114;
	const uint16_t MARKET_DATA_UPDATE_SESSION_HIGH_INT = 129;
	const uint16_t MARKET_DATA_UPDATE_SESSION_LOW = 115;
	const uint16_t MARKET_DATA_UPDATE_SESSION_LOW_INT = 130;
	const uint16_t MARKET_DATA_UPDATE_SESSION_VOLUME = 113;
	const uint16_t MARKET_DATA_UPDATE_OPEN_INTEREST = 124;
	const uint16_t MARKET_DATA_UPDATE_SESSION_SETTLEMENT = 119;
	const uint16_t MARKET_DATA_UPDATE_SESSION_SETTLEMENT_INT = 131;
	const uint16_t MARKET_DATA_UPDATE_SESSION_NUM_TRADES = 135;
	const uint16_t MARKET_DATA_UPDATE_TRADING_SESSION_DATE = 136;

	const uint16_t MARKET_DEPTH_REQUEST = 102;
	const uint16_t MARKET_DEPTH_REJECT = 121;
	const uint16_t MARKET_DEPTH_SNAPSHOT_LEVEL = 122;
	const uint16_t MARKET_DEPTH_SNAPSHOT_LEVEL_INT = 132;
	const uint16_t MARKET_DEPTH_SNAPSHOT_LEVEL_FLOAT = 145;
	const uint16_t MARKET_DEPTH_UPDATE_LEVEL = 106;
	const uint16_t MARKET_DEPTH_UPDATE_LEVEL_FLOAT_WITH_MILLISECONDS = 140;
	const uint16_t MARKET_DEPTH_UPDATE_LEVEL_NO_TIMESTAMP = 141;
	const uint16_t MARKET_DEPTH_UPDATE_LEVEL_INT = 133;

	const uint16_t MARKET_DATA_FEED_STATUS = 100;
	const uint16_t MARKET_DATA_FEED_SYMBOL_STATUS = 116;
	const uint16_t TRADING_SYMBOL_STATUS = 138;

	const uint16_t MARKET_ORDERS_REQUEST = 150;
	const uint16_t MARKET_ORDERS_REJECT = 151;

	const uint16_t MARKET_ORDERS_ADD = 152;
	const uint16_t MARKET_ORDERS_MODIFY = 153;
	const uint16_t MARKET_ORDERS_REMOVE = 154;
	const uint16_t MARKET_ORDERS_SNAPSHOT_MESSAGE_BOUNDARY = 155;


	// Order entry and modification
	const uint16_t SUBMIT_NEW_SINGLE_ORDER = 208;
	const uint16_t SUBMIT_NEW_SINGLE_ORDER_INT = 206;

	const uint16_t SUBMIT_NEW_OCO_ORDER = 201;
	const uint16_t SUBMIT_NEW_OCO_ORDER_INT = 207;
	const uint16_t SUBMIT_FLATTEN_POSITION_ORDER = 209;

	const uint16_t CANCEL_ORDER = 203;

	const uint16_t CANCEL_REPLACE_ORDER = 204;
	const uint16_t CANCEL_REPLACE_ORDER_INT = 205;

	// Trading related
	const uint16_t OPEN_ORDERS_REQUEST = 300;
	const uint16_t OPEN_ORDERS_REJECT = 302;

	const uint16_t ORDER_UPDATE = 301;

	const uint16_t HISTORICAL_ORDER_FILLS_REQUEST = 303;
	const uint16_t HISTORICAL_ORDER_FILLS_REJECT = 308;
	const uint16_t HISTORICAL_ORDER_FILL_RESPONSE = 304;

	const uint16_t CURRENT_POSITIONS_REQUEST = 305;
	const uint16_t CURRENT_POSITIONS_REJECT = 307;
	const uint16_t POSITION_UPDATE = 306;
	const uint16_t ADD_CORRECTING_ORDER_FILL = 309;
	const uint16_t CORRECTING_ORDER_FILL_RESPONSE = 310;

	// Account list
	const uint16_t TRADE_ACCOUNTS_REQUEST = 400;
	const uint16_t TRADE_ACCOUNT_RESPONSE = 401;

	// Symbol discovery and security definitions
	const uint16_t EXCHANGE_LIST_REQUEST = 500;
	const uint16_t EXCHANGE_LIST_RESPONSE = 501;

	const uint16_t SYMBOLS_FOR_EXCHANGE_REQUEST = 502;
	const uint16_t UNDERLYING_SYMBOLS_FOR_EXCHANGE_REQUEST = 503;
	const uint16_t SYMBOLS_FOR_UNDERLYING_REQUEST = 504;
	const uint16_t SECURITY_DEFINITION_FOR_SYMBOL_REQUEST = 506;
	const uint16_t SECURITY_DEFINITION_RESPONSE = 507;

	const uint16_t SYMBOL_SEARCH_REQUEST = 508;

	const uint16_t SECURITY_DEFINITION_REJECT = 509;

	// Account Balance Data
	const uint16_t ACCOUNT_BALANCE_REQUEST = 601;
	const uint16_t ACCOUNT_BALANCE_REJECT = 602;	
	const uint16_t ACCOUNT_BALANCE_UPDATE = 600;
	const uint16_t ACCOUNT_BALANCE_ADJUSTMENT = 607;
	const uint16_t ACCOUNT_BALANCE_ADJUSTMENT_REJECT = 608;
	const uint16_t ACCOUNT_BALANCE_ADJUSTMENT_COMPLETE = 609;
	const uint16_t HISTORICAL_ACCOUNT_BALANCES_REQUEST = 603;
	const uint16_t HISTORICAL_ACCOUNT_BALANCES_REJECT = 604;
	const uint16_t HISTORICAL_ACCOUNT_BALANCE_RESPONSE = 606;

	// Logging
	const uint16_t USER_MESSAGE = 700;
	const uint16_t GENERAL_LOG_MESSAGE = 701;
	const uint16_t ALERT_MESSAGE = 702;

	const uint16_t JOURNAL_ENTRY_ADD = 703;
	const uint16_t JOURNAL_ENTRIES_REQUEST = 704;
	const uint16_t JOURNAL_ENTRIES_REJECT = 705;
	const uint16_t JOURNAL_ENTRY_RESPONSE = 706;
	
	// Historical price data
	const uint16_t HISTORICAL_PRICE_DATA_REQUEST = 800;
	const uint16_t HISTORICAL_PRICE_DATA_RESPONSE_HEADER = 801;
	const uint16_t HISTORICAL_PRICE_DATA_REJECT = 802;
	const uint16_t HISTORICAL_PRICE_DATA_RECORD_RESPONSE = 803;
	const uint16_t HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE = 804;
	const uint16_t HISTORICAL_PRICE_DATA_RECORD_RESPONSE_INT = 805;
	const uint16_t HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE_INT = 806;
	const uint16_t HISTORICAL_PRICE_DATA_RESPONSE_TRAILER = 807;

	// Historical market depth data
	const uint16_t HISTORICAL_MARKET_DEPTH_DATA_REQUEST = 900;
	const uint16_t HISTORICAL_MARKET_DEPTH_DATA_RESPONSE_HEADER = 901;
	const uint16_t HISTORICAL_MARKET_DEPTH_DATA_REJECT = 902;
	const uint16_t HISTORICAL_MARKET_DEPTH_DATA_RECORD_RESPONSE = 903;

	/*==========================================================================*/
	// Standard UNIX date-time value. In seconds.
	typedef int64_t t_DateTime;

	// This is a 32 bit UNIX date-time value used in messages where compactness is an important consideration. Or, where only the Date is needed. In seconds.
	typedef uint32_t t_DateTime4Byte;

	// UNIX date-time value with fractional portion for milliseconds.
	typedef double t_DateTimeWithMilliseconds;

	// Standard UNIX date-time value in milliseconds.
	typedef int64_t t_DateTimeWithMillisecondsInt;

	// Standard UNIX date-time value in microseconds.
	typedef int64_t t_DateTimeWithMicrosecondsInt;

	inline int64_t DateTimeWithMillisecondsToDateTimeWithMicrosecondsInt(const t_DateTimeWithMilliseconds DateTime)
	{
		return static_cast <int64_t>(DateTime * 1000000.0 + 0.5);
	}

	/*==========================================================================*/
	enum EncodingEnum : int32_t
	{ BINARY_ENCODING = 0
	, BINARY_WITH_VARIABLE_LENGTH_STRINGS = 1
	, JSON_ENCODING = 2
	, JSON_COMPACT_ENCODING = 3
	, PROTOCOL_BUFFERS = 4
	};

	inline const char* GetEncodingName(EncodingEnum Encoding)
	{
		switch (Encoding)
		{
			case BINARY_ENCODING:
			return "Binary";

			case BINARY_WITH_VARIABLE_LENGTH_STRINGS:
			return "Binary VLS";

			case JSON_ENCODING:
			return "JSON";

			case JSON_COMPACT_ENCODING:
			return "JSON Compact";

			case PROTOCOL_BUFFERS:
			return "Protocol Buffers";

			default:
			return "Unknown";
		}
	}

	/*==========================================================================*/
	enum LogonStatusEnum : int32_t
	{ LOGON_SUCCESS = 1
	, LOGON_ERROR = 2
	, LOGON_ERROR_NO_RECONNECT = 3
	, LOGON_RECONNECT_NEW_ADDRESS = 4
	};

	/*==========================================================================*/
	enum TradeModeEnum : int32_t
	{ TRADE_MODE_UNSET = 0
	, TRADE_MODE_DEMO = 1
	, TRADE_MODE_SIMULATED = 2
	, TRADE_MODE_LIVE = 3
	};

	/*==========================================================================*/
	enum RequestActionEnum : int32_t
	{ SUBSCRIBE = 1
	, UNSUBSCRIBE = 2
	, SNAPSHOT = 3
	, SNAPSHOT_WITH_INTERVAL_UPDATES = 4
	};

	/*==========================================================================*/
	enum UnbundledTradeIndicatorEnum : int8_t
	{ UNBUNDLED_TRADE_NONE = 0
	, FIRST_SUB_TRADE_OF_UNBUNDLED_TRADE = 1
	, LAST_SUB_TRADE_OF_UNBUNDLED_TRADE = 2
	};

	/*==========================================================================*/
	enum OrderStatusEnum : int32_t
	{ ORDER_STATUS_UNSPECIFIED = 0
	, ORDER_STATUS_ORDER_SENT = 1
	, ORDER_STATUS_PENDING_OPEN = 2
	, ORDER_STATUS_PENDING_CHILD = 3
	, ORDER_STATUS_OPEN = 4
	, ORDER_STATUS_PENDING_CANCEL_REPLACE = 5
	, ORDER_STATUS_PENDING_CANCEL = 6
	, ORDER_STATUS_FILLED = 7
	, ORDER_STATUS_CANCELED = 8
	, ORDER_STATUS_REJECTED = 9
	, ORDER_STATUS_PARTIALLY_FILLED = 10
	};

	/*==========================================================================*/
	enum OrderUpdateReasonEnum : int32_t
	{ ORDER_UPDATE_REASON_UNSET = 0
	, OPEN_ORDERS_REQUEST_RESPONSE = 1
	, NEW_ORDER_ACCEPTED = 2
	, GENERAL_ORDER_UPDATE = 3
	, ORDER_FILLED = 4
	, ORDER_FILLED_PARTIALLY = 5
	, ORDER_CANCELED = 6
	, ORDER_CANCEL_REPLACE_COMPLETE = 7
	, NEW_ORDER_REJECTED = 8
	, ORDER_CANCEL_REJECTED = 9
	, ORDER_CANCEL_REPLACE_REJECTED = 10
	};
	
	/*==========================================================================*/
	enum AtBidOrAskEnum8 : uint8_t
	{ BID_ASK_UNSET_8 = 0
	, AT_BID_8 = 1
	, AT_ASK_8 = 2
	};

	/*==========================================================================*/
	enum AtBidOrAskEnum : uint16_t
	{ BID_ASK_UNSET = 0
	, AT_BID = 1
	, AT_ASK = 2
	};

	/*==========================================================================*/
	enum MarketDepthUpdateTypeEnum : uint8_t
	{ MARKET_DEPTH_UNSET = 0
	, MARKET_DEPTH_INSERT_UPDATE_LEVEL = 1 // Insert or update depth at the given price level
	, MARKET_DEPTH_DELETE_LEVEL = 2 // Delete depth at the given price level
	};

	/*==========================================================================*/
	enum FinalUpdateInBatchEnum : uint8_t
	{
		FINAL_UPDATE_UNSET = 0
		, FINAL_UPDATE_TRUE = 1
		, FINAL_UPDATE_FALSE = 2
		, FINAL_UPDATE_BEGIN_BATCH = 3
	};

	/*==========================================================================*/
	enum MessageSetBoundaryEnum : uint8_t
	{
		MESSAGE_SET_BOUNDARY_UNSET = 0
		, MESSAGE_SET_BOUNDARY_BEGIN = 1
		, MESSAGE_SET_BOUNDARY_END = 2
	};
	
	/*==========================================================================*/
	enum OrderTypeEnum : int32_t
	{ ORDER_TYPE_UNSET = 0
	, ORDER_TYPE_MARKET = 1
	, ORDER_TYPE_LIMIT = 2
	, ORDER_TYPE_STOP = 3
	, ORDER_TYPE_STOP_LIMIT = 4
	, ORDER_TYPE_MARKET_IF_TOUCHED = 5
	, ORDER_TYPE_LIMIT_IF_TOUCHED = 6
	, ORDER_TYPE_MARKET_LIMIT = 7
	};
	
	/*==========================================================================*/
	enum TimeInForceEnum : int32_t
	{ TIF_UNSET = 0
	, TIF_DAY = 1
	, TIF_GOOD_TILL_CANCELED = 2
	, TIF_GOOD_TILL_DATE_TIME = 3
	, TIF_IMMEDIATE_OR_CANCEL = 4
	, TIF_ALL_OR_NONE = 5
	, TIF_FILL_OR_KILL = 6
	};
	
	/*==========================================================================*/
	enum BuySellEnum : int32_t
	{ BUY_SELL_UNSET = 0
	, BUY = 1
	, SELL = 2
	};

	/*==========================================================================*/
	enum OpenCloseTradeEnum : int32_t
	{ TRADE_UNSET = 0
	, TRADE_OPEN = 1
	, TRADE_CLOSE = 2
	};

	/*==========================================================================*/
	enum PartialFillHandlingEnum : int8_t
	{ PARTIAL_FILL_UNSET = 0
	, PARTIAL_FILL_HANDLING_REDUCE_QUANTITY = 1
	, PARTIAL_FILL_HANDLING_IMMEDIATE_CANCEL = 2
	};

	/*==========================================================================*/
	enum MarketDataFeedStatusEnum : int32_t
	{ MARKET_DATA_FEED_STATUS_UNSET = 0
	, MARKET_DATA_FEED_UNAVAILABLE = 1
	, MARKET_DATA_FEED_AVAILABLE = 2
	};

	/*==========================================================================*/
	enum TradingStatusEnum : int8_t
	{ TRADING_STATUS_UNKNOWN = 0
	, TRADING_STATUS_PRE_OPEN = 1
	, TRADING_STATUS_OPEN = 2
	, TRADING_STATUS_CLOSE = 3
	, TRADING_STATUS_TRADING_HALT = 4
	};

	inline const char* GetTradingStatusString(TradingStatusEnum TradingStatus)
	{
		switch (TradingStatus)
		{

		case TRADING_STATUS_PRE_OPEN:
			return "Pre-open";

		case TRADING_STATUS_OPEN:
			return "Open";

		case TRADING_STATUS_CLOSE:
			return "Closed";

		case TRADING_STATUS_TRADING_HALT:
			return "Trading Halt";

		case TRADING_STATUS_UNKNOWN:
		default:
			return "Unknown";
		}
	}


	/*==========================================================================*/
	enum PriceDisplayFormatEnum : int32_t
	{ PRICE_DISPLAY_FORMAT_UNSET =  -1
	//The following formats indicate the number of decimal places to be displayed
	, PRICE_DISPLAY_FORMAT_DECIMAL_0 = 0
	, PRICE_DISPLAY_FORMAT_DECIMAL_1 = 1
	, PRICE_DISPLAY_FORMAT_DECIMAL_2 = 2
	, PRICE_DISPLAY_FORMAT_DECIMAL_3 = 3
	, PRICE_DISPLAY_FORMAT_DECIMAL_4 = 4
	, PRICE_DISPLAY_FORMAT_DECIMAL_5 = 5
	, PRICE_DISPLAY_FORMAT_DECIMAL_6 = 6
	, PRICE_DISPLAY_FORMAT_DECIMAL_7 = 7
	, PRICE_DISPLAY_FORMAT_DECIMAL_8 = 8
	, PRICE_DISPLAY_FORMAT_DECIMAL_9 = 9
	//The following formats are fractional formats
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_256 = 356
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_128 = 228
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_64 = 164
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_32_EIGHTHS = 140
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_32_QUARTERS = 136
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_32_HALVES = 134
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_32 = 132 
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_16 = 116
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_8 = 108
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_4 = 104
	, PRICE_DISPLAY_FORMAT_DENOMINATOR_2 = 102
	};

	/*==========================================================================*/
	enum SecurityTypeEnum : int32_t
	{ SECURITY_TYPE_UNSET = 0
	, SECURITY_TYPE_FUTURES = 1
	, SECURITY_TYPE_STOCK = 2
	, SECURITY_TYPE_FOREX = 3 // CryptoCurrencies also go into this category
	, SECURITY_TYPE_INDEX = 4
	, SECURITY_TYPE_FUTURES_STRATEGY = 5
	, SECURITY_TYPE_FUTURES_OPTION = 7
	, SECURITY_TYPE_STOCK_OPTION = 6
	, SECURITY_TYPE_INDEX_OPTION = 8
	, SECURITY_TYPE_BOND = 9
	, SECURITY_TYPE_MUTUAL_FUND = 10
	};

	enum PutCallEnum : uint8_t
	{ PC_UNSET = 0
	, PC_CALL = 1
	, PC_PUT = 2
	};

	enum SearchTypeEnum : int32_t
	{ SEARCH_TYPE_UNSET = 0
	, SEARCH_TYPE_BY_SYMBOL = 1
	, SEARCH_TYPE_BY_DESCRIPTION = 2
	};
	
	/*==========================================================================*/
	enum HistoricalDataIntervalEnum : int32_t
	{ INTERVAL_TICK = 0
	, INTERVAL_1_SECOND = 1
	, INTERVAL_2_SECONDS = 2
	, INTERVAL_4_SECONDS = 4
	, INTERVAL_5_SECONDS = 5
	, INTERVAL_10_SECONDS = 10
	, INTERVAL_30_SECONDS = 30
	, INTERVAL_1_MINUTE = 60
	, INTERVAL_5_MINUTE = 300
	, INTERVAL_10_MINUTE = 600
	, INTERVAL_15_MINUTE = 900
	, INTERVAL_30_MINUTE = 1800
	, INTERVAL_1_HOUR = 3600
	, INTERVAL_2_HOURS = 7200
	, INTERVAL_1_DAY = 86400
	, INTERVAL_1_WEEK = 604800
	};

	enum HistoricalPriceDataRejectReasonCodeEnum : int16_t
	{ HPDR_UNSET = 0
	, HPDR_UNABLE_TO_SERVE_DATA_RETRY_IN_SPECIFIED_SECONDS = 1
	, HPDR_UNABLE_TO_SERVE_DATA_DO_NOT_RETRY = 2
	, HPDR_DATA_REQUEST_OUTSIDE_BOUNDS_OF_AVAILABLE_DATA = 3
	, HPDR_GENERAL_REJECT_ERROR = 4
	};

	/*==========================================================================*/
	enum TradeConditionEnum : int8_t
	{
		TRADE_CONDITION_NONE = 0
		, TRADE_CONDITION_NON_LAST_UPDATE_EQUITY_TRADE = 1
		, TRADE_CONDITION_ODD_LOT_EQUITY_TRADE = 2
	};

	/*==========================================================================*/
	struct s_EncodingRequest
	{
		uint16_t Size;
		uint16_t Type;
		int32_t ProtocolVersion;
		EncodingEnum Encoding;
		char ProtocolType[4];

		s_EncodingRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);		
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ENCODING_REQUEST;
			Size = sizeof(*this);

			ProtocolVersion = CURRENT_VERSION;
			Encoding = BINARY_ENCODING;
			SetProtocolType("DTC");
		}

		int32_t GetProtocolVersion() const;
		EncodingEnum GetEncoding() const;
		const char* GetProtocolType();
		void SetProtocolType(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_EncodingResponse
	{
		uint16_t Size;
		uint16_t Type;
		int32_t ProtocolVersion;
		EncodingEnum Encoding;

		char ProtocolType[4];

		s_EncodingResponse()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ENCODING_RESPONSE;
			Size = sizeof(*this);

			ProtocolVersion = CURRENT_VERSION;
			Encoding = BINARY_ENCODING;
			SetProtocolType("DTC");
		}

		int32_t GetProtocolVersion() const;
		EncodingEnum GetEncoding() const;
		const char* GetProtocolType();
		void SetProtocolType(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_LogonRequest
	{
		uint16_t Size;
		uint16_t Type;
		int32_t ProtocolVersion;
		char Username[USERNAME_PASSWORD_LENGTH];
		char Password[USERNAME_PASSWORD_LENGTH];
		char GeneralTextData[GENERAL_IDENTIFIER_LENGTH];
		int32_t Integer_1;
		int32_t Integer_2;
		int32_t  HeartbeatIntervalInSeconds; 
		TradeModeEnum TradeMode;
		char TradeAccount[TRADE_ACCOUNT_LENGTH]; 
		char HardwareIdentifier[GENERAL_IDENTIFIER_LENGTH];
		char ClientName[32];
		int32_t MarketDataTransmissionInterval;

		s_LogonRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = LOGON_REQUEST;
			Size = sizeof(*this);

			ProtocolVersion = CURRENT_VERSION;
		}

		int32_t GetProtocolVersion() const;
		const char* GetUsername();
		void SetUsername(const char* NewValue);
		const char* GetPassword();
		void SetPassword(const char* NewValue);
		const char* GetGeneralTextData();
		void SetGeneralTextData(const char* NewValue);
		int32_t GetInteger_1() const;
		int32_t GetInteger_2() const;
		int32_t GetHeartbeatIntervalInSeconds() const;
		TradeModeEnum GetTradeMode() const;
		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
		const char* GetHardwareIdentifier();
		void SetHardwareIdentifier(const char* NewValue);
		const char* GetClientName();
		void SetClientName(const char* NewValue);
		int32_t GetMarketDataTransmissionInterval() const;
	};

	/*==========================================================================*/
	struct s_LogonResponse
	{
		uint16_t Size;
		uint16_t Type;
		int32_t ProtocolVersion;
		LogonStatusEnum Result;
		char ResultText[TEXT_DESCRIPTION_LENGTH];
		char ReconnectAddress[64];
		int32_t Integer_1;
		char ServerName[60];
		uint8_t MarketDepthUpdatesBestBidAndAsk;
		uint8_t TradingIsSupported;
		uint8_t OCOOrdersSupported;
		uint8_t OrderCancelReplaceSupported;
		char SymbolExchangeDelimiter[SYMBOL_EXCHANGE_DELIMITER_LENGTH];
		uint8_t SecurityDefinitionsSupported;
		uint8_t HistoricalPriceDataSupported;
		uint8_t ResubscribeWhenMarketDataFeedAvailable;
		uint8_t MarketDepthIsSupported;
		uint8_t OneHistoricalPriceDataRequestPerConnection;
		uint8_t BracketOrdersSupported;
		uint8_t UseIntegerPriceOrderMessages;
		uint8_t UsesMultiplePositionsPerSymbolAndTradeAccount;
		uint8_t MarketDataSupported;

		s_LogonResponse()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = LOGON_RESPONSE;
			Size = sizeof(*this);

			ProtocolVersion = CURRENT_VERSION;
			OrderCancelReplaceSupported = 1;
			MarketDepthIsSupported = 1;
			MarketDataSupported = 1;
		}

		int32_t GetProtocolVersion() const;
		LogonStatusEnum GetResult() const;
		const char* GetResultText();
		void SetResultText(const char* NewValue);
		const char* GetReconnectAddress();
		void SetReconnectAddress(const char* NewValue);
		int32_t GetInteger_1() const;
		const char* GetServerName();
		void SetServerName(const char* NewValue);		
		uint8_t GetMarketDepthUpdatesBestBidAndAsk() const;
		uint8_t GetTradingIsSupported() const;
		uint8_t GetOCOOrdersSupported() const;
		uint8_t GetOrderCancelReplaceSupported() const;
		const char* GetSymbolExchangeDelimiter();
		void SetSymbolExchangeDelimiter(const char* NewValue);
		uint8_t GetSecurityDefinitionsSupported() const;
		uint8_t GetHistoricalPriceDataSupported() const;
		uint8_t GetResubscribeWhenMarketDataFeedAvailable() const;
		uint8_t GetMarketDepthIsSupported() const;
		uint8_t GetOneHistoricalPriceDataRequestPerConnection() const;
		uint8_t GetUseIntegerPriceOrderMessages() const;
		uint8_t GetBracketOrdersSupported() const;
		uint8_t GetUsesMultiplePositionsPerSymbolAndTradeAccount() const;
		uint8_t GetMarketDataSupported() const;
	};

	/*==========================================================================*/
	struct s_Logoff
	{
		uint16_t Size;
		uint16_t Type;
		char Reason[TEXT_DESCRIPTION_LENGTH];
		uint8_t DoNotReconnect;

		s_Logoff()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = LOGOFF;
			Size = sizeof(*this);
		}

		const char* GetReason();
		void SetReason(const char* NewValue);
		uint8_t GetDoNotReconnect() const;

	};

	/*==========================================================================*/
	struct s_Heartbeat
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t NumDroppedMessages;
		t_DateTime CurrentDateTime;

		s_Heartbeat()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HEARTBEAT;
			Size = sizeof(*this);
		}

		uint32_t GetNumDroppedMessages() const;
		t_DateTime GetCurrentDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketDataFeedStatus
	{
		uint16_t Size;
		uint16_t Type;
		MarketDataFeedStatusEnum Status;

		s_MarketDataFeedStatus()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_FEED_STATUS;
			Size = sizeof(*this);
		}

		MarketDataFeedStatusEnum GetStatus() const;
	};

	/*==========================================================================*/
	struct s_MarketDataFeedSymbolStatus
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		MarketDataFeedStatusEnum Status;

		s_MarketDataFeedSymbolStatus()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_FEED_SYMBOL_STATUS;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		MarketDataFeedStatusEnum GetStatus() const;
	};

	/*==========================================================================*/
	struct s_TradingSymbolStatus
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		TradingStatusEnum Status;

		s_TradingSymbolStatus()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = TRADING_SYMBOL_STATUS;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		TradingStatusEnum GetStatus() const;
	};

	/*==========================================================================*/
	struct s_MarketDataRequest
	{
		uint16_t Size;
		uint16_t Type;
		RequestActionEnum RequestAction;
		uint32_t SymbolID;
		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];
		uint32_t IntervalForSnapshotUpdatesInMilliseconds;

		s_MarketDataRequest()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_REQUEST;
			Size = sizeof(*this);

			RequestAction = SUBSCRIBE;
		}

		RequestActionEnum GetRequestAction() const;
		uint32_t GetSymbolID() const;
		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		uint32_t GetIntervalForSnapshotUpdatesInMilliseconds() const;
	};

	/*==========================================================================*/
	struct s_MarketDepthRequest
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_DEPTH_REQUEST;
		RequestActionEnum RequestAction = SUBSCRIBE;
		uint32_t SymbolID = 0;
		char Symbol[SYMBOL_LENGTH] = {0};
		char Exchange[EXCHANGE_LENGTH] = {0};
		int32_t NumLevels = 0;

		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);

		RequestActionEnum GetRequestAction() const;
		uint32_t GetSymbolID() const;
		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		int32_t GetNumLevels() const;
	};

	/*==========================================================================*/
	struct s_MarketDataReject
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_DATA_REJECT;
		uint32_t SymbolID = 0;
		char RejectText[TEXT_DESCRIPTION_LENGTH] = {0};
				
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);

		uint32_t GetSymbolID() const;
		const char* GetRejectText();
		void SetRejectText(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_MarketDataSnapshot
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		double SessionSettlementPrice;
		double SessionOpenPrice;
		double SessionHighPrice;
		double SessionLowPrice;
		double SessionVolume;
		uint32_t SessionNumTrades;
		uint32_t OpenInterest;

		double BidPrice;
		double AskPrice;
		double AskQuantity;
		double BidQuantity;
		double LastTradePrice;
		double LastTradeVolume;
		t_DateTimeWithMilliseconds LastTradeDateTime;
		t_DateTimeWithMilliseconds BidAskDateTime;
		t_DateTime4Byte SessionSettlementDateTime;
		t_DateTime4Byte TradingSessionDate;
		TradingStatusEnum TradingStatus;
		t_DateTimeWithMilliseconds MarketDepthUpdateDateTime;

		s_MarketDataSnapshot()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_SNAPSHOT;
			Size = sizeof(*this);

			SessionSettlementPrice = DBL_MAX;
			SessionOpenPrice = DBL_MAX;
			SessionHighPrice = DBL_MAX;
			SessionLowPrice = DBL_MAX;
			SessionVolume = DBL_MAX;
			SessionNumTrades = UINT_MAX;

			OpenInterest = UINT_MAX;

			BidPrice = DBL_MAX;
			AskPrice = DBL_MAX;
			AskQuantity = DBL_MAX;
			BidQuantity = DBL_MAX;

			LastTradePrice = DBL_MAX;
			LastTradeVolume = DBL_MAX;
		}

		uint32_t GetSymbolID() const;
		double GetSessionSettlementPrice() const;
		double GetSessionOpenPrice() const;
		double GetSessionHighPrice() const;
		double GetSessionLowPrice() const;
		double GetSessionVolume() const;
		uint32_t GetSessionNumTrades() const;
		uint32_t GetOpenInterest() const;
		double GetBidPrice() const;
		double GetAskPrice() const;
		double GetAskQuantity() const;
		double GetBidQuantity() const;
		double GetLastTradePrice() const;
		double GetLastTradeVolume() const;
		t_DateTimeWithMilliseconds GetLastTradeDateTime() const;
		t_DateTimeWithMilliseconds GetBidAskDateTime() const;
		t_DateTime4Byte GetSessionSettlementDateTime() const;
		t_DateTime4Byte GetTradingSessionDate() const;
		TradingStatusEnum GetTradingStatus() const;
		t_DateTimeWithMilliseconds GetMarketDepthUpdateDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketDataSnapshot_Int
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		int32_t SessionSettlementPrice;
		int32_t SessionOpenPrice;
		int32_t SessionHighPrice;
		int32_t SessionLowPrice;
		int32_t SessionVolume;
		uint32_t SessionNumTrades;
		uint32_t OpenInterest;

		int32_t BidPrice;
		int32_t AskPrice;
		int32_t AskQuantity;
		int32_t BidQuantity;
		int32_t LastTradePrice;
		int32_t LastTradeVolume;
		t_DateTimeWithMilliseconds LastTradeDateTime;
		t_DateTimeWithMilliseconds BidAskDateTime;
		t_DateTime4Byte SessionSettlementDateTime;
		t_DateTime4Byte TradingSessionDate;
		TradingStatusEnum TradingStatus;

		s_MarketDataSnapshot_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_SNAPSHOT_INT;
			Size = sizeof(*this);

			SessionSettlementPrice = INT_MAX;
			SessionOpenPrice = INT_MAX;
			SessionHighPrice = INT_MAX;
			SessionLowPrice = INT_MAX;
			SessionVolume = INT_MAX;
			SessionNumTrades = UINT_MAX;

			OpenInterest = UINT_MAX;

			BidPrice = INT_MAX;
			AskPrice = INT_MAX;
			AskQuantity = INT_MAX;
			BidQuantity = INT_MAX;

			LastTradePrice = INT_MAX;
			LastTradeVolume = INT_MAX;
		}

		uint32_t GetSymbolID() const;
		int32_t GetSessionSettlementPrice() const;
		int32_t GetSessionOpenPrice() const;
		int32_t GetSessionHighPrice() const;
		int32_t GetSessionLowPrice() const;
		int32_t GetSessionVolume() const;
		uint32_t GetSessionNumTrades() const;
		uint32_t GetOpenInterest() const;
		int32_t GetBidPrice() const;
		int32_t GetAskPrice() const;
		int32_t GetAskQuantity() const;
		int32_t GetBidQuantity() const;
		int32_t GetLastTradePrice() const;
		int32_t GetLastTradeVolume() const;
		t_DateTimeWithMilliseconds GetLastTradeDateTime() const;
		t_DateTimeWithMilliseconds GetBidAskDateTime() const;
		t_DateTime4Byte GetSessionSettlementDateTime() const;
		t_DateTime4Byte GetTradingSessionDate() const;
		TradingStatusEnum GetTradingStatus() const;
	};


	struct s_DepthEntry
	{
		double Price;
		float Quantity;
	};

	/*==========================================================================*/
	struct s_MarketDepthSnapshotLevel
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		AtBidOrAskEnum Side;
		double Price;
		double Quantity;
		uint16_t  Level;

		uint8_t IsFirstMessageInBatch;
		uint8_t IsLastMessageInBatch;

		t_DateTimeWithMilliseconds DateTime;

		uint32_t NumOrders;

		s_MarketDepthSnapshotLevel()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_SNAPSHOT_LEVEL;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		AtBidOrAskEnum GetSide() const;
		double GetPrice() const;
		double GetQuantity() const;
		uint16_t GetLevel() const;
		uint8_t GetIsFirstMessageInBatch() const;
		uint8_t GetIsLastMessageInBatch() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
		uint32_t GetNumOrders() const;
	};

#pragma pack(push, 1)
	/*==========================================================================*/
	struct s_MarketDepthSnapshotLevelFloat
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		float Price;
		float Quantity;
		uint32_t NumOrders;
		uint16_t Level;
		AtBidOrAskEnum8 Side;
		FinalUpdateInBatchEnum FinalUpdateInBatch;

		s_MarketDepthSnapshotLevelFloat()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_SNAPSHOT_LEVEL_FLOAT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		float GetPrice() const;
		float GetQuantity() const;
		uint32_t GetNumOrders() const;
		uint16_t GetLevel() const;
		AtBidOrAskEnum8 GetSide() const;
		FinalUpdateInBatchEnum GetFinalUpdateInBatch() const;
	};
#pragma pack(pop)

	/*==========================================================================*/
	struct s_MarketDepthSnapshotLevel_Int
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		AtBidOrAskEnum Side;
		int32_t Price;
		int32_t Quantity;
		uint16_t  Level;

		uint8_t IsFirstMessageInBatch;
		uint8_t IsLastMessageInBatch;

		t_DateTimeWithMilliseconds DateTime;

		uint32_t NumOrders;

		s_MarketDepthSnapshotLevel_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_SNAPSHOT_LEVEL_INT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		AtBidOrAskEnum GetSide() const;
		int32_t GetPrice() const;
		int32_t GetQuantity() const;
		uint16_t GetLevel() const;
		uint8_t GetIsFirstMessageInBatch() const;
		uint8_t GetIsLastMessageInBatch() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
		uint32_t GetNumOrders() const;
	};

	/*==========================================================================*/
	struct s_MarketDepthUpdateLevel
	{	 
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		AtBidOrAskEnum Side;
		double Price;
		double Quantity;
		MarketDepthUpdateTypeEnum UpdateType;
		t_DateTimeWithMilliseconds DateTime;
		uint32_t NumOrders;

		s_MarketDepthUpdateLevel()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_UPDATE_LEVEL;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		AtBidOrAskEnum GetSide() const;
		double GetPrice() const;
		double GetQuantity() const;
		MarketDepthUpdateTypeEnum GetUpdateType() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
		uint32_t GetNumOrders() const;
	};

	/*==========================================================================*/
	struct s_MarketDepthUpdateLevel_Int
	{	 
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		AtBidOrAskEnum Side;
		int32_t Price;
		int32_t Quantity;
		MarketDepthUpdateTypeEnum UpdateType;
		t_DateTimeWithMilliseconds DateTime;

		uint32_t NumOrders;

		s_MarketDepthUpdateLevel_Int()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_UPDATE_LEVEL_INT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		AtBidOrAskEnum GetSide() const;
		int32_t GetPrice() const;
		int32_t GetQuantity() const;
		MarketDepthUpdateTypeEnum GetUpdateType() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
		uint32_t GetNumOrders() const;
	};

	/*==========================================================================*/
	#pragma pack(push, 1)
	struct s_MarketDepthUpdateLevelFloatWithMilliseconds
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		t_DateTimeWithMillisecondsInt DateTime;
		float Price;
		float Quantity;
		AtBidOrAskEnum8 Side;
		MarketDepthUpdateTypeEnum UpdateType;
		uint16_t NumOrders;
		FinalUpdateInBatchEnum FinalUpdateInBatch;

		s_MarketDepthUpdateLevelFloatWithMilliseconds()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_UPDATE_LEVEL_FLOAT_WITH_MILLISECONDS;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		t_DateTimeWithMillisecondsInt GetDateTime() const;
		float GetPrice() const;
		float GetQuantity() const;
		int8_t GetSide() const;
		int8_t GetUpdateType() const;
		uint16_t GetNumOrders() const;
		FinalUpdateInBatchEnum GetFinalUpdateInBatch() const;
	};

	/*==========================================================================*/
	struct s_MarketDepthUpdateLevelNoTimestamp
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		float Price;
		float Quantity;
		uint16_t NumOrders;
		int8_t Side;
		int8_t UpdateType;
		FinalUpdateInBatchEnum FinalUpdateInBatch;

		s_MarketDepthUpdateLevelNoTimestamp()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_UPDATE_LEVEL_NO_TIMESTAMP;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		float GetPrice() const;
		float GetQuantity() const;
		uint16_t GetNumOrders() const;
		int8_t GetSide() const;
		int8_t GetUpdateType() const;
		FinalUpdateInBatchEnum GetFinalUpdateInBatch() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateTradeNoTimestamp
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		float Price;
		uint32_t Volume;
		AtBidOrAskEnum8 AtBidOrAsk;
		UnbundledTradeIndicatorEnum UnbundledTradeIndicator;
		TradeConditionEnum TradeCondition;

		s_MarketDataUpdateTradeNoTimestamp()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_TRADE_NO_TIMESTAMP;
			Size = sizeof(*this);
			UnbundledTradeIndicator = UNBUNDLED_TRADE_NONE;
		}

		uint32_t GetSymbolID() const;
		float GetPrice() const;
		uint32_t GetVolume() const;
		AtBidOrAskEnum8 GetAtBidOrAsk() const;
		UnbundledTradeIndicatorEnum GetUnbundledTradeIndicator() const;
		TradeConditionEnum GetTradeCondition() const;
	};


	#pragma pack(pop)

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionSettlement
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		double Price;
		t_DateTime4Byte DateTime;

		s_MarketDataUpdateSessionSettlement()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_SETTLEMENT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		double GetPrice() const;
		t_DateTime4Byte GetDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionSettlement_Int
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		int32_t Price;
		t_DateTime4Byte DateTime;

		s_MarketDataUpdateSessionSettlement_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_SETTLEMENT_INT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		int32_t GetPrice() const;
		t_DateTime4Byte GetDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionOpen
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		double Price;
		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateSessionOpen()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_OPEN;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		double GetPrice() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionOpen_Int
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		int32_t Price;
		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateSessionOpen_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_OPEN_INT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		int32_t GetPrice() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionNumTrades
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		int32_t NumTrades;

		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateSessionNumTrades()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_NUM_TRADES;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		int32_t GetNumTrades() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateTradingSessionDate
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		t_DateTime4Byte Date;

		s_MarketDataUpdateTradingSessionDate()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_TRADING_SESSION_DATE;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		t_DateTime4Byte GetDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDepthReject
	{
		uint16_t Size;
		uint16_t Type;
		uint32_t SymbolID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_MarketDepthReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DEPTH_REJECT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		const char* GetRejectText();
		void SetRejectText(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateTrade
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;

		AtBidOrAskEnum AtBidOrAsk;

		double Price;
		double Volume;
		t_DateTimeWithMilliseconds DateTime;

		s_MarketDataUpdateTrade()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_TRADE;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		AtBidOrAskEnum GetAtBidOrAsk() const;
		double GetPrice() const;
		double GetVolume() const;
		t_DateTimeWithMilliseconds GetDateTime() const;

	};

	/*==========================================================================*/
	struct s_MarketDataUpdateTrade_Int
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;

		AtBidOrAskEnum AtBidOrAsk;

		int32_t Price;
		int32_t Volume;
		t_DateTimeWithMilliseconds DateTime;


		s_MarketDataUpdateTrade_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_TRADE_INT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		AtBidOrAskEnum GetAtBidOrAsk() const;
		int32_t GetPrice() const;
		int32_t GetVolume() const;
		t_DateTimeWithMilliseconds GetDateTime() const;

	};

	/*==========================================================================*/
	struct s_MarketDataUpdateTradeWithUnbundledIndicator
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		AtBidOrAskEnum8 AtBidOrAsk;
		UnbundledTradeIndicatorEnum UnbundledTradeIndicator;
		uint8_t TradeCondition;
		uint8_t Reserve_1;
		uint32_t Reserve_2;
		double Price;
		uint32_t Volume;
		uint32_t Reserve_3;
		t_DateTimeWithMilliseconds DateTime;

		s_MarketDataUpdateTradeWithUnbundledIndicator()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR;
			Size = sizeof(*this);
			UnbundledTradeIndicator = UNBUNDLED_TRADE_NONE;
		}

		uint32_t GetSymbolID() const;
		AtBidOrAskEnum8 GetAtBidOrAsk() const;
		UnbundledTradeIndicatorEnum GetUnbundledTradeIndicator() const;
		uint8_t GetTradeCondition() const;
		double GetPrice() const;
		uint32_t GetVolume() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
	};

#pragma pack(push, 1)
	/*==========================================================================*/
	struct s_MarketDataUpdateTradeWithUnbundledIndicator2
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		float Price;
		uint32_t Volume;

		t_DateTimeWithMicrosecondsInt DateTime;

		AtBidOrAskEnum8 AtBidOrAsk;
		UnbundledTradeIndicatorEnum UnbundledTradeIndicator;
		TradeConditionEnum TradeCondition;

		s_MarketDataUpdateTradeWithUnbundledIndicator2()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR_2;
			Size = sizeof(*this);
			UnbundledTradeIndicator = UNBUNDLED_TRADE_NONE;
		}

		uint32_t GetSymbolID() const;
		float GetPrice() const;
		uint32_t GetVolume() const;
		t_DateTimeWithMicrosecondsInt GetDateTime() const;

		AtBidOrAskEnum8 GetAtBidOrAsk() const;
		UnbundledTradeIndicatorEnum GetUnbundledTradeIndicator() const;
	};

#pragma pack(pop)

	/*==========================================================================*/
	struct s_MarketDataUpdateBidAsk
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;

		double BidPrice;
		float BidQuantity;
		double AskPrice;
		float AskQuantity;
		t_DateTime4Byte DateTime;

		s_MarketDataUpdateBidAsk()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_BID_ASK;
			Size = sizeof(*this);

			BidPrice = DBL_MAX; //This also signifies the BidQuantity is unset
			AskPrice = DBL_MAX; //This also signifies the AskQuantity is unset
		}

		uint32_t GetSymbolID() const;
		double GetBidPrice() const;
		float GetBidQuantity() const;
		double GetAskPrice() const;
		float GetAskQuantity() const;
		t_DateTime4Byte GetDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateBidAsk_Int
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;

		int32_t BidPrice;
		int32_t BidQuantity;
		int32_t AskPrice;
		int32_t AskQuantity;
		t_DateTime4Byte DateTime;

		s_MarketDataUpdateBidAsk_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_BID_ASK_INT;
			Size = sizeof(*this);

			BidPrice = INT_MAX;
			AskPrice = INT_MAX;
		}

		uint32_t GetSymbolID() const;
		int32_t GetBidPrice() const;
		int32_t GetBidQuantity() const;
		int32_t GetAskPrice() const;
		int32_t GetAskQuantity() const;
		t_DateTime4Byte GetDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateBidAskCompact
	{
		uint16_t Size;
		uint16_t Type;

		float BidPrice;
		float BidQuantity;
		float AskPrice;
		float AskQuantity;

		t_DateTime4Byte DateTime;

		uint32_t SymbolID;

		s_MarketDataUpdateBidAskCompact()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_BID_ASK_COMPACT;
			Size = sizeof(*this);

			BidPrice = FLT_MAX;
			AskPrice = FLT_MAX;
		}

		float GetBidPrice() const;
		float GetBidQuantity() const;
		float GetAskPrice() const;
		float GetAskQuantity() const;
		t_DateTime4Byte GetDateTime() const;
		uint32_t GetSymbolID() const;
	};

#pragma pack(push, 1)
	/*==========================================================================*/
	struct s_MarketDataUpdateBidAskFloatWithMicroseconds
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		float BidPrice;
		float BidQuantity;
		float AskPrice;
		float AskQuantity;
		t_DateTimeWithMicrosecondsInt DateTime;

		s_MarketDataUpdateBidAskFloatWithMicroseconds()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_BID_ASK_FLOAT_WITH_MICROSECONDS;
			Size = sizeof(*this);

			BidPrice = FLT_MAX;
			AskPrice = FLT_MAX;
		}

		uint32_t GetSymbolID() const;
		float GetBidPrice() const;
		float GetBidQuantity() const;
		float GetAskPrice() const;
		float GetAskQuantity() const;
		t_DateTimeWithMicrosecondsInt GetDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateBidAskNoTimeStamp
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;

		float BidPrice;
		uint32_t BidQuantity;
		float AskPrice;
		uint32_t AskQuantity;

		s_MarketDataUpdateBidAskNoTimeStamp()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_BID_ASK_NO_TIMESTAMP;
			Size = sizeof(*this);

			BidPrice = FLT_MAX;
			AskPrice = FLT_MAX;
		}

		uint16_t GetSize() const;
		uint16_t GetType() const;

		uint32_t GetSymbolID() const;

		float GetBidPrice() const;
		uint32_t GetBidQuantity() const;
		float GetAskPrice() const;
		uint32_t GetAskQuantity() const;
	};

#pragma pack(pop)

	/*==========================================================================*/
	struct s_MarketDataUpdateTradeCompact
	{
		uint16_t Size;
		uint16_t Type;
	
		float Price;
		float Volume;
		t_DateTime4Byte DateTime;
		uint32_t SymbolID;
		AtBidOrAskEnum AtBidOrAsk;

		s_MarketDataUpdateTradeCompact()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_TRADE_COMPACT;
			Size = sizeof(*this);
		}

		float GetPrice() const;
		float GetVolume() const;
		t_DateTime4Byte GetDateTime() const;
		uint32_t GetSymbolID() const;
		AtBidOrAskEnum GetAtBidOrAsk() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionVolume
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		double Volume;
		t_DateTime4Byte TradingSessionDate;
		uint8_t IsFinalSessionVolume;

		s_MarketDataUpdateSessionVolume()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_VOLUME;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		double GetVolume() const;
		t_DateTime4Byte GetTradingSessionDate() const;
		uint8_t GetIsFinalSessionVolume() const;
	};
	/*==========================================================================*/
	struct s_MarketDataUpdateOpenInterest
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		uint32_t OpenInterest;

		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateOpenInterest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_OPEN_INTEREST;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		uint32_t GetOpenInterest() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};
	/*==========================================================================*/
	struct s_MarketDataUpdateSessionHigh
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		double Price;
		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateSessionHigh()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_HIGH;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		double GetPrice() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionHigh_Int
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		int32_t Price;
		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateSessionHigh_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_HIGH_INT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		int32_t GetPrice() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionLow
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		double Price;
		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateSessionLow()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_LOW;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		double GetPrice() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateSessionLow_Int
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		int32_t Price;
		t_DateTime4Byte TradingSessionDate;

		s_MarketDataUpdateSessionLow_Int()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_SESSION_LOW_INT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		int32_t GetPrice() const;
		t_DateTime4Byte GetTradingSessionDate() const;
	};

	/*==========================================================================*/
	struct s_MarketDataUpdateLastTradeSnapshot
	{
		uint16_t Size;
		uint16_t Type;

		uint32_t SymbolID;
		double LastTradePrice;
		double LastTradeVolume;
		t_DateTimeWithMilliseconds LastTradeDateTime;

		s_MarketDataUpdateLastTradeSnapshot()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = MARKET_DATA_UPDATE_LAST_TRADE_SNAPSHOT;
			Size = sizeof(*this);
		}

		uint32_t GetSymbolID() const;
		double GetLastTradePrice() const;
		double GetLastTradeVolume() const;
		t_DateTimeWithMilliseconds GetLastTradeDateTime() const;
	};

#pragma pack(push, 1)
	/*==========================================================================*/
	struct s_MarketOrdersRequest
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_ORDERS_REQUEST;

		RequestActionEnum RequestAction = SUBSCRIBE;
		uint32_t SymbolID = 0;
		char Symbol[SYMBOL_LENGTH] = { 0 };
		char Exchange[EXCHANGE_LENGTH] = { 0 };
		uint32_t SendQuantitiesGreaterOrEqualTo = 0;


		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);

		RequestActionEnum GetRequestAction() const;
		uint32_t GetSymbolID() const;
		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		int32_t GetSendQuantitiesGreaterOrEqualTo() const;
	};

	/*==========================================================================*/
	struct s_MarketOrdersReject
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_ORDERS_REJECT;

		uint32_t SymbolID = 0;
		char RejectText[TEXT_DESCRIPTION_LENGTH] = { 0 };

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);

		uint32_t GetSymbolID() const;
		const char* GetRejectText();
		void SetRejectText(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_MarketOrdersAdd//MARKET_ORDERS_ADD
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_ORDERS_ADD;

		uint32_t SymbolID = 0;
		DTC::BuySellEnum Side = BUY_SELL_UNSET;
		uint32_t Quantity = 0;
		double Price = 0;
		uint64_t OrderID = 0;
		t_DateTimeWithMicrosecondsInt DateTime = 0;

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		
		uint32_t GetSymbolID() const;
		DTC::BuySellEnum GetSide() const;
		uint32_t GetQuantity() const;
		double GetPrice() const;
		uint64_t GetOrderID() const;
		t_DateTimeWithMicrosecondsInt GetDateTime() const;
	};

	/*==========================================================================*/
	struct s_MarketOrdersModify//MARKET_ORDERS_MODIFY
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_ORDERS_MODIFY;

		uint32_t SymbolID = 0;
		uint32_t Quantity = 0;
		double Price = 0;
		uint64_t OrderID = 0;
		double PriorPrice = 0;
		uint32_t PriorQuantity = 0;
		uint64_t PriorOrderID = 0;
		t_DateTimeWithMicrosecondsInt DateTime = 0;

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);

		uint32_t GetSymbolID() const;
		uint32_t GetQuantity() const;
		double GetPrice() const;
		uint64_t GetOrderID() const;
		double GetPriorPrice() const;
		uint32_t GetPriorQuantity() const;
		uint64_t GetPriorOrderID() const;
		t_DateTimeWithMicrosecondsInt GetDateTime() const;

	};

	/*==========================================================================*/
	struct s_MarketOrdersRemove//MARKET_ORDERS_REMOVE
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_ORDERS_REMOVE;

		uint32_t SymbolID = 0;
		uint32_t Quantity = 0;
		double Price = 0;
		uint64_t OrderID = 0;
		t_DateTimeWithMicrosecondsInt DateTime = 0;
		DTC::BuySellEnum Side = BUY_SELL_UNSET;

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);

		uint32_t GetSymbolID() const;
		uint32_t GetQuantity() const;
		double GetPrice() const;
		uint64_t GetOrderID() const;
		t_DateTimeWithMicrosecondsInt GetDateTime() const;
		DTC::BuySellEnum GetSide() const;

	};

	/*==========================================================================*/
	
	struct s_MarketOrdersSnapshotMessageBoundary
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = MARKET_ORDERS_SNAPSHOT_MESSAGE_BOUNDARY;

		uint32_t SymbolID = 0;
		MessageSetBoundaryEnum MessageBoundary = MESSAGE_SET_BOUNDARY_UNSET;

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);

		uint32_t GetSymbolID() const;
		MessageSetBoundaryEnum GetMessageBoundary() const;

	};

#pragma pack(pop)
	/*==========================================================================*/
	struct s_SubmitNewSingleOrder
	{
		uint16_t Size;
		uint16_t Type;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		char ClientOrderID[ORDER_ID_LENGTH];

		OrderTypeEnum OrderType;

		BuySellEnum BuySell;

		double Price1;
		double Price2;

		double Quantity;

		TimeInForceEnum TimeInForce;

		t_DateTime GoodTillDateTime;
		
		uint8_t IsAutomatedOrder;

		uint8_t IsParentOrder;

		char FreeFormText[ORDER_FREE_FORM_TEXT_LENGTH];

		OpenCloseTradeEnum OpenOrClose;
		double MaxShowQuantity;

		s_SubmitNewSingleOrder()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SUBMIT_NEW_SINGLE_ORDER;
			Size = sizeof(*this);
		}

		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		const char* GetClientOrderID();
		void SetClientOrderID(const char* NewValue);
		OrderTypeEnum GetOrderType() const;
		BuySellEnum GetBuySell() const;
		double GetPrice1() const;
		double GetPrice2() const;
		double GetQuantity() const;
		TimeInForceEnum GetTimeInForce() const;
		t_DateTime GetGoodTillDateTime() const;
		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
		uint8_t GetIsAutomatedOrder() const;
		uint8_t GetIsParentOrder() const;
		const char* GetFreeFormText();
		void SetFreeFormText(const char* NewValue);
		OpenCloseTradeEnum GetOpenOrClose() const;
		double GetMaxShowQuantity() const;
	};

	/*==========================================================================*/
	struct s_SubmitNewSingleOrderInt
	{
		uint16_t Size;
		uint16_t Type;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		char ClientOrderID[ORDER_ID_LENGTH];

		OrderTypeEnum OrderType;
		BuySellEnum BuySell;

		int64_t Price1;
		int64_t Price2;
		float Divisor;
		int64_t Quantity;

		TimeInForceEnum TimeInForce;
		t_DateTime GoodTillDateTime;
		
		uint8_t IsAutomatedOrder;
		uint8_t IsParentOrder;

		char FreeFormText[ORDER_FREE_FORM_TEXT_LENGTH];
		
		OpenCloseTradeEnum OpenOrClose;


		s_SubmitNewSingleOrderInt()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SUBMIT_NEW_SINGLE_ORDER_INT;
			Size = sizeof(*this);
		}

		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
		const char* GetClientOrderID();
		void SetClientOrderID(const char* NewValue);

		OrderTypeEnum GetOrderType() const;
		BuySellEnum GetBuySell() const;
		int64_t GetPrice1() const;
		int64_t GetPrice2() const;
		float GetDivisor() const;
		int64_t GetQuantity() const;
		TimeInForceEnum GetTimeInForce() const;
		t_DateTime GetGoodTillDateTime() const;
		uint8_t GetIsAutomatedOrder() const;
		uint8_t GetIsParentOrder() const;

		const char* GetFreeFormText();
		void SetFreeFormText(const char* NewValue);

		OpenCloseTradeEnum GetOpenOrClose() const;
	};

	/*==========================================================================*/
	struct s_SubmitFlattenPositionOrder
	{
		uint16_t Size;
		uint16_t Type;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		char ClientOrderID[ORDER_ID_LENGTH];
		char FreeFormText[ORDER_FREE_FORM_TEXT_LENGTH];
		uint8_t IsAutomatedOrder;

		s_SubmitFlattenPositionOrder()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SUBMIT_FLATTEN_POSITION_ORDER;
			Size = sizeof(*this);
		}

		const char* GetSymbol();
		void SetSymbol(const char* NewValue);

		const char* GetExchange();
		void SetExchange(const char* NewValue);

		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);

		const char* GetClientOrderID();
		void SetClientOrderID(const char* NewValue);

		const char* GetFreeFormText();
		void SetFreeFormText(const char* NewValue);

		uint8_t GetIsAutomatedOrder() const;
	};

	/*==========================================================================*/
	struct s_CancelReplaceOrder
	{
		uint16_t Size;
		uint16_t Type;

		char ServerOrderID[ORDER_ID_LENGTH];
		char ClientOrderID[ORDER_ID_LENGTH];

		double Price1;
		double Price2;
		double Quantity;
		uint8_t Price1IsSet;
		uint8_t Price2IsSet;

		int32_t Unused;
		TimeInForceEnum TimeInForce;
		t_DateTime GoodTillDateTime;
		uint8_t UpdatePrice1OffsetToParent;
		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		s_CancelReplaceOrder()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = CANCEL_REPLACE_ORDER;
			Size = sizeof(*this);

			Price1IsSet = 1;
			Price2IsSet = 1;
		}

		const char* GetServerOrderID();
		void SetServerOrderID(const char* NewValue);
		const char* GetClientOrderID();
		void SetClientOrderID(const char* NewValue);
		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
		double GetPrice1() const;
		double GetPrice2() const;
		double GetQuantity() const;
		uint8_t GetPrice1IsSet() const;
		uint8_t GetPrice2IsSet() const;
		TimeInForceEnum GetTimeInForce() const;
		t_DateTime GetGoodTillDateTime() const;
		uint8_t GetUpdatePrice1OffsetToParent() const;
	};

	/*==========================================================================*/
	struct s_CancelReplaceOrderInt
	{
		uint16_t Size;
		uint16_t Type;

		char ServerOrderID[ORDER_ID_LENGTH];
		char ClientOrderID[ORDER_ID_LENGTH];

		int64_t Price1;
		int64_t Price2;
		float Divisor;
		int64_t Quantity;
		uint8_t Price1IsSet;
		uint8_t Price2IsSet;

		int32_t Unused;
		TimeInForceEnum TimeInForce;
		t_DateTime GoodTillDateTime;
		uint8_t UpdatePrice1OffsetToParent;

		s_CancelReplaceOrderInt()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = CANCEL_REPLACE_ORDER_INT;
			Size = sizeof(*this);

			Divisor = 1.0f;
			Price1IsSet = 1;
			Price2IsSet = 1;
		}

		const char* GetServerOrderID();
		void SetServerOrderID(const char* NewValue);
		const char* GetClientOrderID();
		void SetClientOrderID(const char* NewValue);
		int64_t GetPrice1() const;
		int64_t GetPrice2() const;
		float GetDivisor() const;
		int64_t GetQuantity() const;
		uint8_t GetPrice1IsSet() const;
		uint8_t GetPrice2IsSet() const;
		TimeInForceEnum GetTimeInForce() const;
		t_DateTime GetGoodTillDateTime() const;
		uint8_t GetUpdatePrice1OffsetToParent() const;
	};

	/*==========================================================================*/
	struct s_CancelOrder
	{
		uint16_t Size;
		uint16_t Type;
		
		char ServerOrderID[ORDER_ID_LENGTH];
		char ClientOrderID[ORDER_ID_LENGTH];
		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		s_CancelOrder()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = CANCEL_ORDER;
			Size = sizeof(*this);
		}

		const char* GetServerOrderID();
		void SetServerOrderID(const char* NewValue);
		const char* GetClientOrderID();
		void SetClientOrderID(const char* NewValue);
		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_SubmitNewOCOOrder
	{
		uint16_t Size;
		uint16_t Type;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		char ClientOrderID_1[ORDER_ID_LENGTH];
		OrderTypeEnum OrderType_1;
		BuySellEnum BuySell_1;
		double Price1_1;
		double Price2_1;
		double Quantity_1;

		char ClientOrderID_2[ORDER_ID_LENGTH];
		OrderTypeEnum OrderType_2;
		BuySellEnum BuySell_2;
		double Price1_2;
		double Price2_2;
		double Quantity_2;

		TimeInForceEnum TimeInForce;
		t_DateTime GoodTillDateTime;

		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		uint8_t IsAutomatedOrder;

		char ParentTriggerClientOrderID[ORDER_ID_LENGTH];

		char FreeFormText[ORDER_FREE_FORM_TEXT_LENGTH];

		OpenCloseTradeEnum OpenOrClose;

		PartialFillHandlingEnum PartialFillHandling;

		uint8_t UseOffsets;
		double OffsetFromParent1;
		double OffsetFromParent2;
		uint8_t MaintainSamePricesOnParentFill = 0;

		s_SubmitNewOCOOrder()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SUBMIT_NEW_OCO_ORDER;
			Size = sizeof(*this);
		}

		void SetClientOrderID_1(const char* NewValue);
		void SetClientOrderID_2(const char* NewValue);
		const char* GetFreeFormText();
		void SetFreeFormText(const char* NewValue);
		const char* GetClientOrderID_1();
		const char* GetClientOrderID_2();
		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		OrderTypeEnum GetOrderType_1() const;
		OrderTypeEnum GetOrderType_2() const;
		BuySellEnum GetBuySell_1() const;
		BuySellEnum GetBuySell_2() const;
		TimeInForceEnum GetTimeInForce() const;
		t_DateTime GetGoodTillDateTime() const;
		void SetParentTriggerClientOrderID(const char* NewValue);
		const char* GetParentTriggerClientOrderID();
		uint8_t GetIsAutomatedOrder() const;
		double GetPrice1_1() const;
		double GetPrice2_1() const;
		double GetPrice1_2() const;
		double GetPrice2_2() const;
		double GetQuantity_1() const;
		double GetQuantity_2() const;
		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
		OpenCloseTradeEnum GetOpenOrClose() const;
		PartialFillHandlingEnum GetPartialFillHandling() const;
		uint8_t GetUseOffsets() const;
		double GetOffsetFromParent1() const;
		double GetOffsetFromParent2() const;
		uint8_t GetMaintainSamePricesOnParentFill() const;
	};

	/*==========================================================================*/
	struct s_SubmitNewOCOOrderInt
	{
		uint16_t Size;
		uint16_t Type;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		char ClientOrderID_1[ORDER_ID_LENGTH];
		OrderTypeEnum OrderType_1;
		BuySellEnum BuySell_1;
		int64_t Price1_1;
		int64_t Price2_1;
		int64_t Quantity_1;

		char ClientOrderID_2[ORDER_ID_LENGTH];
		OrderTypeEnum OrderType_2;
		BuySellEnum BuySell_2;
		int64_t Price1_2;
		int64_t Price2_2;
		int64_t Quantity_2;

		TimeInForceEnum TimeInForce;
		t_DateTime GoodTillDateTime;

		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		uint8_t IsAutomatedOrder;

		char ParentTriggerClientOrderID[ORDER_ID_LENGTH];

		char FreeFormText[ORDER_FREE_FORM_TEXT_LENGTH];

		float Divisor;

		OpenCloseTradeEnum OpenOrClose;

		PartialFillHandlingEnum PartialFillHandling;

		s_SubmitNewOCOOrderInt()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SUBMIT_NEW_OCO_ORDER_INT;
			Size = sizeof(*this);
		}

		void SetClientOrderID_1(const char* NewValue);
		void SetClientOrderID_2(const char* NewValue);
		const char* GetFreeFormText();
		void SetFreeFormText(const char* NewValue);
		const char* GetClientOrderID_1();
		const char* GetClientOrderID_2();
		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		OrderTypeEnum GetOrderType_1() const;
		OrderTypeEnum GetOrderType_2() const;
		BuySellEnum GetBuySell_1() const;
		BuySellEnum GetBuySell_2() const;
		TimeInForceEnum GetTimeInForce() const;
		t_DateTime GetGoodTillDateTime() const;
		void SetParentTriggerClientOrderID(const char* NewValue);
		const char* GetParentTriggerClientOrderID();
		uint8_t GetIsAutomatedOrder() const;
		int64_t GetPrice1_1() const;
		int64_t GetPrice2_1() const;
		int64_t GetPrice1_2() const;
		int64_t GetPrice2_2() const;
		int64_t GetQuantity_1() const;
		int64_t GetQuantity_2() const;
		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
		float GetDivisor() const;
		OpenCloseTradeEnum GetOpenOrClose() const;
		PartialFillHandlingEnum GetPartialFillHandling() const;
	};

	/*==========================================================================*/
	struct s_OpenOrdersRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		int32_t RequestAllOrders;

		char ServerOrderID[ORDER_ID_LENGTH];
		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		s_OpenOrdersRequest()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = OPEN_ORDERS_REQUEST;
			Size = sizeof(*this);

			RequestAllOrders = 1;
		}

		int32_t GetRequestID() const;
		int32_t GetRequestAllOrders() const;
		void SetServerOrderID(const char* NewValue);
		const char* GetServerOrderID();
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
	};

	/*==========================================================================*/
	struct s_HistoricalOrderFillsRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		char ServerOrderID[ORDER_ID_LENGTH];

		int32_t NumberOfDays;

		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		t_DateTime StartDateTime;

		s_HistoricalOrderFillsRequest()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_ORDER_FILLS_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		int32_t GetNumberOfDays() const;
		t_DateTime GetStartDateTime() const;
		void SetServerOrderID(const char* NewValue);
		const char* GetServerOrderID();
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
	};

	/*==========================================================================*/
	struct s_HistoricalOrderFillsReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_HistoricalOrderFillsReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_ORDER_FILLS_REJECT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
	};


	/*==========================================================================*/
	struct s_CurrentPositionsRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char  TradeAccount[TRADE_ACCOUNT_LENGTH];

		s_CurrentPositionsRequest()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = CURRENT_POSITIONS_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
	};

	/*==========================================================================*/
	struct s_CurrentPositionsReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_CurrentPositionsReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = CURRENT_POSITIONS_REJECT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
	};

	/*==========================================================================*/
	struct s_OrderUpdate
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		int32_t TotalNumMessages;
		int32_t MessageNumber;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		char PreviousServerOrderID[ORDER_ID_LENGTH];

		char ServerOrderID[ORDER_ID_LENGTH];

		char ClientOrderID[ORDER_ID_LENGTH];

		char ExchangeOrderID[ORDER_ID_LENGTH];

		OrderStatusEnum OrderStatus;

		OrderUpdateReasonEnum OrderUpdateReason;

		OrderTypeEnum OrderType;

		BuySellEnum BuySell;

		double Price1;

		double Price2;

		TimeInForceEnum TimeInForce;
		t_DateTime GoodTillDateTime;
		double OrderQuantity;
		double FilledQuantity;
		double RemainingQuantity;
		double AverageFillPrice;

		double LastFillPrice;
		t_DateTimeWithMillisecondsInt LastFillDateTime;
		double LastFillQuantity;
		char LastFillExecutionID[64];

		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		char InfoText[TEXT_DESCRIPTION_LENGTH];

		uint8_t NoOrders;
		char ParentServerOrderID[ORDER_ID_LENGTH];
		char OCOLinkedOrderServerOrderID[ORDER_ID_LENGTH];

		OpenCloseTradeEnum OpenOrClose;

		char PreviousClientOrderID[ORDER_ID_LENGTH];
		char FreeFormText[ORDER_FREE_FORM_TEXT_LENGTH];
		t_DateTimeWithMillisecondsInt OrderReceivedDateTime;
		t_DateTimeWithMilliseconds LatestTransactionDateTime;

		s_OrderUpdate()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ORDER_UPDATE;
			Size = sizeof(*this);

			//The following initializations indicate to the Client that these variables are in an unset state and their values should not be used
			Price1 = DBL_MAX;
			Price2 = DBL_MAX; 

			OrderQuantity = DBL_MAX;
			FilledQuantity = DBL_MAX;
			RemainingQuantity = DBL_MAX;
			AverageFillPrice = DBL_MAX;

			LastFillPrice = DBL_MAX;
			LastFillQuantity = DBL_MAX;
		}

		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		const char* GetPreviousServerOrderID();
		void SetPreviousServerOrderID(const char* NewValue);
		const char* GetServerOrderID();
		void SetServerOrderID(const char* NewValue);
		const char* GetClientOrderID();
		void SetClientOrderID(const char* NewValue);
		const char* GetExchangeOrderID();
		void SetExchangeOrderID(const char* NewValue);
		void SetLastFillExecutionID(const char* NewValue);
		double GetOrderQuantity() const;
		double GetFilledQuantity() const;
		double GetRemainingQuantity() const;
		double GetLastFillQuantity() const;

		int32_t GetRequestID() const;
		int32_t GetMessageNumber() const;
		int32_t GetTotalNumMessages() const;
		OrderStatusEnum GetOrderStatus() const;
		OrderUpdateReasonEnum GetOrderUpdateReason() const;
		OrderTypeEnum GetOrderType() const;
		BuySellEnum GetBuySell() const;
		double GetPrice1() const;
		double GetPrice2() const;
		TimeInForceEnum GetTimeInForce() const;
		t_DateTime GetGoodTillDateTime() const;
		double GetAverageFillPrice() const;
		double GetLastFillPrice() const;
		t_DateTime GetLastFillDateTime() const;
		const char* GetLastFillExecutionID();

		const char* GetTradeAccount();
		void SetTradeAccount(const char* NewValue);
		const char* GetInfoText();
		void SetInfoText(const char* NewValue);
		uint8_t GetNoOrders() const;
		const char* GetParentServerOrderID();
		void SetParentServerOrderID(const char* NewValue);
		const char* GetOCOLinkedOrderServerOrderID();
		void SetOCOLinkedOrderServerOrderID(const char* NewValue);

		OpenCloseTradeEnum GetOpenOrClose() const;

		t_DateTime GetOrderReceivedDateTime() const;

		t_DateTimeWithMilliseconds GetLatestTransactionDateTime() const;

		const char* GetPreviousClientOrderID();
		void SetPreviousClientOrderID(const char* NewValue);

		const char* GetFreeFormText();
		void SetFreeFormText(const char* NewValue);
	};
	
	/*==========================================================================*/
	struct s_OpenOrdersReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_OpenOrdersReject()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = OPEN_ORDERS_REJECT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		const char* GetRejectText();
		void SetRejectText(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_HistoricalOrderFillResponse
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID; 

		int32_t TotalNumberMessages;
		int32_t MessageNumber;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];
		char ServerOrderID[ORDER_ID_LENGTH];
		BuySellEnum BuySell;
		double Price;
		t_DateTime DateTime;
		double Quantity;
		char UniqueExecutionID[ORDER_FILL_EXECUTION_LENGTH];
		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		OpenCloseTradeEnum OpenClose; 

		uint8_t NoOrderFills;
		char InfoText[TEXT_DESCRIPTION_LENGTH];

		double HighPriceDuringPosition;
		double LowPriceDuringPosition;
		double PositionQuantity;

		s_HistoricalOrderFillResponse()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_ORDER_FILL_RESPONSE;
			Size = sizeof(*this);
			PositionQuantity = DBL_MAX;
		}

		int32_t GetRequestID() const;
		int32_t GetMessageNumber() const;
		int32_t GetTotalNumberMessages() const;
		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		const char* GetServerOrderID();
		void SetServerOrderID(const char* NewValue);
		BuySellEnum GetBuySell() const;
		double GetPrice() const;
		t_DateTime GetDateTime() const;
		double GetQuantity() const;
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
		void SetUniqueExecutionID(const char* NewValue);
		const char* GetUniqueExecutionID();
		OpenCloseTradeEnum GetOpenClose() const;
		uint8_t GetNoOrderFills() const;
		double GetHighPriceDuringPosition() const;
		double GetLowPriceDuringPosition() const;
		double GetPositionQuantity() const;
		void SetInfoText(const char* NewValue);
		const char* GetInfoText();
	};

	/*==========================================================================*/
	struct s_PositionUpdate
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		int32_t TotalNumberMessages;
		int32_t MessageNumber;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		double Quantity;
		double AveragePrice;

		char PositionIdentifier[ORDER_ID_LENGTH];

		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		uint8_t NoPositions;

		uint8_t Unsolicited;

		double MarginRequirement;
		t_DateTime4Byte EntryDateTime;

		double QuantityLimit;

		s_PositionUpdate()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = POSITION_UPDATE;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		int32_t GetTotalNumberMessages() const;
		int32_t GetMessageNumber() const;
		void SetSymbol(const char* NewValue);
		const char* GetSymbol();
		void SetExchange(const char* NewValue);
		const char* GetExchange();
		double GetQuantity() const;
		double GetAveragePrice() const;
		void SetPositionIdentifier(const char* NewValue);
		const char* GetPositionIdentifier();
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
		uint8_t GetNoPositions() const;
		uint8_t GetUnsolicited() const;
		double GetMarginRequirement() const;
		t_DateTime4Byte GetEntryDateTime() const;
		double GetQuantityLimit() const;
	};

	/*==========================================================================*/
	struct s_AddCorrectingOrderFill
	{
		uint16_t Size;
		uint16_t Type;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];
		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		char ClientOrderID[ORDER_ID_LENGTH];
		DTC::BuySellEnum BuySell;
		double FillPrice;
		double FillQuantity;
		char FreeFormText[ORDER_FREE_FORM_TEXT_LENGTH];

		s_AddCorrectingOrderFill()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ADD_CORRECTING_ORDER_FILL;
			Size = sizeof(*this);
		}

		void SetSymbol(const char* NewValue);
		const char* GetSymbol();
		void SetExchange(const char* NewValue);
		const char* GetExchange();
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
		void SetClientOrderID(const char* NewValue);
		const char* GetClientOrderID();
		DTC::BuySellEnum GetBuySell() const;
		double GetFillPrice() const;
		double GetFillQuantity() const;
		void SetFreeFormText(const char* NewValue);
		const char* GetFreeFormText();
	};

	/*==========================================================================*/
	struct s_CorrectingOrderFillResponse
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = CORRECTING_ORDER_FILL_RESPONSE;

		char ClientOrderID[ORDER_ID_LENGTH] = {0};
		char ResultText[TEXT_MESSAGE_LENGTH] = {0};

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);

		void SetClientOrderID(const char* NewValue);
		const char* GetClientOrderID();
		void SetResultText(const char* NewValue);
		const char* GetResultText();
	};

	/*==========================================================================*/
	struct s_TradeAccountsRequest
	{
		uint16_t Size;
		uint16_t Type;
		int32_t RequestID;

		s_TradeAccountsRequest()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = TRADE_ACCOUNTS_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
	};

	/*==========================================================================*/
	struct s_TradeAccountResponse
	{
		uint16_t Size;
		uint16_t Type;

		int32_t TotalNumberMessages;

		int32_t MessageNumber;

		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		int32_t RequestID;

		s_TradeAccountResponse()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = TRADE_ACCOUNT_RESPONSE;
			Size = sizeof(*this);
		}

		int32_t GetTotalNumberMessages() const;
		int32_t GetMessageNumber() const;
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
		int32_t GetRequestID() const;
	};

	/*==========================================================================*/
	struct s_ExchangeListRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		s_ExchangeListRequest()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = EXCHANGE_LIST_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
	};

	/*==========================================================================*/
	struct s_ExchangeListResponse
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char Exchange[EXCHANGE_LENGTH];
		uint8_t IsFinalMessage;
		char Description[EXCHANGE_DESCRIPTION_LENGTH];

		s_ExchangeListResponse()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = EXCHANGE_LIST_RESPONSE;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		const char* GetDescription();
		void SetDescription(const char* NewValue);
		uint8_t GetIsFinalMessage() const;
	};

	/*==========================================================================*/
	struct s_SymbolsForExchangeRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char Exchange[EXCHANGE_LENGTH];

		SecurityTypeEnum SecurityType;
		RequestActionEnum RequestAction;
		char Symbol[SYMBOL_LENGTH];

		s_SymbolsForExchangeRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SYMBOLS_FOR_EXCHANGE_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		SecurityTypeEnum GetSecurityType() const;
		RequestActionEnum GetRequestAction() const;
		const char* GetSymbol();
		void SetSymbol(const char* NewValue);
	};

	/*==========================================================================*/
	struct s_UnderlyingSymbolsForExchangeRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		char Exchange[EXCHANGE_LENGTH];

		SecurityTypeEnum SecurityType;

		s_UnderlyingSymbolsForExchangeRequest()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = UNDERLYING_SYMBOLS_FOR_EXCHANGE_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		SecurityTypeEnum GetSecurityType() const;
	};

	/*==========================================================================*/
	struct s_SymbolsForUnderlyingRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		char UnderlyingSymbol[UNDERLYING_SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		SecurityTypeEnum SecurityType;

		s_SymbolsForUnderlyingRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SYMBOLS_FOR_UNDERLYING_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		const char* GetUnderlyingSymbol();
		void SetUnderlyingSymbol(const char* NewValue);
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		SecurityTypeEnum GetSecurityType() const;
	};

	/*==========================================================================*/
	struct s_SymbolSearchRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		char SearchText[SYMBOL_DESCRIPTION_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		SecurityTypeEnum SecurityType;
		SearchTypeEnum SearchType;

		s_SymbolSearchRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SYMBOL_SEARCH_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		const char* GetExchange();
		void SetExchange(const char* NewValue);
		const char* GetSearchText();
		void SetSearchText(const char* NewValue);
		SecurityTypeEnum GetSecurityType() const;
		SearchTypeEnum GetSearchType() const;
	};

	/*==========================================================================*/
	struct s_SecurityDefinitionForSymbolRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		s_SecurityDefinitionForSymbolRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SECURITY_DEFINITION_FOR_SYMBOL_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetSymbol(const char* NewValue);
		const char* GetSymbol();
		void SetExchange(const char* NewValue);
		const char* GetExchange();
	};

	/*==========================================================================*/
	struct s_SecurityDefinitionResponse
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];

		SecurityTypeEnum SecurityType;
		
		char Description[SYMBOL_DESCRIPTION_LENGTH];
		float MinPriceIncrement;
		PriceDisplayFormatEnum PriceDisplayFormat;
		float CurrencyValuePerIncrement;

		uint8_t IsFinalMessage;

		float FloatToIntPriceMultiplier;
		float IntToFloatPriceDivisor;

		char UnderlyingSymbol[UNDERLYING_SYMBOL_LENGTH];
		
		uint8_t UpdatesBidAskOnly;

		float StrikePrice;

		PutCallEnum PutOrCall;

		uint32_t ShortInterest;

		t_DateTime4Byte SecurityExpirationDate;

		float BuyRolloverInterest;
		float SellRolloverInterest;

		float EarningsPerShare;
		uint32_t SharesOutstanding;

		float IntToFloatQuantityDivisor;

		uint8_t HasMarketDepthData;

		float DisplayPriceMultiplier;

		char ExchangeSymbol[SYMBOL_LENGTH];

		float InitialMarginRequirement;
		float MaintenanceMarginRequirement;
		char Currency[CURRENCY_CODE_LENGTH];

		float ContractSize;
		uint32_t OpenInterest;
		t_DateTime4Byte RolloverDate;
		uint8_t IsDelayed;

		s_SecurityDefinitionResponse()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SECURITY_DEFINITION_RESPONSE;
			Size = sizeof(*this);

			PriceDisplayFormat = PRICE_DISPLAY_FORMAT_UNSET;
			PutOrCall = PC_UNSET;

			FloatToIntPriceMultiplier = 1.0;
			IntToFloatPriceDivisor = 1.0;
			HasMarketDepthData = 1;
			DisplayPriceMultiplier = 1.0;
		}

		int32_t GetRequestID() const;
		void SetSymbol(const char* NewValue);
		const char* GetSymbol();
		void SetExchange(const char* NewValue);
		const char* GetExchange();
		SecurityTypeEnum GetSecurityType() const;
		void SetDescription(const char* NewValue);
		const char* GetDescription();
		float GetMinPriceIncrement() const;
		PriceDisplayFormatEnum GetPriceDisplayFormat() const;
		float GetCurrencyValuePerIncrement() const;
		uint8_t GetIsFinalMessage() const;
		float GetFloatToIntPriceMultiplier() const;
		float GetIntToFloatPriceDivisor() const;
		const char* GetUnderlyingSymbol();
		void SetUnderlyingSymbol(const char* NewValue);

		uint8_t GetUpdatesBidAskOnly() const;
		float GetStrikePrice() const;
		PutCallEnum GetPutOrCall() const;
		uint32_t GetShortInterest() const;
		t_DateTime4Byte GetSecurityExpirationDate() const;
		float GetBuyRolloverInterest() const;
		float GetSellRolloverInterest() const;
		float GetEarningsPerShare() const;
		uint32_t GetSharesOutstanding() const;
		float GetIntToFloatQuantityDivisor() const;
		uint8_t GetHasMarketDepthData() const;
		float GetDisplayPriceMultiplier() const;
		const char* GetExchangeSymbol();
		void SetExchangeSymbol(const char* NewValue);
		float GetInitialMarginRequirement() const;
		float GetMaintenanceMarginRequirement() const;
		const char* GetCurrency();
		void SetCurrency(const char* NewValue);
		float GetContractSize() const;
		uint32_t GetOpenInterest() const;
		t_DateTime4Byte GetRolloverDate() const;
		uint8_t GetIsDelayed() const;
	};

	
	/*==========================================================================*/
	struct s_SecurityDefinitionReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_SecurityDefinitionReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = SECURITY_DEFINITION_REJECT;
			Size = sizeof(*this);
		}

		uint32_t GetRequestID() const;

		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
	};

	/*==========================================================================*/
	struct s_AccountBalanceRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		s_AccountBalanceRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ACCOUNT_BALANCE_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;

		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
	};

	/*==========================================================================*/
	struct s_AccountBalanceReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_AccountBalanceReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ACCOUNT_BALANCE_REJECT;
			Size = sizeof(*this);
		}

		uint32_t GetRequestID() const;

		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
	};

	/*==========================================================================*/
	struct s_AccountBalanceUpdate
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		double CashBalance;

		double BalanceAvailableForNewPositions;

		char AccountCurrency[8];

		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		double SecuritiesValue; 
		double MarginRequirement;

		int32_t TotalNumberMessages;
		int32_t MessageNumber;
		uint8_t NoAccountBalances;
		uint8_t Unsolicited;

		double OpenPositionsProfitLoss;
		double DailyProfitLoss;

		char InfoText[TEXT_DESCRIPTION_LENGTH];
		uint64_t TransactionIdentifier;
		double DailyNetLossLimit;
		double TrailingAccountValueToLimitPositions;

		uint8_t DailyNetLossLimitReached = 0;
		uint8_t IsUnderRequiredMargin = 0;

		s_AccountBalanceUpdate()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ACCOUNT_BALANCE_UPDATE;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		double GetCashBalance() const;
		double GetBalanceAvailableForNewPositions() const;
		void SetAccountCurrency(const char* NewValue);
		const char* GetAccountCurrency();
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
		double GetSecuritiesValue() const;
		double GetMarginRequirement() const;

		int32_t GetTotalNumberMessages() const;
		int32_t GetMessageNumber() const;
		uint8_t GetNoAccountBalances() const;
		uint8_t GetUnsolicited() const;

		double GetOpenPositionsProfitLoss() const;
		double GetDailyProfitLoss() const;

		void SetInfoText(const char* NewValue);
		const char* GetInfoText();

		uint64_t GetTransactionIdentifier() const;
		double GetDailyNetLossLimit() const;
		double GetTrailingAccountValueToLimitPositions() const;
		uint8_t GetDailyNetLossLimitReached() const;
		uint8_t GetIsUnderRequiredMargin() const;
	};

	/*==========================================================================*/
	struct s_AccountBalanceAdjustment
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		double CreditAmount;
		double DebitAmount;
		char Currency[CURRENCY_CODE_LENGTH];

		char Reason[TEXT_DESCRIPTION_LENGTH];

		s_AccountBalanceAdjustment()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ACCOUNT_BALANCE_ADJUSTMENT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;

		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();

		double GetCreditAmount() const;
		double GetDebitAmount() const;

		void SetCurrency(const char* NewValue);
		const char* GetCurrency();

		void SetReason(const char* NewValue);
		const char* GetReason();
	};

	/*==========================================================================*/
	struct s_AccountBalanceAdjustmentReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_AccountBalanceAdjustmentReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ACCOUNT_BALANCE_ADJUSTMENT_REJECT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
	};

	/*==========================================================================*/
	struct s_AccountBalanceAdjustmentComplete
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		int64_t TransactionID;

		s_AccountBalanceAdjustmentComplete()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ACCOUNT_BALANCE_ADJUSTMENT_COMPLETE;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		int64_t GetTransactionID() const;
	};

	/*==========================================================================*/
	struct s_HistoricalAccountBalancesRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		t_DateTime StartDateTime;

		s_HistoricalAccountBalancesRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_ACCOUNT_BALANCES_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;

		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();

		t_DateTime GetStartDateTime() const;
	};

	/*==========================================================================*/
	struct s_HistoricalAccountBalancesReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_HistoricalAccountBalancesReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_ACCOUNT_BALANCES_REJECT;
			Size = sizeof(*this);
		}

		uint32_t GetRequestID() const;

		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
	};

	/*==========================================================================*/
	struct s_HistoricalAccountBalanceResponse
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		t_DateTimeWithMilliseconds DateTime;
		double CashBalance;
		char AccountCurrency[8];
		char TradeAccount[TRADE_ACCOUNT_LENGTH];
		uint8_t IsFinalResponse;
		uint8_t NoAccountBalances;
		char InfoText[TEXT_DESCRIPTION_LENGTH];
		char TransactionId[GENERAL_IDENTIFIER_LENGTH];

		s_HistoricalAccountBalanceResponse()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_ACCOUNT_BALANCE_RESPONSE;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
		double GetCashBalance() const;
		void SetAccountCurrency(const char* NewValue);
		const char* GetAccountCurrency();
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
		uint8_t GetIsFinalResponse() const;
		uint8_t GetNoAccountBalances() const;
		void SetInfoText(const char* NewValue);
		const char* GetInfoText();
		void SetTransactionId(const char* NewValue);
		const char* GetTransactionId();
	};

	/*==========================================================================*/
	struct s_UserMessage
	{
		uint16_t Size;
		uint16_t Type;

		char UserMessage[TEXT_MESSAGE_LENGTH];

		uint8_t IsPopupMessage;

		s_UserMessage()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = USER_MESSAGE;
			Size = sizeof(*this);

			IsPopupMessage = 1;
		}

		void SetUserMessage(const char* NewValue);
		const char* GetUserMessage();
		uint8_t GetIsPopupMessage() const;
	};

	/*==========================================================================*/
	struct s_GeneralLogMessage
	{
		uint16_t Size;
		uint16_t Type;

		char MessageText[128];

		s_GeneralLogMessage()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = GENERAL_LOG_MESSAGE;
			Size = sizeof(*this);
		}

		void SetMessageText(const char* NewValue);
		const char* GetMessageText();
	};

	/*==========================================================================*/
	struct s_AlertMessage
	{
		uint16_t Size;
		uint16_t Type;

		char MessageText[128];
		char TradeAccount[TRADE_ACCOUNT_LENGTH];

		s_AlertMessage()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = ALERT_MESSAGE;
			Size = sizeof(*this);
		}

		void SetMessageText(const char* NewValue);
		const char* GetMessageText();
		void SetTradeAccount(const char* NewValue);
		const char* GetTradeAccount();
	};

	/*==========================================================================*/
	struct s_JournalEntryAdd
	{
		uint16_t Size;
		uint16_t Type;

		char JournalEntry[TEXT_MESSAGE_LENGTH];
		t_DateTime DateTime;

		s_JournalEntryAdd()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = JOURNAL_ENTRY_ADD;
			Size = sizeof(*this);
		}

		void SetJournalEntry(const char* NewValue);
		const char* GetJournalEntry();
		t_DateTime GetDateTime() const;
	};

	/*==========================================================================*/
	struct s_JournalEntriesRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		t_DateTime StartDateTime;

		s_JournalEntriesRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = JOURNAL_ENTRIES_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		t_DateTime GetStartDateTime() const;
	};

	/*==========================================================================*/
	struct s_JournalEntriesReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		s_JournalEntriesReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = JOURNAL_ENTRIES_REJECT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
	};

	/*==========================================================================*/
	struct s_JournalEntryResponse
	{
		uint16_t Size;
		uint16_t Type;

		char JournalEntry[TEXT_MESSAGE_LENGTH];
		t_DateTime DateTime;
		uint8_t IsFinalResponse;

		s_JournalEntryResponse()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = JOURNAL_ENTRY_RESPONSE;
			Size = sizeof(*this);
		}

		void SetJournalEntry(const char* NewValue);
		const char* GetJournalEntry();
		t_DateTime GetDateTime() const;
		uint8_t GetIsFinalResponse() const;
	};
	
	/*==========================================================================*/
	struct s_HistoricalPriceDataRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];
		HistoricalDataIntervalEnum RecordInterval;
		t_DateTime StartDateTime;
		t_DateTime EndDateTime;
		uint32_t MaxDaysToReturn;
		uint8_t  UseZLibCompression;
		uint8_t RequestDividendAdjustedStockData;
		uint16_t Integer_1;

		s_HistoricalPriceDataRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_PRICE_DATA_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetSymbol(const char* NewValue);
		const char* GetSymbol();
		void SetExchange(const char* NewValue);
		const char* GetExchange();
		HistoricalDataIntervalEnum GetRecordInterval() const;
		t_DateTime GetStartDateTime() const;
		t_DateTime GetEndDateTime() const;
		uint32_t GetMaxDaysToReturn() const;
		uint8_t GetUseZLibCompression() const;
		uint8_t GetRequestDividendAdjustedStockData() const;
		uint16_t GetInteger_1() const;
	};

	/*==========================================================================*/
	struct s_HistoricalPriceDataResponseHeader
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		HistoricalDataIntervalEnum RecordInterval;

		uint8_t UseZLibCompression;
		
		uint8_t NoRecordsToReturn;

		float IntToFloatPriceDivisor;

		s_HistoricalPriceDataResponseHeader()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_PRICE_DATA_RESPONSE_HEADER;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		HistoricalDataIntervalEnum GetRecordInterval() const;
		uint8_t GetUseZLibCompression() const;
		uint8_t GetNoRecordsToReturn() const;
		float GetIntToFloatPriceDivisor() const;
	};

	/*==========================================================================*/
	struct s_HistoricalPriceDataReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char RejectText[TEXT_DESCRIPTION_LENGTH];

		HistoricalPriceDataRejectReasonCodeEnum RejectReasonCode;
		uint16_t RetryTimeInSeconds;

		s_HistoricalPriceDataReject()
		{
			Clear();
		}
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_PRICE_DATA_REJECT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetRejectText(const char* NewValue);
		const char* GetRejectText();
		HistoricalPriceDataRejectReasonCodeEnum GetRejectReasonCode() const;
		uint16_t GetRetryTimeInSeconds() const;
	};

	/*==========================================================================*/
	struct s_HistoricalPriceDataRecordResponse
	{
		uint16_t Size;
		uint16_t Type;
		int32_t RequestID;

		//Format can also be t_DateTime. Check value to determine. 
		t_DateTimeWithMicrosecondsInt StartDateTime;

		double OpenPrice;
		double HighPrice;
		double LowPrice;
		double LastPrice;
		double Volume;
		union
		{
			uint32_t OpenInterest;
			uint32_t NumTrades;
		};
		double BidVolume;
		double AskVolume;

		uint8_t IsFinalRecord;

		s_HistoricalPriceDataRecordResponse()
		{
			Clear(); 
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_PRICE_DATA_RECORD_RESPONSE;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		t_DateTimeWithMicrosecondsInt GetStartDateTime() const;
		double GetOpenPrice() const;
		double GetHighPrice() const;
		double GetLowPrice() const;
		double GetLastPrice() const;
		double GetVolume() const;
		uint32_t GetOpenInterest() const;
		uint32_t GetNumTrades() const;
		double GetBidVolume() const;
		double GetAskVolume() const;
		uint8_t GetIsFinalRecord() const;
	};

	/*==========================================================================*/
	struct s_HistoricalPriceDataTickRecordResponse
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE;;
		int32_t RequestID = 0;

		t_DateTimeWithMilliseconds DateTime = 0;
		AtBidOrAskEnum AtBidOrAsk = BID_ASK_UNSET;

		double Price = 0;
		double Volume = 0;

		uint8_t IsFinalRecord = 0;
		
		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);

		int32_t GetRequestID() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
		double GetPrice() const;
		double GetVolume() const;
		AtBidOrAskEnum GetAtBidOrAsk() const;
		uint8_t GetIsFinalRecord() const;
	};

	/*==========================================================================*/
	struct s_HistoricalPriceDataRecordResponse_Int
	{
		uint16_t Size = sizeof(*this);
		uint16_t Type = HISTORICAL_PRICE_DATA_RECORD_RESPONSE_INT;
		int32_t RequestID = 0;

		t_DateTime StartDateTime = 0;
		int32_t OpenPrice = 0;
		int32_t HighPrice = 0;
		int32_t LowPrice = 0;
		int32_t LastPrice = 0;
		int32_t Volume = 0;
		union
		{
			uint32_t OpenInterest = 0;
			uint32_t NumTrades;
		};
		int32_t BidVolume = 0;
		int32_t AskVolume = 0;

		uint8_t IsFinalRecord = 0;

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);

		int32_t GetRequestID() const;
		t_DateTime GetStartDateTime() const;
		int32_t GetOpenPrice() const;
		int32_t GetHighPrice() const;
		int32_t GetLowPrice() const;
		int32_t GetLastPrice() const;
		int32_t GetVolume() const;
		uint32_t GetOpenInterest() const;
		uint32_t GetNumTrades() const;
		int32_t GetBidVolume() const;
		int32_t GetAskVolume() const;
		uint8_t GetIsFinalRecord() const;
	};

	/*==========================================================================*/
	struct s_HistoricalPriceDataTickRecordResponse_Int
	{
		uint16_t Size;
		uint16_t Type;
		int32_t RequestID;

		t_DateTimeWithMilliseconds DateTime;

		int32_t Price;
		int32_t Volume;

		AtBidOrAskEnum AtBidOrAsk;
		uint8_t IsFinalRecord;

		s_HistoricalPriceDataTickRecordResponse_Int()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE_INT;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		t_DateTimeWithMilliseconds GetDateTime() const;
		AtBidOrAskEnum GetAtBidOrAsk() const;
		int32_t GetPrice() const;
		int32_t GetVolume() const;
		uint8_t GetIsFinalRecord() const;
	};

	/*==========================================================================*/
	struct s_HistoricalPriceDataResponseTrailer
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		t_DateTimeWithMicrosecondsInt FinalRecordLastDateTime;

		s_HistoricalPriceDataResponseTrailer()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void * p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_PRICE_DATA_RESPONSE_TRAILER;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		t_DateTimeWithMicrosecondsInt GetFinalRecordLastDateTime() const;
	};

	/*==========================================================================*/
	struct s_HistoricalMarketDepthDataRequest
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		char Symbol[SYMBOL_LENGTH];
		char Exchange[EXCHANGE_LENGTH];
		t_DateTimeWithMicrosecondsInt StartDateTime;
		t_DateTimeWithMicrosecondsInt EndDateTime;
		uint8_t  UseZLibCompression;
		uint8_t Integer_1;

		s_HistoricalMarketDepthDataRequest()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_MARKET_DEPTH_DATA_REQUEST;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		void SetSymbol(const char* NewValue);
		const char* GetSymbol();
		void SetExchange(const char* NewValue);
		const char* GetExchange();
		t_DateTimeWithMicrosecondsInt GetStartDateTime() const;
		t_DateTimeWithMicrosecondsInt GetEndDateTime() const;
		uint8_t GetUseZLibCompression() const;
		uint8_t GetInteger_1() const;
	};

	/*==========================================================================*/
	struct s_HistoricalMarketDepthDataResponseHeader
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;
		uint8_t UseZLibCompression;
		uint8_t NoRecordsToReturn;

		s_HistoricalMarketDepthDataResponseHeader()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_MARKET_DEPTH_DATA_RESPONSE_HEADER;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;
		uint8_t GetUseZLibCompression() const;
		uint8_t GetNoRecordsToReturn() const;
	};

	/*==========================================================================*/
	struct s_HistoricalMarketDepthDataReject
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		char RejectText[TEXT_DESCRIPTION_LENGTH];

		HistoricalPriceDataRejectReasonCodeEnum RejectReasonCode;

		s_HistoricalMarketDepthDataReject()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_MARKET_DEPTH_DATA_REJECT;
			Size = sizeof(*this);
			RejectReasonCode = DTC::HPDR_UNSET;
		}

		int32_t GetRequestID() const;

		void SetRejectText(const char* NewValue);
		const char* GetRejectText();

		HistoricalPriceDataRejectReasonCodeEnum GetRejectReasonCode() const;
	};

	/*==========================================================================*/
	struct s_HistoricalMarketDepthDataRecordResponse
	{
		uint16_t Size;
		uint16_t Type;

		int32_t RequestID;

		t_DateTimeWithMicrosecondsInt StartDateTime;
		uint8_t Command;
		uint8_t Flags;
		uint16_t NumOrders;

		float Price;
		uint32_t Quantity;

		uint8_t IsFinalRecord;

		s_HistoricalMarketDepthDataRecordResponse()
		{
			Clear();
		}

		uint16_t GetMessageSize() const;
		void CopyFrom(void* p_SourceData);
		void Clear()
		{
			memset(this, 0, sizeof(*this));
			Type = HISTORICAL_MARKET_DEPTH_DATA_RECORD_RESPONSE;
			Size = sizeof(*this);
		}

		int32_t GetRequestID() const;

		t_DateTimeWithMicrosecondsInt GetStartDateTime() const;
		uint8_t GetCommand() const;
		uint8_t GetFlags() const;
		uint16_t GetNumOrders() const;

		float GetPrice() const;
		uint32_t GetQuantity() const;

		uint8_t GetIsFinalRecord() const;
	};

#pragma pack(pop)
}
