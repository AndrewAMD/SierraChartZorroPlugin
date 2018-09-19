# Sierra Chart Plugin for Zorro

This plugin works both as a broker plugin to Zorro Trading Automation and as a client to Sierra Chart in order to:
1) Get live market data, including market depth
2) Get historical market data
3) Trade algorithmically
4) Track your trading account

This plugin was written in Win32 C/C++ using Visual Studio 2017.

## Build Instructions

This plugin depends on the following libraries:

* Boost libraries, 1.67 or greater
  * Boost Asio (for asynchronous network communications)
  * Boost UUID (to generate order Client ID's)
* OpenSSL (for TLS 1.2 encryption)
* zlib (optional historical data compression)
* DTC Protocol library

Build in Visual Studio 2017 or greater, linking to the above dependencies.  This plugin must be compiled in 32-bit (x86) in order to be compatible with Zorro.

## Installation Instructions

To install the plugin, simply place the SierraChart.dll file in the Plugin folder where Zorro is installed.

## About Sierra Chart

Sierra Chart is a trading platform with support for many brokers.

Sierra Chart has a fully integrated DTC Server.  It has two dedicated ports:
1) One for all trading, current market data, account data, and position data.
2) One for all historical market data.

## Configuring Sierra Chart DTC Server

A Sierra Chart instance can be accessed locally or over the internet. This plugin only uses TLS encryption.  Unencrypted connections are not supported by this plugin.

To set up Sierra Chart's DTC Server:
* Open Sierra Chart
* Global Settings -> Data/Trade Service Settings
* SC Server Settings
  * Check "Enable DTC Protocol Server"
  * Check "Require TLS"
  * Encoding must either be set to "Automatic" or "Binary"
  * Optional: Check "Allow Trading"
  * Optional: Check "Require Authentication"
  * Optional: If you have multiple installations of Sierra Chart, make sure that each installation has unique DTC ports.  For example, installation 1 uses ports 11099, 11098, and 11097, and installation 2 uses ports 11096, 11095, and 11094 for the Listening Port, Historical Data Port, and the TLS Historical Data Port, respectively.
  * Optional: Allowed Incoming IP's should be set to "Local Computer Only", unless you plan on accessing this installation from another computer on the LAN (Local Subnet Only) or the Internet (Any IP).  (If you are opening the port to the interet, consider requiring authentication.)
  * Click OK.

Here are the "ideal default settings", for simply accessing the platform on your own computer:
![Ideal default settings](https://raw.githubusercontent.com/AndrewAMD/gist/master/images/screenshots/0001.JPG)

If you need multiple instances of Sierra Chart to trade with two brokers at the same time, you will need a second installation of Sierra Chart on your computer.  Do do this:
* Follow [these instructions](https://www.sierrachart.com/index.php?page=doc/NewInstance.php).
* Also, make sure that the DTC Ports are unique for every Sierra Chart installation on the same host.

## Configuring Zorro

The user field gets parsed for multiple arguments.  Each argument is separated by a space character.  The format is:
* "field1:value1 field2:value2"

For example, the user field can look like this:
* "sa:1234 ta:5678 h:127.0.0.1 p1:11099 p2:11097 zlib"

Fields:
* "sa" - Sierra Chart Account - only required if the DTC Server has "Require Authentication" checked. By default, this field is blank.
* "ta" - Trade Account - this is either your broker's account number or a simulated account on your Sierra Chart platform.  By default, "Sim1", a simulated account.
* "h" - DTC server hostname. Default value: "127.0.0.1" (localhost - the same computer)
* "p1" - Listening Port. Default value: "11099"
* "p2" - TLS Historical Data Port. Default value: "11097"
* "zlib" - If this flag is provided, zlib will be enabled for transfer of historical data.  By default, disabled.  This setting reduces bandwidth between Zorro and the DTC server, but it increases the processing load.

To set all the fields to their default value, leave the user field completely blank.  This configuration is compatible with the default DTC server settings shown above.

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
  * GET\_MAXTICKS
  * SET\_HWND
  * SET\_SYMBOL
  * GET\_VOLTYPE
  * SET\_VOLTYPE
  * GET\_PRICETYPE
  * SET\_PRICETYPE
  * SET\_ORDERTYPE
  * GET\_UUID
  * SET\_UUID
  * GET\_POSITION
  * GET\_COMPLIANCE
  * SET\_PATCH


In addition, BrokerCommand supports some newly-defined functions:
* SET\_DIVIDEND\_ADJ
  * Input: 1 for dividend-adjusted historical data, 0 for unadjusted historical data.
  * Returns 1 if command accepted, 0 if rejected.
* GET\_DTCSECURITYDEF
  * Input: Pointer to a DTCSECURITYDEF struct. GET\_DTCSECURITYDEF will look up a Security with symbol set with SET_SYMBOL.  The DTCSECURITYDEF struct will be filled with the original values from the DTC server.
  * Returns: 1 if operation was successful, 0 if failed.
```c++
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
```

## Known Issues
* As of this writing, it is not possible to support standard broker commands GET_FUTURES and GET_OPTIONS.  This will be possible as soon as Sierra Chart supports getting symbols by underlying.  Per my discussions with their support, it is likely they will support acquiring futures symbols and not options symbols.  As a workaround to this, search for the individual symbols directly using the GET_DTCSECURITYDEF BrokerCommand.  

## License

This project has an MIT-style license. See the LICENSE.md file for more details.

## Resources

* [The Zorro Project](http://zorro-project.com/)
  * [Manual](http://zorro-project.com/manual/)
  * [Broker API](http://zorro-project.com/manual/en/brokerplugin.htm)
  * [BrokerCommand](http://zorro-project.com/manual/en/brokercommand.htm)
* [Sierra Chart](http://www.sierrachart.com)
* [DTC Protocol](http://www.dtcprotocol.com)
* [Boost](https://www.boost.org)
  * [Boost Asio](https://www.boost.org/doc/libs/1_68_0/doc/html/boost_asio.html)
  * [Boost UUID](https://www.boost.org/doc/libs/1_68_0/libs/uuid/doc/index.html)
* [OpenSSL](https://www.openssl.org)
* [zlib](https://www.zlib.net)

## Contact Info

For any questions and inquiries, I can be reached via email:

* Andrew M. Dolder
* andrew@vitaltrades.com
