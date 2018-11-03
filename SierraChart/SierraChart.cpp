// SierraChart.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Engine.h"
#define  SIERRACHART_EXPORTS // SierraChart.h prerequisite
#include "SierraChart.h"

namespace cro = std::chrono;
namespace asio = boost::asio;
using error_code = boost::system::error_code;
using namespace DTC;
using namespace DTCTools;



// *** EXTERNAL FUNCTIONS ***

DLLFUNC int BrokerOpen(char* Name, FARPROC fpError, FARPROC fpProgress)
{
	strcpy_s(Name, 32, "SierraChart");
	(FARPROC&)BrokerError = fpError;
	(FARPROC&)BrokerProgress = fpProgress;
	return PLUGIN_VERSION;
}

DLLFUNC int BrokerLogin(char* User, char* Pwd, char* Type, char* Accounts)
{
	c.reset(); // kill session if applicable
	if (!User) return 0;
	
	parsing::parse(User);
	if(Pwd) pw = Pwd;
	else pw = "";
	if (!Type) isLive = false;
	if (((std::string)Type) == ((std::string)"Real")) isLive = true;
	else isLive = false;
	{
		socket_config conf;
		conf.hb_interval_s = HEARTBEAT1_S;
		conf.id = 1;
		conf.host = h;
		conf.port = p1;
		conf.ssl = DEFAULT_TLS_ENABLED;
		conf.zlib = zlib_enabled;
		conf.timeout_ms = 10000;
		conf.tradeaccount = tradeaccount_main;
		conf.logon_request.HeartbeatIntervalInSeconds = HEARTBEAT1_S;
		conf.logon_request.SetUsername(user.c_str());
		conf.logon_request.SetPassword(pw.c_str());
		c = std::make_unique<client>(conf); // new session
	}
	int ret = c->zt_BrokerLogin(Accounts);
	c->zt_print_errors();
	if (!ret) c.reset();
	return ret;
}

DLLFUNC int BrokerTime(DATE *pTimeGMT)
{
	if (!c) return 0;
	if (c->stopped) return 0;
	c->zt_print_errors();
	return 2;
}

DLLFUNC int BrokerAsset(char* ZorroAsset, double *pPrice, double *pSpread, double *pVolume, 
	double *pPip, double *pPipCost, double *pLotAmount, double *pMarginCost, 
	double *pRollLong, double *pRollShort)
{
	if (!c) return 0;
	if (c->stopped) return 0;
	c->zt_print_errors();
	return c->zt_BrokerAsset(ZorroAsset, pPrice, pSpread, pVolume, pPip, pPipCost, pLotAmount, pMarginCost, pRollLong, pRollShort);
}

DLLFUNC int BrokerAccount(char* Account, double *pBalance, double *pTradeVal, double *pMarginVal)
{
	if (!c) return 0;
	if (c->stopped) return 0;
	c->zt_print_errors();
	return c->zt_BrokerAccount(Account, pBalance, pTradeVal, pMarginVal);

}
DLLFUNC int BrokerBuy2(char* ZorroAsset, int Amount, double StopDist, double Limit, double *pPrice, int *pFill)
{
	if (!c) return 0;
	if (c->stopped) return 0;
	c->zt_print_errors();

	return c->zt_BrokerBuy2(ZorroAsset, Amount, StopDist, Limit, pPrice, pFill);
}
DLLFUNC int BrokerTrade(int nTradeID, double *pOpen, double *pClose, double *pRoll, double *pProfit)
{
	if (!c) return 0;
	if (c->stopped) return 0;
	c->zt_print_errors();

	return c->zt_BrokerTrade(nTradeID, pOpen, pClose, pRoll, pProfit);
}

DLLFUNC int BrokerHistory2(char* ZorroAsset, DATE tStart, DATE tEnd, int nTickMinutes, int nTicks, T6* ticks)
{
	if (!c) return 0;
	if (c->stopped) return 0;
	s_SecurityDefinitionResponse* def = c->can_define(ZorroAsset);
	if (!def) return 0;
	
	socket_config conf;
	conf.hb_interval_s = HEARTBEAT2_S;
	conf.id = 2;
	conf.host = h;
	conf.port = p2;
	conf.ssl = DEFAULT_TLS_ENABLED;
	conf.zlib = zlib_enabled;
	conf.timeout_ms = 300000; // Five minutes. Need to be generous for large downloads.  There are no hearbeats!!
	conf.tradeaccount = tradeaccount_main;
	conf.logon_request.HeartbeatIntervalInSeconds = HEARTBEAT2_S;
	conf.logon_request.SetUsername(user.c_str());
	conf.logon_request.SetPassword(pw.c_str());
	client h(conf); // temporary session
	int ret = h.zt_BrokerHistory2(def, tStart, tEnd, nTickMinutes, nTicks, ticks);
	h.zt_print_errors();
	return ret;
}


