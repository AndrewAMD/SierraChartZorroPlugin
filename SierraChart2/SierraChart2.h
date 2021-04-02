#pragma once
#ifdef SIERRACHART2_EXPORTS
#define DLLFUNC  extern "C" __declspec(dllexport)
#else
#define DLLFUNC extern "C" __declspec(dllimport)
#endif

#include <Windows.h>
#include "dtc.h"

#include <string>
#include <map>

#define PLUGIN_VERSION 2
#define HEARTBEAT_SECONDS 120

// default network settings
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT1 "11099"
#define DEFAULT_PORT2 "11097"
#define DEFAULT_USERNAME "_"
#define DEFAULT_PASSWORD "_"
#define DEFAULT_ACCOUNT "Sim1"

#define MAXTICKS 100000


struct s_Asset {
	std::string SCSymbol;
	std::string UnderlyingSymbol; //only filled if configured with SC_SET_FUTURES_CONTRACT_CONFIG
	std::string ZorroSymbol; // only filled if Zorro uses -FUT- symbol.
	s_SecurityDefinitionResponse definition;
	bool is_defined = false;
	bool is_subscribed = false;
	uint32_t SymbolID = 0;
	std::map<int, double> mBook;  // book_key to volume (bid is negaive key)
	int nExpiry = 0;
	double vPrice = 0;
	double vSpread = 0;
	double vVolume = 0;
	double vPip = 0; //"pricePrecision"
	double vPipCost = 0;
	double vLotAmount = 0; // Based on present value of SET_AMOUNT
	double vMarginCost = 0;
	double vRollLong = 0;
	double vRollShort = 0;
};



// variables
extern std::map<std::string, s_OrderUpdate> g_mOrders; //key:ServerOrderID.
extern std::map<std::string, s_Asset> g_mAssets; // key: SCSymbol
extern std::map<std::string, s_AccountBalanceUpdate> g_mBalances; // key: TradeAccount
extern std::string g_sUser;
extern std::string g_sTradeaccountSelected;
extern std::string g_sHost;
extern std::string g_sPortMain;
extern std::string g_sPortHist;
extern char g_Symbol[SYMBOL_LENGTH];
extern int g_PriceType;
extern TimeInForceEnum g_TimeInForce;
extern int g_OrderBlockMode;   // 1: allow, 0: disable blocking on order placement
extern int g_nLastTradeID;
extern int g_OrderWait_ms;
extern bool g_BeQuiet;
s_OrderUpdate* get_order_by_ServerOrderID(const char* ServerOrderID);
s_OrderUpdate* get_order_by_ClientOrderID(const char* ClientOrderID);
s_OrderUpdate* get_order_by_TradeID(int nTradeID);
s_Asset* get_asset_by_SCSymbol(const char* SCSymbol);
s_Asset* get_asset_by_SymbolID(uint32_t SymbolID);
s_Asset* get_asset_by_ZorroSymbol(const char* ZorroSymbol);
void define(s_Asset* pAsset);

int new_TradeID();
const char* new_ClientOrderID(int nTradeID);
int get_TradeID(const char* sClientOrderID);


#include "zorro_incl.h"
DLLFUNC double BrokerCommand(int Command, DWORD dwParameter);
DLLFUNC int BrokerAsset(
	char* ZorroSymbol, double* pPrice, double* pSpread, double* pVolume,
	double* pPip, double* pPipCost, double* pLotAmount,
	double* pMarginCost, double* pRollLong, double* pRollShort);

#define MO_JAN (1<<0)
#define MO_FEB (1<<1)
#define MO_MAR (1<<2)
#define MO_APR (1<<3)
#define MO_MAY (1<<4)
#define MO_JUN (1<<5)
#define MO_JUL (1<<6)
#define MO_AUG (1<<7)
#define MO_SEP (1<<8)
#define MO_OCT (1<<9)
#define MO_NOV (1<<10)
#define MO_DEC (1<<11)
#define SC_GET_SNAPSHOT                6001
#define SC_GET_SECURITYDEF             6002
#define SC_SET_ORDERBLOCKMODE          6003 // 1: ENABLE, 0: DISABLE BLOCKING ON ORDER PLACEMENT
#define SC_SET_FUTURES_CONTRACT_CONFIG 6004 
#pragma pack(push,1)
typedef struct SC_SNAPSHOT {
	double SessionSettlementPrice;
	double SessionOpenPrice;
	double SessionHighPrice;
	double SessionLowPrice;
	double SessionVolume;
	unsigned int SessionNumTrades;
	unsigned int OpenInterest;
	double vBidPrice;
	double vAskPrice;
	double vAskQuantity;
	double vBidQuantity;
	double vLastTradePrice;
	double vLastTradeVolume;
	DATE LastTradeDateTime;
	DATE BidAskDateTime;
	DATE SessionSettlementDateTime;
	DATE TradingSessionDate;
} SC_SNAPSHOT;
typedef struct SC_SECURITYDEF{
	char sSymbol[64];
	char sExchange[16];
	int SecurityType;					// See DTC SecurityTypeEnum
	char sDescription[64];
	float MinPriceIncrement;
	int PriceDisplayFormat;				// see DTC PriceDisplayFormatEnum
	float CurrencyValuePerIncrement;
	float FloatToIntPriceMultiplier;
	float IntToFloatPriceDivisor;
	char sUnderlyingSymbol[32];
	bool UpdatesBidAskOnly;
	float StrikePrice;
	int PutOrCall;						// 0: unset, 1: call, 2: put
	unsigned int ShortInterest;
	DATE SecurityExpirationDate;
	float BuyRolloverInterest;
	float SellRolloverInterest;
	float EarningsPerShare;
	unsigned int SharesOutstanding;
	float IntToFloatQuantityDivisor;
	unsigned char HasMarketDepthData;
	float DisplayPriceMultiplier;
	char sExchangeSymbol[64];
	float InitialMarginRequirement;
	float MaintenanceMarginRequirement;
	char sCurrency[8];
	float ContractSize;
	unsigned int OpenInterest;
	DATE RolloverDate;
	unsigned char IsDelayed;
} SC_SECURITYDEF;
#pragma pack(pop)
