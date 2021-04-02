#include "pch.h"
#include "framework.h"
#include "SierraChart2.h"
#include "StrBufs.h"
#include "client.h"

#include "zorro_incl.h"
#include <exception>
#include <vector>
#include "Time.h"

#include "banned.h" //must include last

//globals
std::map<std::string, s_OrderUpdate> g_mOrders;
std::map<std::string, s_Asset> g_mAssets;
std::map<std::string, s_AccountBalanceUpdate> g_mBalances;
std::string g_sUser;
std::string g_sPwd;
std::string g_sTradeaccountSelected;
std::string g_sHost;
std::string g_sPortMain;
std::string g_sPortHist;
char g_Symbol[SYMBOL_LENGTH];
int g_PriceType = 1;
TimeInForceEnum g_TimeInForce = TIF_DAY;
int g_OrderBlockMode = 1;
int g_nLastTradeID = 1;
int g_OrderWait_ms = 60000;
bool g_BeQuiet = false; // for special occasions where the output is too verbose


int new_TradeID() {return g_nLastTradeID = max(2, g_nLastTradeID + 1);}
const char* new_ClientOrderID(int nTradeID) {return strf("%08d-%d", get_todays_date_yyyymmdd(), nTradeID);}
int get_TradeID(const char* sClientOrderID) {
	//format: YYYYMMDD-nTradeID, e.g. "20210327-1234"
	const char* p = strstr(sClientOrderID,"-");
	if (!p) return 0;
	return atoi(p + 1);
}
s_OrderUpdate* get_order_by_ServerOrderID(const char* ServerOrderID) {
	if (!ServerOrderID)return NULL;
	if (!strlen(ServerOrderID))return NULL;
	auto& o = g_mOrders[ServerOrderID];
	return &o;
}
s_OrderUpdate* get_order_by_ClientOrderID(const char* ClientOrderID) {
	for (auto& o : g_mOrders) {
		if (!strcmp(o.second.ClientOrderID, ClientOrderID)) {
			return &o.second;
		}
	}
	return NULL;
}
s_OrderUpdate* get_order_by_TradeID(int nTradeID) {
	for (auto& o : g_mOrders) {
		if (nTradeID == get_TradeID(o.second.ClientOrderID)) {
			return &o.second;
		}
	}
	return NULL;
}
s_Asset* get_asset_by_SCSymbol(const char* SCSymbol) {
	for (auto& a : g_mAssets) {
		if (a.first == SCSymbol) {
			return &a.second;
		}
	}
	s_Asset* pA = &g_mAssets[SCSymbol];
	pA->SCSymbol = SCSymbol;
	define(pA);
	if (pA->is_defined)return pA;
	g_mAssets.erase(SCSymbol);
	return NULL;
}
s_Asset* get_asset_by_SymbolID(uint32_t SymbolID) {
	for (auto& a : g_mAssets) {
		if (a.second.SymbolID == SymbolID) {
			return &a.second;
		}
	}
	return NULL;
}
s_Asset* get_asset_by_ZorroSymbol(const char* ZorroSymbol) {
	if (strstr(ZorroSymbol, "-FUT-")) { 
		for (auto& a : g_mAssets) {
			if (a.second.ZorroSymbol == ZorroSymbol) {
				return &a.second;
			}
		}
		return NULL;
	}
	else {
		return get_asset_by_SCSymbol(ZorroSymbol);
	}
}


DLLFUNC int BrokerOpen(char* Name, void* fpError, void* fpProgress) {
	strcpy_s(Name, 32, "SierraChart");
	if (fpError)(void*&)BrokerError = fpError;
	if (fpProgress)(void*&)BrokerProgress = fpProgress;
	return PLUGIN_VERSION;
}

bool ubc_encoding(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	bool* pIsGood = (bool*)pAuxiliary;
	switch (Type) {
	case ENCODING_RESPONSE: {
		s_EncodingResponse m;
		m.CopyFrom(pMsg);
		switch (m.Encoding) {
		case BINARY_ENCODING: *pIsGood = true;
		}
		return true;
	}//LOGON_RESPONSE
	}//switch
	return false;
}

bool ubc_login(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	auto pLr = (s_LogonResponse*)pAuxiliary;
	switch (Type) {
	case LOGON_RESPONSE:
		pLr->CopyFrom(pMsg);
		return true;
	}//switch
	return false;
}

struct s_ta_list {
	int num_tradeaccounts;
	char ta_list[32][32];
};

bool ubc_check_tradeaccount(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	s_ta_list* pTaList = (s_ta_list*)pAuxiliary;
	switch (Type) {
	case TRADE_ACCOUNT_RESPONSE: {
		s_TradeAccountResponse re;
		re.CopyFrom(pMsg);
		if (strlen(re.TradeAccount)) {
			strcpy_s(&pTaList->ta_list[pTaList->num_tradeaccounts][0], 32, re.TradeAccount);
			pTaList->num_tradeaccounts++;
		}
		if (re.MessageNumber == re.TotalNumberMessages) return true;
	}//TRADE_ACCOUNT_RESPONSE
	}//switch
	return false;
}

