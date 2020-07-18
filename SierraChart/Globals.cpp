#include "Engine.h"

std::unique_ptr<client> c;  //main client session
int(__cdecl *BrokerError)(const char* txt) = NULL;
int(__cdecl *BrokerProgress)(const int percent) = NULL;
std::string user="", pw="", h="", p1="", p2="", 
tradeaccount_main="", tradeaccount_selected = "";

bool isLive = false;
bool zlib_enabled = DEFAULT_ZLIB_ENABLED;
bool dividend_adjusted = false;
HWND hWindow = NULL;
int pricetype = PRICETYPE_ASKBID;
int voltype = VOLTYPE_TRADE_VOLUME;
int ordertype = ORDERTYPE_FILLORKILL;
int patch = 0;
std::thread::id zt_id = std::this_thread::get_id();
std::string uuid = "", symbol = ""; //ordertext = "zorro"
//double bc_limit;


void market_trigger()
{
	if (hWindow) PostMessage(hWindow, WM_APP + 1, 0, 0);
}

bool can_calc_LotAmount(DTC::s_SecurityDefinitionResponse* def, double& LotAmount)
{
	if (def->GetMinPriceIncrement() && def->GetCurrencyValuePerIncrement())
	{
		LotAmount = def->GetCurrencyValuePerIncrement() / def->GetMinPriceIncrement();
		return true;
	}
	else return false;
}
