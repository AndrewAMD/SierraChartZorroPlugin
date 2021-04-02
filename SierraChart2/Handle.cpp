#include "pch.h"
#include "framework.h"
#include "StrBufs.h"

#include "client.h"
#include "dtc.h"

#include "Handle.h"
#include "SierraChart2.h"

#include "banned.h" //must include last


void handle_heartbeat(t_feedid id, void* pMsg) {
	//zprintf("%s: Received heartbeat", FeedNames[id]); //delete me
}
void handle_logoff(t_feedid id, void* pMsg) {
	zprintf("%s: Receved LOGOFF request.", FeedNames[id]);
	cl_shutdown(id);
}
void handle_user_message(t_feedid id, void* pMsg) {
	s_UserMessage m;
	m.CopyFrom(pMsg);
	zprintf("%s: \"%s\"", FeedNames[id], m.UserMessage);
}
void handle_general_log_message(t_feedid id, void* pMsg) {
	s_GeneralLogMessage m;
	m.CopyFrom(pMsg);
	zprintf("#%s: \"%s\"", FeedNames[id], m.MessageText);
}
void handle_MarketDataSnapshot(t_feedid id, void* pMsg) {
	s_MarketDataSnapshot m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (g_PriceType == 1) {
		double ask = 0, bid = 0;
		if (m.AskPrice != DBL_MAX)ask = m.AskPrice;
		if (m.BidPrice != DBL_MAX)bid = m.BidPrice;
		if (ask > 0 && bid > 0) {
			if (ask > 0) pA->vPrice = ask;
			if (ask > 0 && bid > 0) pA->vSpread = ask - bid;
		}
	}
	if (m.SessionVolume != DBL_MAX)pA->vVolume = m.SessionVolume;
	
}
void handle_MarketDataUpdateTrade(t_feedid id, void* pMsg) {
	s_MarketDataUpdateTrade m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (g_PriceType == 2) {
		pA->vPrice = m.Price;
	}
	if (m.Volume != DBL_MAX)pA->vVolume += m.Volume;
}
void handle_MarketDataUpdateTradeWithUnbundledIndicator2(t_feedid id, void* pMsg) {
	s_MarketDataUpdateTradeWithUnbundledIndicator2 m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (g_PriceType == 2) {
		pA->vPrice = m.Price;
	}
	if (m.Volume != DBL_MAX)pA->vVolume += m.Volume;
}
void handle_MarketDataUpdateTradeNoTimestamp(t_feedid id, void* pMsg) {
	s_MarketDataUpdateTradeNoTimestamp m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (g_PriceType == 2) {
		pA->vPrice = m.Price;
	}
	if (m.Volume != DBL_MAX)pA->vVolume += m.Volume;
}
void handle_MarketDataUpdateTradeCompact(t_feedid id, void* pMsg) {
	s_MarketDataUpdateTradeCompact m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (g_PriceType == 2) {
		pA->vPrice = m.Price;
	}
	if (m.Volume != DBL_MAX)pA->vVolume += m.Volume;
}
void handle_MarketDataUpdateBidAsk(t_feedid id, void* pMsg) {
	s_MarketDataUpdateBidAsk m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (g_PriceType == 1) {
		double ask = 0, bid = 0;
		if (m.AskPrice != DBL_MAX)ask = m.AskPrice;
		if (m.BidPrice != DBL_MAX)bid = m.BidPrice;
		if (ask > 0 && bid > 0) {
			if (ask > 0) pA->vPrice = ask;
			if (ask > 0 && bid > 0) pA->vSpread = ask - bid;
		}
	}
}
void handle_MarketDataUpdateBidAskCompact(t_feedid id, void* pMsg) {
	s_MarketDataUpdateBidAskCompact m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (g_PriceType == 1) {
		double ask = 0, bid = 0;
		if (m.AskPrice != DBL_MAX)ask = m.AskPrice;
		if (m.BidPrice != DBL_MAX)bid = m.BidPrice;
		if (ask > 0 && bid > 0) {
			if (ask > 0) pA->vPrice = ask;
			if (ask > 0 && bid > 0) pA->vSpread = ask - bid;
		}
	}
}
void handle_MarketDataUpdateSessionVolume(t_feedid id, void* pMsg) {
	s_MarketDataUpdateSessionVolume m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (m.Volume != DBL_MAX)pA->vVolume = m.Volume;
}
void handle_MarketDepthReject(t_feedid id, void* pMsg) {
	s_MarketDepthReject m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	auto s = strf("%s: No market depth", pA->SCSymbol.c_str());
	if (strlen(m.RejectText)) {
		s = ("%s %s", s, m.RejectText);
	}
	zprintf(s);
}
#include <math.h>
void handle_MarketDepthSnapshotLevel(t_feedid id, void* pMsg) {
	s_MarketDepthSnapshotLevel m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (m.IsFirstMessageInBatch) {
		pA->mBook.clear();
	}
	if (!pA->vPip) return; //avoid divide by zero
	int lev = lround(m.Price / pA->vPip);
	if (m.Side == AT_BID) lev *= -1;
	pA->mBook[lev] = m.Quantity;
}
void handle_MarketDepthUpdateLevel(t_feedid id, void* pMsg) {
	s_MarketDepthUpdateLevel  m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (!pA->vPip) return; //avoid divide by zero
	int lev = lround(m.Price / pA->vPip);
	if (m.Side == AT_BID) lev *= -1;
	pA->mBook[lev] = m.Quantity;
	if (m.UpdateType == MARKET_DEPTH_DELETE_LEVEL) {
		pA->mBook.erase(lev);
	}
}
void handle_MarketDepthUpdateLevelFloatWithMilliseconds(t_feedid id, void* pMsg) {
	s_MarketDepthUpdateLevelFloatWithMilliseconds  m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (!pA->vPip) return; //avoid divide by zero
	int lev = lround(m.Price / pA->vPip);
	if (m.Side == AT_BID) lev *= -1;
	pA->mBook[lev] = m.Quantity;
	if (m.UpdateType == MARKET_DEPTH_DELETE_LEVEL) {
		pA->mBook.erase(lev);
	}
}
void handle_MarketDepthUpdateLevelNoTimestamp(t_feedid id, void* pMsg) {
	s_MarketDepthUpdateLevelNoTimestamp  m;
	m.CopyFrom(pMsg);
	s_Asset* pA = get_asset_by_SymbolID(m.SymbolID);
	if (!pA)return;
	if (!pA->vPip) return; //avoid divide by zero
	int lev = lround(m.Price / pA->vPip);
	if (m.Side == AT_BID) lev *= -1;
	pA->mBook[lev] = m.Quantity;
	if (m.UpdateType == MARKET_DEPTH_DELETE_LEVEL) {
		pA->mBook.erase(lev);
	}
}
void handle_AccountBalanceReject(t_feedid id, void* pMsg) {
	s_AccountBalanceReject m;
	m.CopyFrom(pMsg);
	auto s = strf("%s: Account balance request rejected");
	if (strlen(m.RejectText)) {
		s = ("%s: \"%s\"", s, m.RejectText);
	}
	zprintf(s);
}
void handle_AccountBalanceUpdate(t_feedid id, void* pMsg) {
	s_AccountBalanceUpdate m;
	m.CopyFrom(pMsg);
	if (strlen(m.TradeAccount)) {
		g_mBalances[m.TradeAccount] = m;
	}
}
const char* get_order_status(OrderStatusEnum status) {
	switch (status) {
	case ORDER_STATUS_UNSPECIFIED: return "(status unspecified)";
	case ORDER_STATUS_ORDER_SENT: return "order sent";
	case ORDER_STATUS_PENDING_OPEN: return "pending open";
	case ORDER_STATUS_PENDING_CHILD: return "pending child";
	case ORDER_STATUS_OPEN: return "open";
	case ORDER_STATUS_PENDING_CANCEL_REPLACE: return "pending cancel replace";
	case ORDER_STATUS_PENDING_CANCEL: return "pending cancel";
	case ORDER_STATUS_FILLED: return "filled";
	case ORDER_STATUS_CANCELED: return "canceled";
	case ORDER_STATUS_REJECTED: return "rejected";
	case ORDER_STATUS_PARTIALLY_FILLED: return "partially filled";
	}
	return "(unknown status code)";
}
void print_orderinfo(const s_OrderUpdate& m) {
	const char* s = strf("%s", m.ClientOrderID);
	if (strlen(m.ServerOrderID)) {
		s = strf("%s (%s)", s, m.ServerOrderID);
	}
	s = strf("%s [%d/%d] %s: %s",
		s,
		lround(m.FilledQuantity), lround(m.OrderQuantity),
		m.Symbol,
		get_order_status(m.OrderStatus)
	);
	if (strlen(m.InfoText)) {
		s = strf("%s: %s", s, m.InfoText);
	}
	zprintf(s);
}
void handle_OrderUpdate(t_feedid id, void* pMsg) {
	s_OrderUpdate m;
	m.CopyFrom(pMsg);
	switch (m.OrderStatus) { //print end of life
	case ORDER_STATUS_FILLED:
	case ORDER_STATUS_CANCELED:
	case ORDER_STATUS_REJECTED:
		print_orderinfo(m);
	}
	if (strlen(m.ServerOrderID)) {
		auto p = get_order_by_ServerOrderID(m.ServerOrderID);
		if (!p)return;
		*p = m;
	}
}

