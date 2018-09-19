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

bool Market::can_get(s_MarketDataSnapshot& snapshot, uint32_t SymbolID)
{
	for (const auto& snap : snapshots_)
	{
		if (snap.GetSymbolID() != SymbolID) continue;
		snapshot = snap;
		return true;
	}
	return false;
}

void Market::Snapshot(s_MarketDataSnapshot* snapshot)
{
	// make sure shapshot is ok
	uint32_t SymbolID = snapshot->GetSymbolID();
	if (!SymbolID) return;

	// check if snapshot exists, and if so update it
	for (auto& snap : snapshots_)
	{
		if (snap.GetSymbolID() != SymbolID) continue;

		// found a match
		snap = *snapshot;
		return;
	}
	// does not exist, add it
	snapshots_.push_back(*snapshot);
}
s_MarketDataSnapshot* Market::get_snapshot(uint32_t SymbolID)
{
	for (auto& snap : snapshots_)
	{
		if (snap.GetSymbolID() != SymbolID) continue;
		return &snap;
	}
	return 0;
}