bool ubc_exchangeresponse(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	switch (Type) {
	case EXCHANGE_LIST_RESPONSE: {
		s_ExchangeListResponse re;
		re.CopyFrom(pMsg);
		if (strlen(re.Exchange)) {
			zprintf("Detected exchange: %s", re.Exchange);
		}
		else {
			zprintf("no exchanges supplied by DTC server");
		}
		if (re.IsFinalMessage) {
			return true;
		}
	}//EXCHANGE_LIST_RESPONSE
	}//switch
	return false;
}
bool ubc_symbolsforexchange(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	switch (Type) {
	case SECURITY_DEFINITION_RESPONSE: {
		s_SecurityDefinitionResponse re;
		re.CopyFrom(pMsg);
		if (strlen(re.Symbol)) {
			zprintf("Detected symbol: %s", re.Symbol);
		}
		else {
			zprintf("no exchanges supplied by DTC server");
		}
		if (re.IsFinalMessage) {
			return true;
		}
	}//SECURITY_DEFINITION_RESPONSE
	case SECURITY_DEFINITION_REJECT: {
		s_SecurityDefinitionReject re;
		re.CopyFrom(pMsg);
		zprintf("\"%s\"", re.RejectText);
		return true;
	}//SECURITY_DEFINITION_RESPONSE
	}//switch
	return false;
}


bool ubc_openorders(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	switch (Type) {
	case ORDER_UPDATE: {
		s_OrderUpdate re;
		re.CopyFrom(pMsg);
		g_nLastTradeID = max(g_nLastTradeID, get_TradeID(re.ClientOrderID));
		if (re.RequestID== request_id && re.TotalNumMessages == re.MessageNumber)return true;
	}//ORDER_UPDATE
	case OPEN_ORDERS_REJECT: {
		s_OpenOrdersReject re;
		re.CopyFrom(pMsg);
		zprintf("\"%s\"", re.RejectText);
		return true;
	}//OPEN_ORDERS_REJECT 
	}//switch
	return false;
}


DLLFUNC int BrokerLogin(char* User, char* Pwd, char* Type, char* Accounts) {
	try {
		if (!User) {
			zprintf("Logging out...");
			cl_reset_all();
			return 0;
		}

		// set default values
		g_sUser = DEFAULT_USERNAME;
		if(Pwd)g_sPwd = Pwd;
		g_sTradeaccountSelected = DEFAULT_ACCOUNT;
		g_sHost = DEFAULT_HOST;
		g_sPortMain = DEFAULT_PORT1;
		g_sPortHist = DEFAULT_PORT2;

		{
			char user[1024] = { 0 };
			strcpy_s(user, User);
			User = user;
			char* tctx = NULL;
			char* s = NULL;
			for (; s = strtok_s(User, " ", &tctx);) {
				if (User)User = NULL;
				if (strstr(s, "sa:")) {// Sierra Account
					g_sUser = s + 3;
				}
				if (strstr(s, "ta:")) {// Trade Account
					g_sTradeaccountSelected = s + 3;
				}
				if (strstr(s, "h:")) {// hostname
					g_sHost = s + 2;
				}
				if (strstr(s, "p1:")) {// port 1 (main)
					g_sPortMain = s + 3;
				}
				if (strstr(s, "p2:")) {// port 2 (history)
					g_sPortHist = s + 3;
				}
			}
		}
		const char* const sN = FeedNames[FEED_MAIN];
		{
			zprintf("%s: Connecting to %s:%s...", sN, g_sHost.c_str(), g_sPortMain.c_str());
			cl_connect(FEED_MAIN, g_sHost.c_str(), g_sPortMain.c_str());
			if (cl_is_stopped(FEED_MAIN)) { return 0; }
		}
		{
			zprintf("%s: Requesting binary encoding...", sN);
			bool is_binary = false;
			s_EncodingRequest er;
			er.Encoding = BINARY_ENCODING;
			cl_send(FEED_MAIN, &er, er.Size);
			cl_block(ubc_encoding, FEED_MAIN, 0, &is_binary);
			if (cl_is_stopped(FEED_MAIN)) { return 0; }
			if (!is_binary) {
				zprintf("%s: Server does not support binary encoding!", sN);
				return 0;
			}
		}
		{
			zprintf("%s: Sending Logon Request...", sN);
			s_LogonRequest lr;
			lr.HeartbeatIntervalInSeconds = HEARTBEAT_SECONDS;
			lr.SetClientName("ZorroSCPlugin");
			lr.SetUsername(g_sUser.c_str());
			if (Pwd)lr.SetPassword(Pwd);
			lr.SetTradeAccount(g_sTradeaccountSelected.c_str());
			cl_send(FEED_MAIN, &lr, lr.Size);
			s_LogonResponse lre;
			cl_block(ubc_login, FEED_MAIN, 0, &lre);
			if (cl_is_stopped(FEED_MAIN)) { return 0; }
			zprintf("%s: \"%s\"", sN, lre.ResultText);
			if (lre.Result != LOGON_SUCCESS) {
				zprintf("%s: Logon failure", sN);
				cl_shutdown(FEED_MAIN);
				return 0;
			}
			zprintf("%s: ProtocolVersion: %d", sN, lre.ProtocolVersion);
			if (!lre.MarketDataSupported) {
				zprintf("%s: Warning: This server does not support market data.", sN);
			}
			if (!lre.TradingIsSupported) {
				zprintf("%s: Warning: This server does not support trading.", sN);
			}
		}
		{
			s_TradeAccountsRequest tarq;
			tarq.RequestID = new_request_id();
			cl_send(FEED_MAIN, &tarq, tarq.Size);
			s_ta_list tal = { 0 };
			cl_block(ubc_check_tradeaccount, FEED_MAIN, tarq.RequestID, &tal);
			if (cl_is_stopped(FEED_MAIN)) { return 0; }
			strcpy_s(Accounts, 1024, strf("%s ", g_sTradeaccountSelected.c_str()));
			bool is_match = false;
			for (int i = 0; i < tal.num_tradeaccounts; i++) {
				char* this_ta = &tal.ta_list[i][0];
				zprintf("TradeAccount detected: %s", this_ta);
				if (!strcmp(this_ta, g_sTradeaccountSelected.c_str())) {
					is_match = true;
				}
				else {
					strcat_s(Accounts, 1024, strf("%s ", this_ta));
				}
				s_AccountBalanceRequest abr;
				abr.RequestID = new_request_id();
				abr.SetTradeAccount(this_ta);
				cl_send(FEED_MAIN, &abr, abr.Size);
				cl_drain();
			}
			if (!is_match) {
				zprintf("TradeAccount %s not found!", g_sTradeaccountSelected.c_str());
				cl_shutdown(FEED_MAIN);
				return 0;
			}
			strcat_s(Accounts, 1024, " ");
			int len = (int)strlen(Accounts);
			for (int i = 0; i < len; i++) {
				if (Accounts[i] == ' ')Accounts[i] = '\0';
			}
			zprintf("Using TradeAccount: %s", g_sTradeaccountSelected.c_str());
		}

		{
			s_OpenOrdersRequest rq;
			rq.RequestID = new_request_id();
			rq.RequestAllOrders = 1;
			cl_send(FEED_MAIN, &rq, rq.Size);
			cl_block(ubc_openorders, FEED_MAIN, rq.RequestID, NULL);
		}

		return 1;
	}
	catch (std::exception const& e) {
		zprintf("BrokerLogin error: %s", e.what());
		return 0;
	}

}

