# Sierra Chart Plugin for Zorro

This plugin works both as a broker plugin to the Zorro Trading Automaton and as a client to Sierra Chart in order to:
1) Get live market data
2) Get historical market data
3) Trade algorithmically
4) Track your trading account

This plugin was written in Win32 C/C++ using Visual Studio 2017.

## Build Instructions

This plugin depends on the following libraries:

* Asio standalone library (included)
* DTC Protocol library (included)

Build in Visual Studio 2019 or greater.  This plugin must be compiled in 32-bit (x86) in order to be compatible with Zorro.

## Installation Instructions

To install the plugin, simply place the SierraChart.dll file in the Plugin folder where Zorro is installed.

[The DLL release builds can be found here.](https://github.com/AndrewAMD/SierraChartZorroPlugin/releases)

## About Sierra Chart

Sierra Chart is a trading platform with support for [many brokers](https://www.sierrachart.com/index.php?page=doc/SupportedDataAndTradingServices.php).

Sierra Chart has a fully integrated DTC Server.  It has two dedicated ports:
1) One for all trading, current market data, account data, and position data.
2) One for all historical market data.

## Configuring Sierra Chart DTC Server

A Sierra Chart instance can be accessed locally or over the internet. This plugin only uses TLS encryption.  Unencrypted connections are not supported by this plugin.

To set up Sierra Chart's DTC Server:
* Open Sierra Chart
* Global Settings -> Sierra Chart Server Settings
* Sierra Chart Server Settings Window:
  * Click "[DTC Protocol Server]" at the top
  * Set "DTC Protocol Server" to "Yes"
  * Set "Listening Port" to "11099"
  * Set "Historical Data Port" to "11097"
  * Set "Require TLS" to "No"
  * Encoding must either be set to "Automatic" or "Binary"
  * Optional: Set "Allow Trading" to "Yes"
  * Optional: Set "Require Authentication" to "Yes"
  * Optional: If you have multiple installations of Sierra Chart, make sure that each installation has unique DTC ports.  For example, installation 1 uses ports 11099, 11097, and 11098, and installation 2 uses ports 11096, 11095, and 11094 for the Listening Port, Historical Data Port, and the TLS Historical Data Port, respectively.
  * Click OK.