DLLFUNC double BrokerCommand(int Command, DWORD dwParameter)
{
	switch (Command) 
	{
	case GET_MAXTICKS:
		return HISTORY_MAXIMUM_TICKS;
	case SET_HWND:
		hWindow = (HWND)dwParameter;
		return 1;
	case SET_SYMBOL:
		symbol = (const char*)dwParameter;
		return 1;
	case GET_VOLTYPE:
		return voltype;
	case SET_VOLTYPE:
		switch ((int)dwParameter)
		{
		case VOLTYPE_SESSION_VOLUME:
		case VOLTYPE_SESSION_NUMTRADES:
		case VOLTYPE_SESSION_NO_VOLUME:
			voltype = (int)dwParameter;
			return 1;
		default:
			return 0;
		}
	case GET_PRICETYPE:
		return pricetype;
	case SET_PRICETYPE:
		switch ((int)dwParameter)
		{
		case PRICETYPE_ASKBID:
		case PRICETYPE_TRADES:
			pricetype = (int)dwParameter;
			return 1;
		default:
			return 0;
		}
	case SET_ORDERTYPE: // 0 = fill-or-kill, 1 = immediate-or-cancel, 2 = good-till-cancelled 
		switch ((int)dwParameter)
		{
		case ORDERTYPE_FILLORKILL:
		case ORDERTYPE_IMMEDIATEORCANCEL:
		case ORDERTYPE_GOODTILLCANCELED:
			ordertype = (int)dwParameter;
			return 1;
		default:
			return 0;
		}
		return 0;
	case GET_UUID:
		strcpy_s((char*)dwParameter, 64, uuid.c_str());
		return 1;
	case SET_UUID:
		uuid = (const char*)dwParameter;
		return 1;
	case GET_POSITION:
		return c->zt_get_position((char*)dwParameter);
	case GET_COMPLIANCE:
	{
		int output = 0;
		//output += 1; // no partial closing ... not applicable.
		output += 2; // no hedging
		//output += 4; // FIFO compliance ... not applicable.
		output += 8; // no closing of trades
		return output;
	}
	case GET_BOOK:
		return c->zt_get_book((T2*)dwParameter);

	//case GET_OPTIONS:
	//	// TODO: support GET_OPTIONS
	//	return 0;

	//case GET_FUTURES:
	//	// TODO: support GET_FUTURES
	//	return 0;
	//case GET_UNDERLYING:
	//	// TODO: support GET_UNDERLYING
	//	return 0;
	case SET_PATCH:
		patch = (int)dwParameter;
		return 1;
	case SET_DIVIDEND_ADJ:
	{
		int setting = (int)dwParameter;
		if (setting == 0) {
			dividend_adjusted = false;
			return 1;
		}
		else if (setting == 1) {
			dividend_adjusted = true;
			return 1;
		}
		else return 0;
	}
	case GET_DTCSECURITYDEF:
	{
		if (!c) return 0;
		if (c->stopped) return 0;
		s_SecurityDefinitionResponse* d = c->can_define((char*)symbol.c_str());
		if (!d) return 0;

		DTCSECURITYDEF* o = (DTCSECURITYDEF*)dwParameter;
		if (!o) return 0;
		memset(o, 0, sizeof(DTCSECURITYDEF));
		strcpy_s(o->Symbol, 64, d->Symbol);
		strcpy_s(o->Exchange, 16, d->Exchange);
		o->SecurityType = d->SecurityType;
		strcpy_s(o->Description, 64, d->Description);
		o->MinPriceIncrement = d->MinPriceIncrement;
		o->PriceDisplayFormat = d->PriceDisplayFormat;
		o->CurrencyValuePerIncrement = d->CurrencyValuePerIncrement;
		o->FloatToIntPriceMultiplier = d->FloatToIntPriceMultiplier;
		o->IntToFloatPriceDivisor = d->IntToFloatPriceDivisor;
		strcpy_s(o->UnderlyingSymbol, 32, d->UnderlyingSymbol);
		if (d->UpdatesBidAskOnly) o->UpdatesBidAskOnly = true;
		else o->UpdatesBidAskOnly = false;
		o->StrikePrice = d->StrikePrice;
		o->PutOrCall = d->PutOrCall;
		o->ShortInterest = d->ShortInterest;
		o->SecurityExpirationDate = d->SecurityExpirationDate;
		o->BuyRolloverInterest = d->BuyRolloverInterest;
		o->SellRolloverInterest = d->SellRolloverInterest;
		o->EarningsPerShare = d->EarningsPerShare;
		o->SharesOutstanding = d->SharesOutstanding;
		o->IntToFloatQuantityDivisor = d->IntToFloatQuantityDivisor;
		if (d->HasMarketDepthData) o->HasMarketDepthData = true;
		else o->HasMarketDepthData = false;
		o->DisplayPriceMultiplier = d->DisplayPriceMultiplier;
		strcpy_s(o->ExchangeSymbol, 64, d->ExchangeSymbol);
		o->InitialMarginRequirement = d->InitialMarginRequirement;
		o->MaintenanceMarginRequirement = d->MaintenanceMarginRequirement;
		strcpy_s(o->Currency, 8, d->Currency);
		return 1;
	}

	
	default:
		return 0;
	
	} //switch
}