bool ubc_define(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	s_Asset* pAsset = (s_Asset*)pAuxiliary;
	switch (Type) {
	case SECURITY_DEFINITION_RESPONSE: {
		s_SecurityDefinitionResponse re;
		re.CopyFrom(pMsg);
		if (!strcmp(pAsset->SCSymbol.c_str(),re.Symbol)) {
			pAsset->definition = re;
			pAsset->is_defined = true;
			if (re.MinPriceIncrement && re.MinPriceIncrement != DBL_MAX) {
				pAsset->vPip = 1 / re.MinPriceIncrement;
			}
			if (re.SecurityExpirationDate) {
				pAsset->nExpiry = vEpochSeconds_to_todays_date_yyyymmdd(re.SecurityExpirationDate);
			}
		}
		if (re.IsFinalMessage) {
			return true;
		}
	}//SECURITY_DEFINITION_RESPONSE
	case SECURITY_DEFINITION_REJECT: {
		s_SecurityDefinitionReject re;
		re.CopyFrom(pMsg);
		zprintf("Rejected: \"%s\"", re.RejectText);
		return true;
	}//SECURITY_DEFINITION_RESPONSE
	}//switch
	return false;
}
void define(s_Asset* pAsset) {
	s_SecurityDefinitionForSymbolRequest rq;
	rq.RequestID = new_request_id();
	rq.SetSymbol(pAsset->SCSymbol.c_str());
	cl_send(FEED_MAIN, &rq, rq.Size);
	cl_block(ubc_define, FEED_MAIN, rq.RequestID, pAsset);
}

bool ubc_subscribe(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	s_Asset* pAsset = (s_Asset*)pAuxiliary;
	switch (Type) {
	case MARKET_DATA_SNAPSHOT: {
		s_MarketDataSnapshot re;
		re.CopyFrom(pMsg);
		if (re.SymbolID == pAsset->SymbolID && (re.BidPrice || re.AskPrice || re.LastTradePrice)) {
			pAsset->is_subscribed = true;
			return true;
		}
	}//MARKET_DATA_SNAPSHOT
	case MARKET_DATA_REJECT: {
		s_MarketDataReject re;
		re.CopyFrom(pMsg);
		if (re.SymbolID == pAsset->SymbolID) {
			pAsset->is_subscribed = false;
			if (!g_BeQuiet) {
				if (strlen(re.RejectText))zprintf("Rejected: \"%s\"", re.RejectText);
				else zprintf("Rejected.");
			}
			return true;
		}
	}//MARKET_DATA_REJECT
	}//switch
	return false;
}



DLLFUNC int BrokerAsset(
	char* ZorroSymbol, double* pPrice, double* pSpread, double* pVolume,
	double* pPip, double* pPipCost, double* pLotAmount,
	double* pMarginCost, double* pRollLong, double* pRollShort)
{
	try {
		cl_drain();
		if (cl_is_stopped(FEED_MAIN)) {
			zprintf("BrokerAsset: stopped");
			return 0;
		}
		s_Asset* pAsset = get_asset_by_ZorroSymbol(ZorroSymbol);
		if (!pAsset)return 0;

		if (!pPrice && !pAsset->is_subscribed) { //subscribe
			{
				s_MarketDataRequest rq;
				rq.SymbolID = pAsset->SymbolID = new_request_id();
				rq.RequestAction = SUBSCRIBE;
				rq.SetSymbol(pAsset->SCSymbol.c_str());
				cl_send(FEED_MAIN, &rq, rq.Size);
				cl_block(ubc_subscribe, FEED_MAIN, 0, pAsset);
				if (!pAsset->is_subscribed) {
					if(!g_BeQuiet)zprintf("%s: subscription failed!", pAsset->SCSymbol.c_str());
					return 0;
				}
			}
			pAsset->is_subscribed = true;
			{
				s_MarketDepthRequest rq;
				rq.SymbolID = pAsset->SymbolID;
				rq.RequestAction = SUBSCRIBE;
				rq.SetSymbol(pAsset->SCSymbol.c_str());
				cl_send(FEED_MAIN, &rq, rq.Size);
				cl_drain(); // no need to block for market depth
			}
			if (pPrice && pAsset->vPrice != 0)           *pPrice = pAsset->vPrice;
			if (pSpread && pAsset->vSpread != 0)         *pSpread = pAsset->vSpread;
			if (pVolume && pAsset->vVolume != 0)         *pVolume = pAsset->vVolume;
			if (pPip && pAsset->vPip != 0)               *pPip = pAsset->vPip;
			if (pPipCost && pAsset->vPipCost != 0)       *pPipCost = pAsset->vPipCost;
			//if (pLotAmount && pAsset->vLotAmount != 0)   *pLotAmount = pAsset->vLotAmount;
			if (pMarginCost && pAsset->vMarginCost != 0) *pMarginCost = pAsset->vMarginCost;
			if (pRollLong && pAsset->vRollLong != 0)     *pRollLong = pAsset->vRollLong;
			if (pRollShort && pAsset->vRollShort != 0)   *pRollShort = pAsset->vRollShort;
			
			return 1;
		}//subscribe

		if (pPrice && pAsset->vPrice != 0)           *pPrice = pAsset->vPrice;
		if (pSpread && pAsset->vSpread != 0)         *pSpread = pAsset->vSpread;
		if (pVolume && pAsset->vVolume != 0)         *pVolume = pAsset->vVolume;
		if (pPip && pAsset->vPip != 0)               *pPip = pAsset->vPip;
		if (pPipCost && pAsset->vPipCost != 0)       *pPipCost = pAsset->vPipCost;
		//if (pLotAmount && pAsset->vLotAmount != 0)   *pLotAmount = pAsset->vLotAmount;
		if (pMarginCost && pAsset->vMarginCost != 0) *pMarginCost = pAsset->vMarginCost;
		if (pRollLong && pAsset->vRollLong != 0)     *pRollLong = pAsset->vRollLong;
		if (pRollShort && pAsset->vRollShort != 0)   *pRollShort = pAsset->vRollShort;

		return 1;
	}
	catch (std::exception const& e) {
		zprintf("BrokerAsset error: %s", e.what());
		return 0;
	}
}