If you need multiple instances of Sierra Chart to trade with two brokers at the same time, you will need a second installation of Sierra Chart on your computer.  To do this:
* Follow [these instructions](https://www.sierrachart.com/index.php?page=doc/NewInstance.php).
* Also, make sure that the DTC Ports are unique for every Sierra Chart installation on the same host.

## Configuring Zorro

### User field

The user field gets parsed for multiple arguments.  Each argument is separated by a space character.  The format is:
* "field1:value1 field2:value2"

For example, the user field can look like this:
* "sa:1234 ta:5678 h:127.0.0.1 p1:11099 p2:11097"

Fields:
* "sa" - Sierra Chart Account - only required if the DTC Server has "Require Authentication" checked. By default, this field is blank.
* "ta" - Trade Account - this is either your broker's account number or a simulated account on your Sierra Chart platform.  By default, "Sim1", a simulated account.
* "h" - DTC server hostname. Default value: "127.0.0.1" (localhost - the same computer)
* "p1" - Listening Port. Default value: "11099"
* "p2" - Historical Data Port. Default value: "11097"

To set all the fields to their default value, leave the user field completely blank.  This default configuration is compatible with the default DTC server settings shown above.

### Password field

This field is only required if the DTC Server has "Require Authentication" checked.

Simply input the password to your Sierra Chart account.

## Plugin Capabilities

The following standard Zorro Broker API functions have been implemented:

* BrokerOpen
* BrokerLogin
* BrokerTime
* BrokerAsset
* BrokerAccount
* BrokerHistory2
* BrokerBuy2 (orders only)
* BrokerTrade (orders only)
* BrokerCommand standard functions:
  * GET\_PRICETYPE
  * SET\_PRICETYPE
  * SET\_ORDERTYPE
  * GET\_WAIT
  * SET\_WAIT
  * GET\_MAXTICKS
  * SET\_SYMBOL
  * DO\_CANCEL
  * GET\_FUTURES
  * SET\_HWND



In addition, BrokerCommand supports some newly-defined functions:
* SC\_GET\_SNAPSHOT (must set SET\_SYMBOL first)
  * Input: Pointer to user-supplied SC\_SNAPSHOT struct for symbol set via SET\_SYMBOL.  Plugin will copy values to struct.
  * Returns 1 if successful, 0 if failure.
* SC\_GET\_SECURITYDEF (must set SET\_SYMBOL first)
  * Input: Pointer to user-supplied SC\_SECURITYDEF struct for symbol set via SET\_SYMBOL.  Plugin will copy values to struct.
  * Returns 1 if successful, 0 if failure.
* SC\_SET\_ORDERBLOCKMODE
  * Input: 1 to enable, 0 to disable. If enabled, Zorro will wait for an order to be filled before returning from enterLong/enterShort.
  * Returns 1 if successful, 0 if failure.

## Example Test Script
```c++
#include <default.c>
#define SC_GET_SNAPSHOT                6001
#define SC_GET_SECURITYDEF             6002
#define SC_SET_ORDERBLOCKMODE          6003 // 1: ENABLE, 0: DISABLE BLOCKING ON ORDER PLACEMENT
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
	unsigned char UpdatesBidAskOnly;
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

CONTRACT Cons[MAX_CONTRACTS];
void test_futures(){
	printf("\n------------");
	memset(Cons,0,MAX_CONTRACTS*sizeof(CONTRACT));
	string sym = "ES?##";
	brokerCommand(SET_SYMBOL,sym);
	int N = brokerCommand(GET_FUTURES,Cons);
	printf("\nReceived %d %s futures contracts via GET_FUTURES...",N,sym);
	int i;
	for(i=0;i<N;i++){
		CONTRACT* p = &Cons[i];
		printf("\n[%d] type: %d, m: %0.1f, ex: %d, str: %0.2f, ask: %0.2f, bid: %0.2f",
			i,
			p->Type,
			(var)p->fVal,
			p->Expiry,
			(var)p->fStrike,
			(var)p->fAsk,
			(var)p->fBid
			);
	}
	
	N = contractUpdate(sym,0,FUTURE);
	printf("\nReceived %d %s futures contracts via contractUpdate()...",N,sym);
	for(i=1;i<=N;i++){
		CONTRACT* p = contract(i);
		if(!p) continue;
		printf("\n[%d] type: %d, m: %0.1f, ex: %d, str: %0.2f, ask: %0.2f, bid: %0.2f",
			i,
			p->Type,
			(var)p->fVal,
			p->Expiry,
			(var)p->fStrike,
			(var)p->fAsk,
			(var)p->fBid
			);
	}
}
void test_dtcsecuritydef(){
	printf("\n------------");
	string sym = "ESM21";
	SC_SECURITYDEF d;
	memset(&d,0,sizeof(d));
	brokerCommand(SET_SYMBOL,sym);
	brokerCommand(SC_GET_SECURITYDEF,&d);
	printf("\nsSymbol: %s",d.sSymbol);
	printf("\nsDescription: %s",d.sDescription);
	printf("\nMinPriceIncrement: %0.6f",(var)d.MinPriceIncrement);
}
void test_snapshot(){
	printf("\n------------");
	string sym = "ESM21";
	SC_SNAPSHOT s;
	memset(&s,0,sizeof(s));
	brokerCommand(SET_SYMBOL,sym);
	brokerCommand(SC_GET_SNAPSHOT,&s);
	printf("\nSC symbol: %s",sym);
	printf("\nvBidPrice: %0.6f",s.vBidPrice);
	printf("\nvAskPrice: %0.6f",s.vAskPrice);
	printf("\nSessionVolume: %0.6f",s.SessionVolume);
	printf("\nTrading session date: %d",ymd(s.TradingSessionDate));
}


void main(void){
	set(LOGFILE);
	if(!Live){printf("\nPress [Trade]."); return;}
	test_futures();
	test_dtcsecuritydef();
	test_snapshot();
	printf("\nDone!");
}

```
## Known Issues

* The DTC server might sometimes refuse subscription requests, even when a given symbol can be subscribed to! The plugin attempts to work around this by repeatedly attempting to subscribe until a subscription is confirmed.
* GET_FUTURES subscribes to all available symbols for the given underlying symbol and returns information on the successfully subscribed symbols.  Take note of how many symbol subscriptions your data services permit.
* The DTC server might produce an invalid snapshot for a symbol if you're not subscribed to the given symbol!

## License

This project has an MIT-style license. See the LICENSE.md file for more details.

## Resources

* [The Zorro Project](http://zorro-project.com/)
  * [Manual](http://zorro-project.com/manual/)
  * [Broker API](http://zorro-project.com/manual/en/brokerplugin.htm)
  * [BrokerCommand](http://zorro-project.com/manual/en/brokercommand.htm)
* [Sierra Chart](http://www.sierrachart.com)
* [DTC Protocol](http://www.dtcprotocol.org)
* [Asio](https://think-async.com/Asio/)


## Contact Info

For any questions and inquiries, I can be reached via email:

* Andrew M. Dolder, P.E.
* Engineer
* VitalTrades LLC
* andrew@vitaltrades.com
