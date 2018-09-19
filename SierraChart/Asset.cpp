#include "Engine.h"
using namespace DTC;
using namespace DTCTools;
using namespace DTCTypes;

double client::zt_get_position(char* ZorroAsset)
{
	s_SecurityDefinitionResponse* def = can_define(ZorroAsset);
	if (!def) {
		err("GET_POSITION: " + (std::string)ZorroAsset + " not defined");
		return 0;
	}
	
	return maybe_post_return([&]()->double {
		per_trade_account& pta = m_pta.find(tradeaccount_selected)->second;
		std::string sym = def->GetSymbol();
		s_HistoricalOrderFillResponse* hofr = NULL;
		for (auto& o : pta.orders_hist)
		{
			if ((std::string)o.GetSymbol() == sym)
				hofr = &o;
		}
		if (!hofr) return 0;

		double AmountDivisor = 1;
		if (can_calc_LotAmount(def, AmountDivisor))
		{
			if (AmountDivisor >= 1)
				AmountDivisor = 1;
		}

		// Amount / AmountDivisor = Quantity, therefore
		// Amount = Quantity * AmountDivisor
		return (hofr->GetQuantity() * AmountDivisor);
	});
}


void client::print_exchanges() // diagnostic purposes only
{
	s_ExchangeListRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	b.expect(sol_ExchangeListResponse_RequestID, rq.RequestID);
	err("Requesting exchange list");
	write_async(rq);
	if (!b.block_is_good())
	{
		err("rejected!");
		return;
	}

	auto fu = post_use_future(io, [&]()->bool {
		int i = 0;
		for (auto a : exchanges)
		{
			i++;
			std::string name = a.GetExchange();
			if (name.size())
			{
				err(("Exch#" + std::to_string(i) + ": " + (std::string)a.Exchange).c_str());
			}
			else
			{
				err(("Exch#" + std::to_string(i) + ": (blank entry)").c_str());
			}
		}
		return 0;
	});
	fu.get(); // ignored
}

void client::print_security_info(std::string Symbol)  // diagnostic purposes only
{
	s_SecurityDefinitionForSymbolRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	rq.SetSymbol(Symbol.c_str());
	b.expect(sol_SecurityDefinitionResponse_RequestID, rq.RequestID);
	err(("Requesting definition for symbol: " + Symbol).c_str());
	write_async(rq);
	if (!b.block_is_good()) 
	{
		err("Request rejected.");
		return;
	}
	if (security_definitions_latest.size())
	{
		const s_SecurityDefinitionResponse& re = security_definitions_latest.back();
		err(("Symbol: " + (std::string)re.Symbol).c_str());
		err(("Exchange: " + (std::string)re.Exchange).c_str());
		err(("Type: " + std::to_string((int)re.SecurityType)).c_str());
		err(("Underlying: " + (std::string)re.UnderlyingSymbol).c_str());
		err(("Currency: " + (std::string)re.Currency).c_str());
	}
}
void client::assets_test_print()
{
	//print_security_info("F.US.EPM18");
	//print_security_info("F.US.M6BM18");
	//print_security_info("C.US.EP11J1815550");
	//print_security_info("P.US.EP11J1815550");
	print_symbols_for_underlying("F.US.JY6Z18");
	print_symbols_for_underlying("F.US.EDAZ18");

}
void client::print_underlying_symbols_for_exchange(std::string Exchange)
{
	s_UnderlyingSymbolsForExchangeRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	if (Exchange.size()) rq.SetExchange(Exchange.c_str());
	b.expect(sol_SecurityDefinitionResponse_RequestID, rq.RequestID);
	err(("Requesting underlying symbols for Exchange " + Exchange).c_str());
	write_async(rq);
	if (!b.block_is_good())
	{
		err("request rejected");
		return;
	}

	for (auto re : security_definitions_latest)
	{
		err(("Symbol: " + (std::string)re.Symbol).c_str());
		err(("Exchange: " + (std::string)re.Exchange).c_str());
		err(("Type: " + std::to_string((int)re.SecurityType)).c_str());
		err(("Underlying: " + (std::string)re.UnderlyingSymbol).c_str());
	}
}
void client::print_symbols_for_underlying(std::string Underlying)
{
	s_SymbolsForUnderlyingRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	rq.SetUnderlyingSymbol(Underlying.c_str());
	b.expect(sol_SecurityDefinitionResponse_RequestID, rq.RequestID);
	err(("Requesting symbols for underlying: " + Underlying).c_str());
	write_async(rq);
	if (!b.block_is_good())
	{
		err("request rejected");
		return;
	}

	for (auto re : security_definitions_latest)
	{
		err(("Symbol: " + (std::string)re.Symbol).c_str());
		err(("Exchange: " + (std::string)re.Exchange).c_str());
		err(("Type: " + std::to_string((int)re.SecurityType)).c_str());
		err(("Underlying: " + (std::string)re.UnderlyingSymbol).c_str());
	}
}



//bool client::can_parse_option(std::string ZorroAsset, std::string& Underlying, int& Expiry_YYYYMMDD, double& StrikePrice, char& P_or_C)
//{
//	std::string& in = ZorroAsset;
//	// reformat options to Ally Invest format
//	// example input:  "ES-FOP-20121221-1350-C-GLOBEX"
//	// example input:  "SPY-OPT-20170721-241.50-P-NYSE"
//	// example output: "SPY170714C00205000" = (SPY, 20170714, CALL, STRIKE = 00205.000)