DLLFUNC int BrokerTime(DATE* pTimeGMT) {
	try {
		cl_drain();
		if (cl_is_stopped(FEED_MAIN)) {
			return 0;
		}

		return 2; // Cannot detect market status.
	}
	catch (std::exception const& e) {
		zprintf("BrokerTime error: %s", e.what());
		return 0;
	}
}
DLLFUNC int BrokerAccount(const char* Account,
	double* pBalance, double* pTradeVal, double* pMarginVal) {
	try {
		cl_drain();
		if (cl_is_stopped(FEED_MAIN)) {
			zprintf("BrokerAccount: 'stopped' detected!");
			return 0;
		}
		if (!Account) {
			Account = g_sTradeaccountSelected.c_str();
		}
		auto& bal = g_mBalances[Account];
		//if (pBalance)*pBalance = bal.CashBalance;
		if (pTradeVal)*pTradeVal = bal.SecuritiesValue;
		if (pMarginVal)*pMarginVal = bal.MarginRequirement;
		return 1;
	}
	catch (std::exception const& e) {
		zprintf("BrokerAccount error: %s", e.what());
		return 0;
	}
}

struct s_HistData {
	s_HistoricalPriceDataRequest rq;
	s_HistoricalPriceDataResponseHeader hdr;
	s_HistoricalPriceDataReject rj;
	std::vector<s_HistoricalPriceDataRecordResponse> vBars;
	std::vector<s_HistoricalPriceDataTickRecordResponse> vTicks;
	s_HistData() {
		vBars.reserve(1024);
		vTicks.reserve(1024);
	}
};
bool ubc_gethist(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	s_HistData* p = (s_HistData*)pAuxiliary;
	switch (Type) {
	case HISTORICAL_PRICE_DATA_RESPONSE_HEADER: {
		s_HistoricalPriceDataResponseHeader re;
		re.CopyFrom(pMsg);
		p->hdr = re;
		if (re.NoRecordsToReturn) {
			zprintf("No records to return");
			return true;
		}
		return false;
	}//HISTORICAL_PRICE_DATA_RESPONSE_HEADER
	case HISTORICAL_PRICE_DATA_REJECT: {
		s_HistoricalPriceDataReject  re;
		re.CopyFrom(pMsg);
		p->rj = re;
		zprintf("History download rejected: \"%s\"", re.RejectText);
		return true;
	}//HISTORICAL_PRICE_DATA_REJECT 
	case HISTORICAL_PRICE_DATA_RECORD_RESPONSE: {
		s_HistoricalPriceDataRecordResponse  re;
		re.CopyFrom(pMsg);
		if (p->vBars.capacity() == p->vBars.size()) {
			p->vBars.reserve(p->vBars.capacity() * 2);
		}
		p->vBars.push_back(re);
		if (re.IsFinalRecord)return true;
		return false;
	}//HISTORICAL_PRICE_DATA_RECORD_RESPONSE
	case HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE: {
		s_HistoricalPriceDataTickRecordResponse  re;
		re.CopyFrom(pMsg);
		re.CopyFrom(pMsg);
		if (p->vTicks.capacity() == p->vTicks.size()) {
			p->vTicks.reserve(p->vTicks.capacity() * 2);
		}
		p->vTicks.push_back(re);
		if (re.IsFinalRecord)return true;
		return false;
	}//HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE 
	}//switch
	return false;
}
void get_history(s_HistData* pHD) {
	const char* const sN = FeedNames[FEED_HIST];
	{
		cl_connect(FEED_HIST, g_sHost.c_str(), g_sPortHist.c_str());
		if (cl_is_stopped(FEED_HIST)) { return; }
	}
	{
		bool is_binary = false;
		s_EncodingRequest er;
		er.Encoding = BINARY_ENCODING;
		cl_send(FEED_HIST, &er, er.Size);
		cl_block(ubc_encoding, FEED_HIST, 0, &is_binary);
		if (cl_is_stopped(FEED_HIST)) { return; }
		if (!is_binary) {
			zprintf("%s: Server does not support binary encoding!", sN);
			return;
		}
	}
	{
		//zprintf("%s: Sending Logon Request...", sN);
		s_LogonRequest lr;
		lr.HeartbeatIntervalInSeconds = HEARTBEAT_SECONDS;
		lr.SetClientName("ZorroSCPlugin");
		lr.SetUsername(g_sUser.c_str());
		if (g_sPwd.length())lr.SetPassword(g_sPwd.c_str());
		lr.SetTradeAccount(g_sTradeaccountSelected.c_str());
		cl_send(FEED_HIST, &lr, lr.Size);
		s_LogonResponse lre;
		cl_block(ubc_login, FEED_HIST, 0, &lre);
		if (cl_is_stopped(FEED_HIST)) { return; }
		if (lre.Result != LOGON_SUCCESS) {
			zprintf("%s: Logon failure", sN);
			cl_shutdown(FEED_HIST);
			return;
		}
		if (!lre.HistoricalPriceDataSupported) {
			zprintf("%s: Error: This server does not support historical price data.", sN);
			cl_shutdown(FEED_HIST);
			return;
		}
	}
	{
		cl_send(FEED_HIST, &pHD->rq, pHD->rq.Size);
		cl_block(ubc_gethist, FEED_HIST, pHD->rq.RequestID, pHD);
		cl_shutdown(FEED_HIST);
	}

}

