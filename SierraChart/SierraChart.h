#pragma once

#include <windows.h>  // FARPROC

typedef double DATE;			//prerequisite for using trading.h
#include "zorro_include/trading.h"	// enter your path to trading.h (in your Zorro folder)


#ifdef SIERRACHART_EXPORTS
#define DLLFUNC extern "C" __declspec(dllexport)
#else  
#define DLLFUNC extern "C" __declspec(dllimport)
#endif  

// zorro functions, as defined here:
// http://zorro-project.com/manual/en/brokerplugin.htm
// http://zorro-project.com/manual/en/brokercommand.htm
DLLFUNC int BrokerOpen(char* Name, FARPROC fpError, FARPROC fpProgress);
DLLFUNC int BrokerLogin(char* User, char* Pwd, char* Type, char* Accounts);
DLLFUNC int BrokerTime(DATE *pTimeGMT);
DLLFUNC int BrokerAsset(char* ZorroAsset, double *pPrice, double *pSpread, double *pVolume, double *pPip, double *pPipCost, double *pLotAmount, double *pMarginCost, double *pRollLong, double *pRollShort);
DLLFUNC int BrokerHistory2(char* ZorroAsset, DATE tStart, DATE tEnd, int nTickMinutes, int nTicks, T6* ticks);
DLLFUNC int BrokerAccount (char* Account, double *pBalance, double *pTradeVal, double *pMarginVal);
DLLFUNC int BrokerBuy2(char* ZorroAsset, int Amount, double StopDist, double Limit, double *pPrice, int *pFill);
DLLFUNC int BrokerTrade(int nTradeID, double *pOpen, double *pClose, double *pRoll, double *pProfit);
DLLFUNC double BrokerCommand(int Command, DWORD dwParameter);