//	try {
//		size_t optpos = str.find("-OPT-");

//		// if this is not an option...
//		if (optpos == std::string::npos) { return str; }

//		// otherwise, get to work.
//		std::ostringstream oss;
//		oss << str.substr(0, optpos); // "SPY"
//		oss << str.substr(optpos + 7, 6); // "170721"
//		oss << str.substr(str.length() - 1, 1); //"P"

//		int qpos = optpos + 14;
//		int qlen = str.length() - qpos - 2;
//		double quote = std::stod(str.substr(qpos, qlen));
//		int quote_i = (int)(std::round(quote * 1000));
//		oss << std::setw(8) << std::setfill('0') << quote_i; //"00241500"

//		return(oss.str());
//	}
//	catch (...)
//	{
//		return str;
//	}

//}



s_SecurityDefinitionResponse* client::can_define_local(std::string& Symbol)
{

	// first, check if there are exact matches.
	for (auto& a : security_definitions)
	{
		if (Symbol == (std::string)a.Symbol) return &a;
	}

	// no matches
	return 0;
}
s_SecurityDefinitionResponse* client::can_define_local_hist(std::string& Symbol)
{

	// first, check if there are exact matches.
	for (auto& a : security_definitions)
	{
		if (Symbol == (std::string)a.Symbol) return &a;
	}

	// no matches
	return 0;
}


s_SecurityDefinitionResponse* client::can_define_server(std::string& Symbol)
{
	s_SecurityDefinitionForSymbolRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	rq.SetSymbol(Symbol.c_str());
	b.expect(sol_SecurityDefinitionResponse_RequestID, rq.RequestID);
	//err("Requesting definition...");
	write_async(rq);
	if (!b.block_is_good())
		return NULL;
	return can_define_local(Symbol);
}

s_SecurityDefinitionResponse* client::can_define_server_hist(std::string& Symbol)
{
	s_SecurityDefinitionForSymbolRequest rq;
	rq.RequestID = rid.get_request_id(rq);
	rq.SetSymbol(Symbol.c_str());
	b.expect(sol_SecurityDefinitionResponse_RequestID, rq.RequestID);
	//err("Requesting definition...");
	write_async(rq);
	if (!b.block_is_good())
		return NULL;
	return can_define_local_hist(Symbol);
}

s_SecurityDefinitionResponse* client::can_define(char* ZorroAsset)
{
	std::string Symbol = ZorroAsset; // HACK: Assume ZorroAsset is literally the ticker symbol

	s_SecurityDefinitionResponse* out;
	if (out = can_define_local(Symbol))
	{
		return out;
	}
	else return can_define_server(Symbol);
}

bool client::can_subscribe(s_SecurityDefinitionResponse* def)
{
	s_MarketDataRequest rq;
	rq.SymbolID = sid.get_symbolID(def);
	rq.SetSymbol(def->GetSymbol());
	rq.SetExchange(def->GetExchange());
	b.expect(sol_MarketDataSnapshot_SymbolID, rq.SymbolID);
	write_async(rq);
	if(!b.block_is_good())
	return 0;
	else return 1;

}

bool client::can_update(s_SecurityDefinitionResponse* d,
	double *pPrice, double *pSpread, double *pVolume,
	double *pPip, double *pPipCost, double *pLotAmount,
	double *pMarginCost, double *pRollLong, double *pRollShort)
{
	return maybe_post_return([&]()->int {
		s_MarketDataSnapshot* s = market.get_snapshot(sid.get_symbolID(d));
		if ((!s)) { return false; }
		if (!pPrice) { return false; }
		if (pPrice && s->GetAskPrice()) 
			*pPrice = s->GetAskPrice();
		if (pSpread && s->GetAskPrice() && s->GetBidPrice()) 
			*pSpread = std::abs(s->GetAskPrice() - s->GetBidPrice());
		if (pVolume && s->GetSessionVolume()) 
			*pVolume = s->GetSessionVolume();
		if (pPip && d->GetMinPriceIncrement())	
			*pPip = d->GetMinPriceIncrement();
		double LotAmount = 0;
		if (pLotAmount && can_calc_LotAmount(d, LotAmount))
			*pLotAmount = LotAmount;

		// *** NOTE ***
		// pPipCost, pMarginCost, pRollLong, and pRollShort are rarely set because
		//		1) Account currency and security currency can be different
		//		2) The DTC server usually does not enforce that both currencies are defined,
		//				even though the protocol is capable of it!
		//		3) In many cases, one or both of these fields will be blank!
		per_trade_account& pta = m_pta.find(tradeaccount_selected)->second;
		std::string def_currency = d->GetCurrency();
		std::string acc_currency = pta.balance.GetAccountCurrency();
		if (
			def_currency.size() &&
			acc_currency.size() &&
			(def_currency == acc_currency)
			)
		{
			if (pPipCost && d->GetCurrencyValuePerIncrement())
				*pPipCost = d->GetCurrencyValuePerIncrement();
			if (pMarginCost && d->GetInitialMarginRequirement())
				*pMarginCost = d->GetInitialMarginRequirement();
			if (pRollLong && d->GetBuyRolloverInterest())
				*pRollLong = d->GetBuyRolloverInterest();
			if (pRollShort && d->GetSellRolloverInterest())
				*pRollLong = d->GetSellRolloverInterest();
		}
		return true;
	});
}