DLLFUNC int BrokerHistory2(char* ZorroSymbol, DATE tStart, DATE tEnd,
	int nTickMinutes, int nTicks, T6* pTicks)
{
	try {
		s_Asset* pAsset = get_asset_by_ZorroSymbol(ZorroSymbol);
		if (!pAsset) {
			zprintf("BrokerHistory2: Symbol %s not found", ZorroSymbol);
			return 0;
		}
		const char* SCSymbol = pAsset->SCSymbol.c_str();

		__time32_t eStart = (__time32_t)date_to_vEpochSeconds(tStart);
		__time32_t eEnd = (__time32_t)date_to_vEpochSeconds(tEnd);

		// only tick, 1m, and daily supported.
		
		if (nTickMinutes <= 0) { nTickMinutes = 0; }
		else if (nTickMinutes < 1440) { nTickMinutes = 1; }
		else { nTickMinutes = 1440; }

		s_HistData h;
		h.rq.RequestID = new_request_id();
		h.rq.SetSymbol(pAsset->SCSymbol.c_str());
		switch (nTickMinutes) {
		case 0: h.rq.RecordInterval = INTERVAL_TICK; break;
		case 1: h.rq.RecordInterval = INTERVAL_1_MINUTE; break;
		case 1440: h.rq.RecordInterval = INTERVAL_1_DAY; break;
		}
		h.rq.StartDateTime = eStart;
		h.rq.EndDateTime = eEnd;
		get_history(&h);
		int N = 0;
		if (h.vBars.size()) {
			for (auto p = h.vBars.rbegin(); p != h.vBars.rend(); p++) {
				bool is_microseconds = p->StartDateTime > 16725225600ll; // 2500 A.D.
				DATE d = is_microseconds ? 
					llEpochMicroseconds_to_date(p->StartDateTime) : 
					vEpochSeconds_to_date((double)p->StartDateTime);
				if (nTickMinutes) {//shift to beginning of bar.
					d *= 1440 / nTickMinutes;
					d = (int)d;
					d /= 1440 / nTickMinutes;
				}
				if (nTickMinutes == 1)d += (1./1440); // zorro uses bar close time for intraday.
				if (d < tStart || tEnd < d) continue;
				pTicks[N].time = d;
				if (nTickMinutes == 1440) pTicks[N].time = lround(pTicks[N].time);
				pTicks[N].fOpen = (float)p->OpenPrice;
				pTicks[N].fHigh = (float)p->HighPrice;
				pTicks[N].fLow = (float)p->LowPrice;
				pTicks[N].fClose = (float)p->LastPrice;
				pTicks[N].fVal = (float)p->NumTrades;
				pTicks[N].fVol = (float)p->Volume;
				N++;
				if (N == nTicks) break;
			}
		}
		else if (h.vTicks.size()) {
			for (auto p = h.vTicks.rbegin(); p != h.vTicks.rend(); p++) {
				if (p->DateTime < eStart || eEnd < p->DateTime) continue;
				pTicks[N].time = vEpochSeconds_to_date(p->DateTime);
				pTicks[N].fOpen = (float)p->Price;
				pTicks[N].fHigh = (float)p->Price;
				pTicks[N].fLow = (float)p->Price;
				pTicks[N].fClose = (float)p->Price;
				pTicks[N].fVal = (float)p->Price;
				pTicks[N].fVol = (float)p->Price;
				N++;
				if (N == nTicks) break;
			}
		}
		return N;
	}
	catch (std::exception const& e) {
		zprintf("BrokerHistory2 error: %s", e.what());
		return 0;
	}
}