void handle_msg(t_feedid id, void* pMsg, uint16_t Type) {
	//zprintf("HANDLING MESSAGE");//delete me
	switch (Type) {
	case HEARTBEAT: return handle_heartbeat(id, pMsg);
	case LOGOFF: return handle_logoff(id, pMsg);
	case USER_MESSAGE: return handle_user_message(id, pMsg);
	case GENERAL_LOG_MESSAGE: return handle_general_log_message(id, pMsg);
	case MARKET_DATA_SNAPSHOT: return handle_MarketDataSnapshot(id, pMsg);
	case MARKET_DATA_UPDATE_TRADE: return handle_MarketDataUpdateBidAsk(id, pMsg);
	case MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR_2: return handle_MarketDataUpdateTradeWithUnbundledIndicator2(id, pMsg);
	case MARKET_DATA_UPDATE_TRADE_NO_TIMESTAMP: return handle_MarketDataUpdateTradeNoTimestamp(id, pMsg);
	case MARKET_DATA_UPDATE_TRADE_COMPACT: return handle_MarketDataUpdateTradeCompact(id, pMsg);
	case MARKET_DATA_UPDATE_BID_ASK: return handle_MarketDataUpdateBidAsk(id, pMsg);
	case MARKET_DATA_UPDATE_BID_ASK_COMPACT: return handle_MarketDataUpdateBidAskCompact(id, pMsg);
	case MARKET_DATA_UPDATE_SESSION_VOLUME: return handle_MarketDataUpdateSessionVolume(id, pMsg);
	case MARKET_DEPTH_REJECT: return handle_MarketDepthReject(id, pMsg);
	case MARKET_DEPTH_SNAPSHOT_LEVEL: return handle_MarketDepthSnapshotLevel(id, pMsg);
	case MARKET_DEPTH_UPDATE_LEVEL: return handle_MarketDepthUpdateLevel(id, pMsg);
	case MARKET_DEPTH_UPDATE_LEVEL_FLOAT_WITH_MILLISECONDS: return handle_MarketDepthUpdateLevelFloatWithMilliseconds(id, pMsg);
	case MARKET_DEPTH_UPDATE_LEVEL_NO_TIMESTAMP: return handle_MarketDepthUpdateLevelNoTimestamp(id, pMsg);
	case ACCOUNT_BALANCE_REJECT: return handle_AccountBalanceReject(id, pMsg);
	case ACCOUNT_BALANCE_UPDATE: return handle_AccountBalanceUpdate(id, pMsg);
	case ORDER_UPDATE: return handle_OrderUpdate(id, pMsg);
	}
	//zprintf("Unhandled type: %d", Type);//delete me
}





