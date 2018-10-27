#include "stdafx.h"
#include "Engine.h"

using namespace DTC;
using namespace DTCTools;
using namespace DTCTypes;
namespace cro = std::chrono;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;
using error_code = boost::system::error_code;
#undef max
#undef min


SymbolKnowledge::SymbolKnowledge() :
	symbol_status (MARKET_DATA_FEED_AVAILABLE),
	MinPriceIncrement(0)
{}
SymbolKnowledge::~SymbolKnowledge() {}

void client::md_update(
	uint32_t SymbolID,
	const DTC::AtBidOrAskEnum& Side,
	const double& Price,
	const double& Quantity,
	const DTC::t_DateTimeWithMilliseconds& DateTime,
	const DTC::MarketDepthUpdateTypeEnum& UpdateType)
{
	auto pK = market.get_symbol_knowledge(SymbolID);
	if (!pK) return;

	// is increment set? if not, need to set.
	if (!pK->MinPriceIncrement) {
		auto sym = sid.get_existing_symbol(SymbolID);
		if (sym == "") return;

		// got symbol, need definition
		auto pDef = can_define((char*)sym.c_str());
		if (!pDef) return;
		pK->MinPriceIncrement = pDef->GetMinPriceIncrement();
	}

	
	std::map<unsigned int, DepthEntry>* pMap = NULL;
	switch (Side) {
	case AT_ASK:
		pMap = &pK->map_pricelevel_askqty;
		break;
	case AT_BID:
		pMap = &pK->map_pricelevel_bidqty;
		break;
	case BID_ASK_UNSET:
	default:
		return;
	}
	if (!pMap) return;
	
	// rounding price level to nearest integer using +0.5 method
	unsigned int pricelevel = (unsigned int)((Price / pK->MinPriceIncrement) + 0.5);

	switch (UpdateType) {
	case MARKET_DEPTH_INSERT_UPDATE_LEVEL:
	{
		DepthEntry e;
		e.DateTime = DateTime;
		e.Quantity = Quantity;
		(*pMap)[pricelevel] = e;
	}
	break;
	case MARKET_DEPTH_DELETE_LEVEL:
		pMap->erase(pricelevel);
		break;
	case DEPTH_UNSET:
	default:
		return;
	}


}
void client::md_update(
	uint32_t SymbolID,
	const DTC::AtBidOrAskEnum& Side,
	const float& Price,
	const float& Quantity,
	const DTC::t_DateTime4Byte& DateTime,
	const DTC::MarketDepthUpdateTypeEnum& UpdateType)
{
	md_update(SymbolID, Side, (double)Price, (double)Quantity, (t_DateTimeWithMilliseconds)DateTime, UpdateType);
}
void client::md_update(
	uint32_t SymbolID,
	const DTC::AtBidOrAskEnum& Side,
	const double& Price,
	const double& Quantity,
	const DTC::t_DateTimeWithMilliseconds& DateTime) {
	md_update(SymbolID, Side, Price, Quantity, DateTime, MARKET_DEPTH_INSERT_UPDATE_LEVEL);
}


Market::Market() :
	feed_status(MARKET_DATA_FEED_AVAILABLE)
{}
Market::~Market() {}

//bool Market::can_get(s_MarketDataSnapshot& snapshot, uint32_t SymbolID)
//{
//	for (const auto& snap : market_knowledge)
//	{
//		if (snap.GetSymbolID() != SymbolID) continue;
//		snapshot = snap;
//		return true;
//	}
//	return false;
//}

void Market::Snapshot(s_MarketDataSnapshot* snapshot)
{
	// make sure shapshot is ok
	uint32_t SymbolID = snapshot->GetSymbolID();
	if (!SymbolID) return;

	// check if symbol_knowledge exists, and if so update it
	for (auto& sym_knowledge : market_knowledge)
	{
		if (sym_knowledge.snap.GetSymbolID() != SymbolID) continue;

		// found a match
		sym_knowledge.snap = *snapshot;
		return;
	}
	// does not exist, add it
	SymbolKnowledge k;
	k.snap = *snapshot;
	market_knowledge.push_back(k);
}
s_MarketDataSnapshot* Market::get_snapshot(uint32_t SymbolID)
{
	for (auto& sym_knowledge : market_knowledge)
	{
		if (sym_knowledge.snap.GetSymbolID() != SymbolID) continue;
		return &sym_knowledge.snap;
	}
	return NULL;
}
SymbolKnowledge* Market::get_symbol_knowledge(uint32_t SymbolID)
{
	for (auto& sym_knowledge : market_knowledge)
	{
		if (sym_knowledge.snap.GetSymbolID() != SymbolID) continue;
		return &sym_knowledge;
	}
	return NULL;
}