bool ubc_submitorder(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	auto pO = (const s_SubmitNewSingleOrder*)pAuxiliary;
	switch (Type) {
	case ORDER_UPDATE: {
		s_OrderUpdate re;
		re.CopyFrom(pMsg);
		if (!strcmp(re.ClientOrderID, pO->ClientOrderID)) { // same order
			switch (re.OrderStatus) { //check for end of life
			//case ORDER_STATUS_FILLED:
			//case ORDER_STATUS_CANCELED:
			case ORDER_STATUS_REJECTED:
				return true;
			}
			if (strlen(re.ServerOrderID)) { // check for order id assignment
				return true;
			}
		}
	}//ORDER_UPDATE
	}//switch
	return false;
}
const char* get_tif_info(TimeInForceEnum tif) {
	switch (tif) {
	case TIF_UNSET: return "(TIF not set)";
	case TIF_DAY: return "DAY";
	case TIF_GOOD_TILL_CANCELED: return "GTC";
	case TIF_GOOD_TILL_DATE_TIME: return "Good till date/time";
	case TIF_IMMEDIATE_OR_CANCEL: return "IOC";
	case TIF_ALL_OR_NONE: return "AON";
	case TIF_FILL_OR_KILL: return "FOK";
	}
	return "(TIF unknown)";
}
const char* get_price(s_Asset* pA, double Limit) {
	int decimals = 0;
	switch (pA->definition.PriceDisplayFormat) {
	case PRICE_DISPLAY_FORMAT_DECIMAL_1: decimals = 1;
	case PRICE_DISPLAY_FORMAT_DECIMAL_2: decimals = 2;
	case PRICE_DISPLAY_FORMAT_DECIMAL_3: decimals = 3;
	case PRICE_DISPLAY_FORMAT_DECIMAL_4: decimals = 4;
	case PRICE_DISPLAY_FORMAT_DECIMAL_5: decimals = 5;
	case PRICE_DISPLAY_FORMAT_DECIMAL_6: decimals = 6;
	case PRICE_DISPLAY_FORMAT_DECIMAL_7: decimals = 7;
	case PRICE_DISPLAY_FORMAT_DECIMAL_8: decimals = 8;
	case PRICE_DISPLAY_FORMAT_DECIMAL_9: decimals = 9;
	}
	return strf(strf("%%0.%df", decimals), Limit);
}
bool is_buy(int Amount) { return Amount > 0; }
bool is_market(double Limit) { return Limit <= 0; }
BuySellEnum get_buy_or_sell(int Amount) { return Amount > 0 ? BUY : SELL; }
const char* get_buy_or_sell_info(int Amount) { return Amount > 0 ? "Buy" : "Sell"; }
OrderTypeEnum get_ordertype(double Limit) { return is_market(Limit) ? ORDER_TYPE_MARKET : ORDER_TYPE_LIMIT; }
const char* get_ordertype_info(s_Asset* pA, double Limit) {
	return is_market(Limit) ? "MARKET" : strf("LIMIT=%s, TIF:%s", get_price(pA, Limit), get_tif_info(g_TimeInForce));
}
DLLFUNC int BrokerBuy2(char* ZorroAsset, int Amount,
	double StopDist, double Limit, double* pPrice, int* pFill) {
	try {
		cl_drain();
		if (cl_is_stopped(FEED_MAIN)) {
			zprintf("BrokerBuy2(A): stopped");
			return 0;
		}


		s_Asset* pA = get_asset_by_ZorroSymbol(ZorroAsset);
		if (!pA) {
			zprintf("%s: Invalid symbol", ZorroAsset);
			return 0;
		}

		//

		//zprintf("Ordering volume: %s...", get_ordervolume(pA, Amount));
		zprintf("%s: %s %d at %s",
			pA->SCSymbol.c_str(),
			get_buy_or_sell_info(Amount),
			abs(Amount),
			get_ordertype_info(pA, Limit)
		);

		s_OrderUpdate* pO = NULL;
		s_SubmitNewSingleOrder o;
		o.SetSymbol(pA->SCSymbol.c_str());
		int nTradeID = new_TradeID();
		o.SetClientOrderID(new_ClientOrderID(nTradeID));
		o.BuySell = get_buy_or_sell(Amount);
		if (is_market(Limit)) {
			o.OrderType = ORDER_TYPE_MARKET;
		}
		else {
			o.OrderType = ORDER_TYPE_LIMIT;
			o.Price1 = Limit;
		}
		o.TimeInForce = g_TimeInForce;
		o.Quantity = abs(Amount);
		o.SetTradeAccount(g_sTradeaccountSelected.c_str());
		o.IsAutomatedOrder = 1;
		cl_send(FEED_MAIN, &o, o.Size);
		cl_block(ubc_submitorder, FEED_MAIN, 0, &o);
		pO = get_order_by_ClientOrderID(o.ClientOrderID);
		if (!pO) {
			zprintf("matching ClientOrderID not found");
			return 0;
		}


		if (g_OrderBlockMode == 1 && (g_TimeInForce == TIF_IMMEDIATE_OR_CANCEL || g_TimeInForce == TIF_FILL_OR_KILL)) {
			if (g_OrderWait_ms > 0)set_timeout(g_OrderWait_ms);
			else set_timeout(NETWORK_TIMEOUT_MS);
			for (;;) {
				if (!refresh()) return 0;
				if (cl_is_stopped(FEED_MAIN)) {
					zprintf("BrokerBuy2(B): stopped");
					return 0;
				}
				if (pPrice && pO->AverageFillPrice > 0 && pO->AverageFillPrice != DBL_MAX)
					*pPrice = pO->AverageFillPrice;
				if (pFill && pO->FilledQuantity > 0 && pO->FilledQuantity != DBL_MAX)
					*pFill = lround(pO->FilledQuantity);
				if (timed_out()) {
					zprintf("timed out, canceling trade...");
					BrokerCommand(DO_CANCEL, nTradeID);
					return 0;
				}
				switch (pO->OrderStatus) {
				case ORDER_STATUS_FILLED:
				case ORDER_STATUS_CANCELED:
				case ORDER_STATUS_REJECTED:
					if (pO->FilledQuantity <= 0) return 0;
					return nTradeID;
				}
				cl_loiter();
			}
		}
		return nTradeID;
	}
	catch (std::exception const& e) {
		zprintf("BrokerBuy2 error: %s", e.what());
		return 0;
	}

}
DLLFUNC int BrokerTrade(int nTradeID, double* pOpen, double* pClose, double* pRoll, double* pProfit) {
	try {
		cl_drain();
		if (cl_is_stopped(FEED_MAIN)) {
			zprintf("BrokerTrade: stopped");
			return NAY;
		}
		auto pO = get_order_by_TradeID(nTradeID);
		if (!pO) return NAY;
		auto pA = get_asset_by_SCSymbol(pO->Symbol);
		if (!pA) return NAY;
		switch (pO->OrderStatus) {
		case ORDER_STATUS_FILLED:
		case ORDER_STATUS_CANCELED:
		case ORDER_STATUS_REJECTED:
			return lround(pO->FilledQuantity);
		}
		return 0;//NOT FILLED
	}
	catch (std::exception const& e) {
		zprintf("BrokerTrade error: %s", e.what());
		return 0;
	}
}

struct s_snapshot {
	s_MarketDataRequest rq;
	s_MarketDataSnapshot snap;
};
bool ubc_snapshot(t_feedid id, void* pMsg, uint16_t Type, int32_t request_id, void* pAuxiliary) {
	s_snapshot* pS = (s_snapshot*)pAuxiliary;
	switch (Type) {
	case MARKET_DATA_SNAPSHOT: {
		s_MarketDataSnapshot re;
		re.CopyFrom(pMsg);
		if (re.SymbolID == pS->rq.SymbolID) {
			pS->snap = re;
			return true;
		}
	}//MARKET_DATA_SNAPSHOT
	case MARKET_DATA_REJECT: {
		s_MarketDataReject re;
		re.CopyFrom(pMsg);
		if (re.SymbolID == pS->rq.SymbolID) {
			if (strlen(re.RejectText))zprintf("Rejected: \"%s\"", re.RejectText);
			else zprintf("Rejected.");
			return true;
		}
	}//MARKET_DATA_REJECT
	}//switch
	return false;
}

DLLFUNC double BrokerCommand(int Command, DWORD dwParameter) {
	cl_drain();
	switch (Command) {
	case GET_PRICETYPE:
		return g_PriceType;
	case SET_PRICETYPE:
		switch (dwParameter) {
		case 1: // bid-ask-spread
		case 2: // last trade price
			g_PriceType = (int)dwParameter;
		}
		return 0;
	case SET_ORDERTYPE:
		switch ((int)dwParameter) {
		case 0: g_TimeInForce = TIF_FILL_OR_KILL; return 1;
		case 1: g_TimeInForce = TIF_ALL_OR_NONE; return 1;
		case 2: g_TimeInForce = TIF_GOOD_TILL_CANCELED; return 1;
		case 11: g_TimeInForce = TIF_DAY; return 1;
		case 12: g_TimeInForce = TIF_IMMEDIATE_OR_CANCEL; return 1;
		case 13: g_TimeInForce = TIF_FILL_OR_KILL; return 1;
		}
		return 0;
	case GET_WAIT:
		return g_OrderWait_ms;
	case SET_WAIT:  // Note: 0 = no time limit
		g_OrderWait_ms = (int)dwParameter;
		return 1;
	case GET_MAXTICKS: return MAXTICKS;
	case SET_SYMBOL:
		strcpy_s(g_Symbol, (char*)dwParameter);
		return 1;
	case DO_CANCEL: {
		s_OrderUpdate* pO = get_order_by_TradeID((int)dwParameter);
		if (!pO) return 0;
		s_CancelOrder co;
		co.SetServerOrderID(pO->ServerOrderID);
		co.SetClientOrderID(pO->ClientOrderID);
		cl_send(FEED_MAIN, &co, co.Size);
		cl_drain(); // no need to block
		return 1;
	}//DO_CANCEL
	case SC_GET_SNAPSHOT: {
		SC_SNAPSHOT* p = (SC_SNAPSHOT*)dwParameter;
		if (!p) return 0;
		memset(p, 0, sizeof(SC_SNAPSHOT));
		if (!strlen(g_Symbol)) return 0;
		s_Asset* pA = get_asset_by_SCSymbol(g_Symbol);
		if (!pA) return 0;
		if (!pA->SymbolID) pA->SymbolID = new_symbol_id();
		s_snapshot s;
		s.rq.RequestAction = SNAPSHOT;
		s.rq.SymbolID = pA->SymbolID;
		s.rq.SetSymbol(g_Symbol);
		cl_send(FEED_MAIN, &s.rq, s.rq.Size);
		cl_block(ubc_snapshot, FEED_MAIN, 0, &s);
		if (!s.snap.SymbolID) return 0;
		p->SessionSettlementPrice = s.snap.SessionSettlementPrice;
		p->SessionOpenPrice = s.snap.SessionOpenPrice;
		p->SessionHighPrice = s.snap.SessionHighPrice;
		p->SessionLowPrice = s.snap.SessionLowPrice;
		p->SessionVolume = s.snap.SessionVolume;
		p->SessionNumTrades = s.snap.SessionNumTrades;
		p->OpenInterest = s.snap.OpenInterest;
		p->vBidPrice = s.snap.BidPrice;
		p->vAskPrice = s.snap.AskPrice;
		p->vAskQuantity = s.snap.AskQuantity;
		p->vBidQuantity = s.snap.BidQuantity;
		p->vLastTradePrice = s.snap.LastTradePrice;
		p->vLastTradeVolume = s.snap.LastTradeVolume;
		p->LastTradeDateTime = s.snap.LastTradeDateTime > 0? vEpochSeconds_to_date(s.snap.LastTradeDateTime) : 0;
		p->BidAskDateTime = s.snap.BidAskDateTime > 0 ? vEpochSeconds_to_date(s.snap.BidAskDateTime) : 0;
		p->SessionSettlementDateTime = s.snap.SessionSettlementDateTime > 0 ? vEpochSeconds_to_date(s.snap.SessionSettlementDateTime) : 0;
		p->TradingSessionDate = s.snap.TradingSessionDate > 0 ? vEpochSeconds_to_date(s.snap.TradingSessionDate) : 0;
		return 1;
	}//SC_GET_SNAPSHOT
	case SC_GET_SECURITYDEF: {
		SC_SECURITYDEF* p = (SC_SECURITYDEF*)dwParameter;
		if (!p) return 0;
		memset(p, 0, sizeof(SC_SECURITYDEF));
		if (!strlen(g_Symbol)) return 0;
		s_Asset* pA = get_asset_by_SCSymbol(g_Symbol);
		if (!pA) return 0;
		strcpy_s(p->sSymbol, pA->definition.Symbol);
		strcpy_s(p->sExchange, pA->definition.Exchange);
		strcpy_s(p->sDescription, pA->definition.Description);
		strcpy_s(p->sUnderlyingSymbol, pA->definition.UnderlyingSymbol);
		strcpy_s(p->sExchangeSymbol, pA->definition.ExchangeSymbol);
		strcpy_s(p->sCurrency, pA->definition.Currency);
		p->SecurityExpirationDate = pA->definition.SecurityExpirationDate > 0 ? vEpochSeconds_to_date(pA->definition.SecurityExpirationDate) : 0;
		p->RolloverDate = pA->definition.RolloverDate > 0 ? vEpochSeconds_to_date(pA->definition.RolloverDate) : 0;
		p->SecurityType = pA->definition.SecurityType;
		p->MinPriceIncrement = pA->definition.MinPriceIncrement;
		p->PriceDisplayFormat = pA->definition.PriceDisplayFormat;
		p->CurrencyValuePerIncrement = pA->definition.CurrencyValuePerIncrement;
		p->FloatToIntPriceMultiplier = pA->definition.FloatToIntPriceMultiplier;
		p->IntToFloatPriceDivisor = pA->definition.IntToFloatPriceDivisor;
		p->UpdatesBidAskOnly = pA->definition.UpdatesBidAskOnly;
		p->StrikePrice = pA->definition.StrikePrice;
		p->PutOrCall = pA->definition.PutOrCall;
		p->ShortInterest = pA->definition.ShortInterest;
		p->BuyRolloverInterest = pA->definition.BuyRolloverInterest;
		p->SellRolloverInterest = pA->definition.SellRolloverInterest;
		p->EarningsPerShare = pA->definition.EarningsPerShare;
		p->SharesOutstanding = pA->definition.SharesOutstanding;
		p->IntToFloatQuantityDivisor = pA->definition.IntToFloatQuantityDivisor;
		p->HasMarketDepthData = pA->definition.HasMarketDepthData;
		p->DisplayPriceMultiplier = pA->definition.DisplayPriceMultiplier;
		p->InitialMarginRequirement = pA->definition.InitialMarginRequirement;
		p->MaintenanceMarginRequirement = pA->definition.MaintenanceMarginRequirement;
		p->ContractSize = pA->definition.ContractSize;
		p->OpenInterest = pA->definition.OpenInterest;
		p->IsDelayed = pA->definition.IsDelayed;
		return 1;
	}//SC_GET_SECURITYDEF
	case SC_SET_ORDERBLOCKMODE:
		switch (dwParameter) {
		case 0:
		case 1:
			g_OrderBlockMode = (int)dwParameter;
			return 1;
		}
		return 0;
	case SC_SET_FUTURES_CONTRACT_CONFIG: {
		int today_yyyymmdd = get_todays_date_yyyymmdd();
		int yr_first = today_yyyymmdd / 10000;
		int yr_max = yr_first + 10;
		const char* monthcodestr = get_monthcode_string((int)dwParameter);
		int len = (int)strlen(monthcodestr);
		int N = 0;
		for (int yr = yr_first; yr <= yr_max; yr++) {
			for (int i=0; i < len; i++) {
				char sc_symbol[64];
				strcpy_s(sc_symbol, g_Symbol);
				auto p = strstr(sc_symbol, "?##");
				if (!p)continue;
				const char* myy = strf("%c%02d", monthcodestr[i], yr % 100);
				memcpy_s(p, 3, myy, 3);

				s_Asset* pA = get_asset_by_SCSymbol(sc_symbol);
				if (!pA) continue;
				if (!pA->is_defined) continue;
				if (today_yyyymmdd > pA->nExpiry) continue;
				g_BeQuiet = true;
				int ret = BrokerAsset(sc_symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
				g_BeQuiet = false;
				if (!ret) continue;
				pA = get_asset_by_SCSymbol(sc_symbol);
				if (!pA) continue;
				if (!pA->is_subscribed) continue;
				if (!pA->nExpiry) continue;

				pA->UnderlyingSymbol = g_Symbol;
				pA->ZorroSymbol = strf("%s-FUT-%08d", g_Symbol, pA->nExpiry);
				N++;
			}
		}
		return N;
	}//SC_SET_FUTURES_CONTRACT_CONFIG
	case GET_FUTURES: { //does not set multiplier
		CONTRACT* p = (CONTRACT*)dwParameter;
		int today_yyyymmdd = get_todays_date_yyyymmdd();
		int N = 0;
		for (const auto& ap : g_mAssets) {
			const auto& a = ap.second;
			if (a.UnderlyingSymbol != g_Symbol)continue;
			if (a.nExpiry < today_yyyymmdd)continue;
			if (!a.is_subscribed) continue;
			memset(&p[N], 0, sizeof(CONTRACT));
			p[N].Expiry = a.nExpiry;
			p[N].Type = FUTURE;
			N++;
			if (N == MAX_CONTRACTS) break;
		}
		return N;
	}//GET_FUTURES
	case SET_HWND:
		cl_set_hwnd((HWND)dwParameter);
		return 1;
	}//switch
	return 0;
}