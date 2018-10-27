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





void client::receive(const std::vector<char>& m_in)
{
	uint16_t t = NULL;
	{
		s_Header* pHdr = (s_Header*)m_in.data();
		t = pHdr->Type;
	}
	switch (t)
	{

		// Authentication and connection monitoring
	case LOGON_RESPONSE:
	{
		s_LogonResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HEARTBEAT:
	{
		s_Heartbeat m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case LOGOFF:
	{
		s_Logoff m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case ENCODING_RESPONSE:
	{
		s_EncodingResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	// Market data
	case MARKET_DATA_REJECT:
	{
		s_MarketDataReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_SNAPSHOT:
	{
		s_MarketDataSnapshot m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_SNAPSHOT_INT:
	{
		s_MarketDataSnapshot_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case MARKET_DATA_UPDATE_TRADE:
	{
		s_MarketDataUpdateTrade m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_TRADE_COMPACT:
	{
		s_MarketDataUpdateTradeCompact m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_TRADE_INT:
	{
		s_MarketDataUpdateTrade_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_LAST_TRADE_SNAPSHOT:
	{
		s_MarketDataUpdateLastTradeSnapshot m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR:
	{
		s_MarketDataUpdateTradeWithUnbundledIndicator m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_BID_ASK:
	{
		s_MarketDataUpdateBidAsk m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_BID_ASK_COMPACT:
	{
		s_MarketDataUpdateBidAskCompact m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_BID_ASK_INT:
	{
		s_MarketDataUpdateBidAsk_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case MARKET_DATA_UPDATE_SESSION_OPEN:
	{
		s_MarketDataUpdateSessionOpen m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_OPEN_INT:
	{
		s_MarketDataUpdateSessionOpen_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_HIGH:
	{
		s_MarketDataUpdateSessionHigh m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_HIGH_INT:
	{
		s_MarketDataUpdateSessionHigh_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_LOW:
	{
		s_MarketDataUpdateSessionLow m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_LOW_INT:
	{
		s_MarketDataUpdateSessionLow_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_VOLUME:
	{
		s_MarketDataUpdateSessionVolume m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_OPEN_INTEREST:
	{
		s_MarketDataUpdateOpenInterest m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_SETTLEMENT:
	{
		s_MarketDataUpdateSessionSettlement m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_SETTLEMENT_INT:
	{
		s_MarketDataUpdateSessionSettlement_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_SESSION_NUM_TRADES:
	{
		s_MarketDataUpdateSessionNumTrades m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_UPDATE_TRADING_SESSION_DATE:
	{
		s_MarketDataUpdateTradingSessionDate m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case MARKET_DEPTH_REJECT:
	{
		s_MarketDepthReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DEPTH_SNAPSHOT_LEVEL:
	{
		s_MarketDepthSnapshotLevel m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DEPTH_SNAPSHOT_LEVEL_INT:
	{
		s_MarketDepthSnapshotLevel_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DEPTH_UPDATE_LEVEL:
	{
		s_MarketDepthUpdateLevel m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DEPTH_UPDATE_LEVEL_COMPACT:
	{
		s_MarketDepthUpdateLevelCompact m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DEPTH_UPDATE_LEVEL_INT:
	{
		s_MarketDepthUpdateLevel_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DEPTH_FULL_UPDATE_10:
	{
		s_MarketDepthFullUpdate10 m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DEPTH_FULL_UPDATE_20:
	{
		s_MarketDepthFullUpdate20 m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case MARKET_DATA_FEED_STATUS:
	{
		s_MarketDataFeedStatus m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case MARKET_DATA_FEED_SYMBOL_STATUS:
	{
		s_MarketDataFeedSymbolStatus m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

		// Trading related
	case OPEN_ORDERS_REJECT:
	{
		s_OpenOrdersReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case ORDER_UPDATE:
	{
		s_OrderUpdate m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case HISTORICAL_ORDER_FILLS_REJECT:
	{
		s_HistoricalOrderFillsReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HISTORICAL_ORDER_FILL_RESPONSE:
	{
		s_HistoricalOrderFillResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case CURRENT_POSITIONS_REJECT:
	{
		s_CurrentPositionsReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case POSITION_UPDATE:
	{
		s_PositionUpdate m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

		// Account list
	case TRADE_ACCOUNT_RESPONSE:
	{
		s_TradeAccountResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

		// Symbol discovery and security definitions
	case EXCHANGE_LIST_RESPONSE:
	{
		s_ExchangeListResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	case SECURITY_DEFINITION_RESPONSE:
	{
		s_SecurityDefinitionResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}


	case SECURITY_DEFINITION_REJECT:
	{
		s_SecurityDefinitionReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

		// Account balance
	case ACCOUNT_BALANCE_REJECT:
	{
		s_AccountBalanceReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case ACCOUNT_BALANCE_UPDATE:
	{
		s_AccountBalanceUpdate m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

		// Logging
	case USER_MESSAGE:
	{
		s_UserMessage m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case GENERAL_LOG_MESSAGE:
	{
		s_GeneralLogMessage m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

		// Historical price data
	case HISTORICAL_PRICE_DATA_RESPONSE_HEADER:
	{
		s_HistoricalPriceDataResponseHeader m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HISTORICAL_PRICE_DATA_REJECT:
	{
		s_HistoricalPriceDataReject m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HISTORICAL_PRICE_DATA_RECORD_RESPONSE:
	{
		s_HistoricalPriceDataRecordResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE:
	{
		s_HistoricalPriceDataTickRecordResponse m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HISTORICAL_PRICE_DATA_RECORD_RESPONSE_INT:
	{
		s_HistoricalPriceDataRecordResponse_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE_INT:
	{
		s_HistoricalPriceDataTickRecordResponse_Int m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}
	case HISTORICAL_PRICE_DATA_RESPONSE_TRAILER:
	{
		s_HistoricalPriceDataResponseTrailer m; m.CopyFrom((void*)m_in.data());
		receive(&m); break;
	}

	default:
		err(("Received unknown msg type: " + std::to_string((int)t)).c_str());
		break;
	}
}

void client::receive(s_LogonResponse* m) {
	server_settings = *m;
	if (m->GetHistoricalPriceDataSupported())
		err("#" + (std::string)server_settings.GetResultText()); // Historical socket is too verbose!
	else err(server_settings.GetResultText());

	if (conf.id == uint8_t(1)) {
		if (!m->GetTradingIsSupported()) err("WARNING: Trading not supported");
		if (!m->GetMarketDataSupported()) err("WARNING: Market data not supported");
		if (!m->GetSecurityDefinitionsSupported()) err("WARNING: Security definitions not supported");
		if (!m->GetMarketDepthIsSupported()) err("NOTE: Market depth not supported");
		if (m->GetMarketDepthUpdatesBestBidAndAsk()) err("DEVNOTE: Market depth updates best bid and ask");
	}
	if (b.solicit == sol_LogonResponse) {
		if (server_settings.GetResult() != LOGON_SUCCESS) b.unblock(false);
		else b.unblock(true);
	}
}
void client::receive(s_Heartbeat* m) {
	if (m->GetNumDroppedMessages())
	{
		err(("Server: " + std::to_string((int)m->GetNumDroppedMessages()) + " messages dropped!").c_str());
	}
}
void client::receive(s_Logoff* m) {
	err(m->GetReason());
	stop();
	b.unblock(false);
}
void client::receive(s_EncodingResponse* m) {}

// Market data
void client::receive(s_MarketDataReject* m) {
	err(m->GetRejectText());
	
	b.unblock(false); // No need to filter this due to one-second pause upon subscription

	market_trigger();
}
void client::receive(s_MarketDataSnapshot* m) {
	market.Snapshot(m);
	if (
		(b.solicit == sol_MarketDataSnapshot_SymbolID) &&
		(m->GetSymbolID() == b.solicit_ID) 
		)
	{
		b.unblock(true);
	}
	market_trigger();
}
void client::receive(s_MarketDataSnapshot_Int* m) { market_trigger(); }

void client::receive(s_MarketDataUpdateTrade* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->LastTradeDateTime = m->GetDateTime();
	s->LastTradePrice = m->GetPrice();
	s->LastTradeVolume = m->GetVolume();
	s->SessionVolume += m->GetVolume();
	s->SessionNumTrades++;
	market_trigger();
}
void client::receive(s_MarketDataUpdateTradeCompact* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->LastTradeDateTime = (t_DateTimeWithMilliseconds)m->GetDateTime();
	s->LastTradePrice = (double)m->GetPrice();
	s->LastTradeVolume = (double)m->GetVolume();
	s->SessionVolume += (double)m->GetVolume();
	s->SessionNumTrades++;
	market_trigger();
}
void client::receive(s_MarketDataUpdateTrade_Int* m) { market_trigger(); }
void client::receive(s_MarketDataUpdateLastTradeSnapshot* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->LastTradeDateTime = m->GetLastTradeDateTime();
	s->LastTradePrice = m->GetLastTradePrice();
	s->LastTradeVolume = m->GetLastTradeVolume();
	market_trigger();
}
void client::receive(s_MarketDataUpdateTradeWithUnbundledIndicator* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->LastTradeDateTime = m->GetDateTime();
	s->LastTradePrice = m->GetPrice();
	s->LastTradeVolume = m->GetVolume();
	s->SessionVolume += m->GetVolume();
	s->SessionNumTrades++;
	// m->GetUnbundledTradeIndicator() // ?????
	market_trigger();
}

void client::receive(s_MarketDataUpdateBidAsk* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->AskPrice = m->GetAskPrice();
	s->AskQuantity = m->GetAskQuantity();
	s->BidPrice = m->GetBidPrice();
	s->BidQuantity = m->GetBidQuantity();
	s->BidAskDateTime = m->GetDateTime();
	market_trigger();
}
void client::receive(s_MarketDataUpdateBidAskCompact* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->AskPrice = (double)m->GetAskPrice();
	s->AskQuantity = (double)m->GetAskQuantity();
	s->BidPrice = (double)m->GetBidPrice();
	s->BidQuantity = (double)m->GetBidQuantity();
	s->BidAskDateTime = (t_DateTimeWithMilliseconds)m->GetDateTime();
	market_trigger();
}
void client::receive(s_MarketDataUpdateBidAsk_Int* m) { market_trigger(); }

void client::receive(s_MarketDataUpdateSessionOpen* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->SessionOpenPrice = m->GetPrice();
	s->TradingSessionDate = m->GetTradingSessionDate();
	market_trigger();
}
void client::receive(s_MarketDataUpdateSessionOpen_Int* m) { market_trigger(); }
void client::receive(s_MarketDataUpdateSessionHigh* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->SessionHighPrice = m->GetPrice();
	s->TradingSessionDate = m->GetTradingSessionDate();
	market_trigger();
}
void client::receive(s_MarketDataUpdateSessionHigh_Int* m) { market_trigger(); }
void client::receive(s_MarketDataUpdateSessionLow* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->SessionLowPrice = m->GetPrice();
	s->TradingSessionDate = m->GetTradingSessionDate();
	market_trigger();
}
void client::receive(s_MarketDataUpdateSessionLow_Int* m) { market_trigger(); }
void client::receive(s_MarketDataUpdateSessionVolume* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->SessionVolume = m->GetVolume();
	s->TradingSessionDate = m->GetTradingSessionDate();
	market_trigger();
}
void client::receive(s_MarketDataUpdateOpenInterest* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->OpenInterest = m->GetOpenInterest();
	s->TradingSessionDate = m->GetTradingSessionDate();
	market_trigger();
}
void client::receive(s_MarketDataUpdateSessionSettlement* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	market_trigger();
}
void client::receive(s_MarketDataUpdateSessionSettlement_Int* m) {}
void client::receive(s_MarketDataUpdateSessionNumTrades* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->SessionNumTrades = m->GetNumTrades();
	s->TradingSessionDate = m->GetTradingSessionDate();
	market_trigger();
}
void client::receive(s_MarketDataUpdateTradingSessionDate* m) {
	s_MarketDataSnapshot* s = market.get_snapshot(m->GetSymbolID()); if (!s) return;
	s->TradingSessionDate = m->GetDate();
	market_trigger();
}

void client::receive(s_MarketDepthReject* m) {
	err(m->GetRejectText());
	if ((b.solicit == sol_MarketDepthSnapshot_SymbolID) && (m->GetSymbolID() == b.solicit_ID))
	{
		b.unblock(false);
	}
	market_trigger();
}
void client::receive(s_MarketDepthSnapshotLevel* m) {
	md_update(m->GetSymbolID(), m->GetSide(), m->GetPrice(), m->GetQuantity(),m->GetDateTime());
	// unblock after last snapshot msg received
	if ((b.solicit == sol_MarketDepthSnapshot_SymbolID) &&
		(m->GetSymbolID() == b.solicit_ID) &&
		(m->GetIsLastMessageInBatch())
		)
	{
		b.unblock(true);
	}
}
void client::receive(s_MarketDepthSnapshotLevel_Int* m) { market_trigger(); }
void client::receive(s_MarketDepthUpdateLevel* m) { 
	md_update(m->GetSymbolID(), m->GetSide(), m->GetPrice(), m->GetQuantity(), m->GetDateTime(),m->GetUpdateType());
	market_trigger(); 
}
void client::receive(s_MarketDepthUpdateLevelCompact* m) { 
	md_update(m->GetSymbolID(), m->GetSide(), m->GetPrice(), m->GetQuantity(), m->GetUpdateType(), m->GetUpdateType());
	market_trigger(); 
}
void client::receive(s_MarketDepthUpdateLevel_Int* m) { market_trigger(); }
void client::receive(s_MarketDepthFullUpdate10* m) { 
	auto pK = market.get_symbol_knowledge(m->GetSymbolID());
	if (!pK) return;
	pK->map_pricelevel_askqty.clear();
	pK->map_pricelevel_bidqty.clear();

	for (int i = 0; i < (m->NUM_DEPTH_LEVELS); i++) {
		md_update(m->GetSymbolID(), AT_ASK, m->AskDepth[i].Price, m->AskDepth[i].Quantity,0); //no date
		md_update(m->GetSymbolID(), AT_BID, m->BidDepth[i].Price, m->BidDepth[i].Quantity,0); //no date
	}
	market_trigger(); 
}
void client::receive(s_MarketDepthFullUpdate20* m) { 
	auto pK = market.get_symbol_knowledge(m->GetSymbolID());
	if (!pK) return;
	pK->map_pricelevel_askqty.clear();
	pK->map_pricelevel_bidqty.clear();

	for (int i = 0; i < (m->NUM_DEPTH_LEVELS); i++) {
		md_update(m->GetSymbolID(), AT_ASK, m->AskDepth[i].Price, m->AskDepth[i].Quantity,0); // no date
		md_update(m->GetSymbolID(), AT_BID, m->BidDepth[i].Price, m->BidDepth[i].Quantity,0); // no date
	}
	market_trigger();
}

void client::receive(s_MarketDataFeedStatus* m) { 
	market.feed_status = m->GetStatus();
	std::string str = "";
	switch (market.feed_status){
	case MARKET_DATA_FEED_STATUS_UNSET:
	default:
		str = "unset"; 
		break;
	case MARKET_DATA_FEED_UNAVAILABLE:
		str = "unavailable"; 
		break;	
	case MARKET_DATA_FEED_AVAILABLE:
		str = "available"; 
		break;
	}
	err("Datafeed Status: " + str);
	market_trigger(); 
}
void client::receive(s_MarketDataFeedSymbolStatus* m) { 
	auto pK = market.get_symbol_knowledge(m->GetSymbolID());
	if (!pK) return;

	auto sym = sid.get_existing_symbol(m->GetSymbolID());
	
	pK->symbol_status = m->GetStatus();
	std::string str = "";
	switch (pK->symbol_status) {
	case MARKET_DATA_FEED_STATUS_UNSET:
	default:
		str = "unset"; 
		break;
	case MARKET_DATA_FEED_UNAVAILABLE:
		str = "unavailable"; 
		break;
	case MARKET_DATA_FEED_AVAILABLE:
		str = "available"; 
		break;
	}
	err("Symbol " + sym + " feed Status: " + str);

	market_trigger(); 
}

// Trading related
void client::receive(s_OpenOrdersReject* m) {
	err(m->GetRejectText());
	if ((b.solicit == sol_OrderUpdate_RequestID) && (m->GetRequestID() == b.solicit_ID))
	{
		b.unblock(false);
	}
}
void client::receive(s_OrderUpdate* m) {
	std::string ta = m->GetTradeAccount();
	if (ta == "") ta = tradeaccount_main;
	per_trade_account& pta = m_pta.find(ta)->second;
	
	std::string txt = m->GetInfoText();
	if (txt.size()) err(txt);

	// check if ServerOrderID exists and update
	std::string id = m->GetServerOrderID(); bool found = false;
	for (auto& snap : pta.orders_open)
	{
		if (((std::string)snap.GetServerOrderID()) == id) {
			snap = *m;
			found = true;
			break;
		}
	}
	if (!found) {
		// ServerOrderID does not exist, add it
		pta.orders_open.push_back(*m);
	}


	// is this solicited? If so, break. If not, return because we are done.
	switch (b.solicit)
	{
	case sol_OrderUpdate_RequestID:
		if (m->GetRequestID() == b.solicit_ID) 
			break; 
		else return;
	case sol_OrderUpdate_ClientOrderID:
		if ((std::string)m->GetClientOrderID() == b.solicit_OrderID)
			break; 
		else return;
	case sol_OrderUpdate_ServerOrderID:
		if ((std::string)m->GetServerOrderID() == b.solicit_OrderID)
			break;
		else return;
	default:
		return;
	}

	// Solicited.  Is result good or bad?  Unblock either way.
	switch (m->GetOrderUpdateReason())
	{
	case OPEN_ORDERS_REQUEST_RESPONSE:
	case NEW_ORDER_ACCEPTED:
	case GENERAL_ORDER_UPDATE:
	case ORDER_FILLED:
	case ORDER_FILLED_PARTIALLY:
	case ORDER_CANCEL_REPLACE_COMPLETE:
	case ORDER_CANCELED:
		b.unblock(true);
		return;
	
	case NEW_ORDER_REJECTED:
	case ORDER_CANCEL_REJECTED:
	case ORDER_CANCEL_REPLACE_REJECTED:
		b.unblock(false);
		return;
	case ORDER_UPDATE_REASON_UNSET:
	default:
		break; //??? check order status instead
	}

	// update reason was ambiguous.  Check status
	switch (m->GetOrderStatus())
	{
	case ORDER_STATUS_ORDER_SENT:
	case ORDER_STATUS_PENDING_OPEN:
	case ORDER_STATUS_PENDING_CHILD:
	case ORDER_STATUS_OPEN:
	case ORDER_STATUS_PENDING_CANCEL_REPLACE:
	case ORDER_STATUS_PENDING_CANCEL:
	case ORDER_STATUS_FILLED:
	case ORDER_STATUS_CANCELED:
	case ORDER_STATUS_PARTIALLY_FILLED:
		b.unblock(true);
	case ORDER_STATUS_REJECTED:
		b.unblock(false);
	case ORDER_STATUS_UNSPECIFIED:
	default:
		err("Warning: Order update is ambiguous!");
		b.unblock(false);
	}
}

void client::receive(s_HistoricalOrderFillsReject* m) {
	err(m->GetRejectText());
	if ((b.solicit == sol_HistoricalOrderFillResponse_RequestID) && (m->GetRequestID() == b.solicit_ID))
	{
		b.unblock(false);
	}
}
void client::receive(s_HistoricalOrderFillResponse* m) {
	std::string ta = m->GetTradeAccount();
	if (ta == "") ta = tradeaccount_main;
	per_trade_account& pta = m_pta.find(ta)->second;

	// check if ServerOrderID exists and update
	std::string id = m->GetServerOrderID(); bool found = false;
	for (auto& snap : pta.orders_hist)
	{
		if (((std::string)snap.GetServerOrderID()) != id) continue;
		snap = *m;
		found = true;
		break;
	}
	if (!found)
	{
		// ServerOrderID does not exist, add it
		pta.orders_hist.push_back(*m);
	}

	if (
		(b.solicit == sol_HistoricalOrderFillResponse_RequestID) &&
		(m->GetRequestID() == b.solicit_ID) &&
		(m->GetMessageNumber() == m->GetTotalNumberMessages())
		)
		b.unblock(true);
}

void client::receive(s_CurrentPositionsReject* m) {
	err(m->GetRejectText());
	if ((b.solicit == sol_PositionUpdate_RequestID) && (m->GetRequestID() == b.solicit_ID))
	{
		b.unblock(false);
	}
}
void client::receive(s_PositionUpdate* m) {
	std::string ta = m->GetTradeAccount();
	if (ta == "") ta = tradeaccount_main;
	per_trade_account& pta = m_pta.find(ta)->second;

	// purge if first of solicited messages
	if ((!m->GetUnsolicited()) && m->GetMessageNumber() == 1)
	{
		pta.positions.clear();
	}

	// check if Symbol exists and update
	std::string sym = m->GetSymbol(); bool found = false;
	for (auto& snap : pta.positions)
	{
		if (((std::string)snap.GetSymbol()) != sym) continue;
		snap = *m;
		found = true;
		break;
	}
	if (!found) {
		// Symbol does not exist, add it
		pta.positions.push_back(*m);
	}

	if (
		(b.solicit == sol_PositionUpdate_RequestID) &&
		(m->GetRequestID() == b.solicit_ID) &&
		(m->GetMessageNumber() == m->GetTotalNumberMessages())
		)
		b.unblock(true);
}

// Account list
void client::receive(s_TradeAccountResponse* m) {
	if (
		(m->GetMessageNumber() == 1)
		)
		trade_accounts.clear();
	trade_accounts.push_back(*m);

	if (
		(b.solicit == sol_TradeAccountsResponse_RequestID) &&
		(m->GetRequestID() == b.solicit_ID) &&
		(m->GetMessageNumber() == m->GetTotalNumberMessages())
		)
		b.unblock(true);
}

// Symbol discovery and security definitions
void client::receive(s_ExchangeListResponse* m) {
	// check if this is new request
	if (exchanges.size())
	{
		const s_ExchangeListResponse& last = exchanges.back();
		if (last.GetRequestID() != m->GetRequestID())
			exchanges.clear();
	}

	exchanges.push_back(*m);


	if (
		(b.solicit == sol_ExchangeListResponse_RequestID) &&
		(m->GetRequestID() == b.solicit_ID) &&
		m->GetIsFinalMessage()
		)
		b.unblock(true);
}
void client::receive(s_SecurityDefinitionResponse* m) {

	// security_definitions is where all known assets are indexed

	// check if Symbol exists and update
	std::string 
		sym = m->GetSymbol(), 
		description = m->GetDescription();
	bool found = false;
	//err((
	//	"RECEIVED DEF: \"" + sym +
	//	//"\", TYPE: " + std::to_string((int)m->GetSecurityType()) +
	//	//", CVPI: " + std::to_string((float)m->GetCurrencyValuePerIncrement()) +
	//	//", INCR: " + std::to_string((float)m->GetMinPriceIncrement()) +
	//	", EXP: " + std::to_string(m->GetSecurityExpirationDate())
	//	).c_str()); // delete this
	//err("Description: " + (std::string)m->GetDescription());
	if (
		sym.size() && // filter out definitions without a symbol
		description.size()
		//m->GetCurrencyValuePerIncrement() && //not always available
		//m->GetMinPriceIncrement()// filter out definitions missing this value
		// Filter by description, per SC staff recommendation: 
		// https://www.sierrachart.com/SupportBoard.php?ThreadID=37923
		)
	{
		for (auto& def : security_definitions)
		{
			if (((std::string)def.GetSymbol()) != sym) continue;
			def = *m;
			found = true;
			break;
		}
		if (!found) {
			// Symbol does not exist, add it
			security_definitions.push_back(*m);
		}
	}

	// security_definitions_latest only has the latest response batch, unfiltered.
	if (next_is_new)
	{
		security_definitions_latest.clear();
		next_is_new = false;
	}
	if (m->GetIsFinalMessage()) next_is_new = true;
	security_definitions_latest.push_back(*m);


	if (
		(b.solicit == sol_SecurityDefinitionResponse_RequestID) &&
		(m->GetRequestID() == b.solicit_ID) &&
		m->GetIsFinalMessage()
		)
	{
		if(((std::string)m->GetDescription()).size())b.unblock(true);
		else b.unblock(false);
	}
}
void client::receive(s_SecurityDefinitionReject* m) {
	err("SECURITY DEFINITION REJECT");
	err(m->GetRejectText());
	if (
		(b.solicit == sol_SecurityDefinitionResponse_RequestID) &&
		(m->GetRequestID() == b.solicit_ID)
		)
	{
		b.unblock(false);
	}
}

// Account balance
void client::receive(s_AccountBalanceReject* m) {
	err(m->GetRejectText());
	if ((b.solicit == sol_AccountBalanceUpdate_RequestID) && (m->GetRequestID() == b.solicit_ID))
	{
		b.unblock(false);
	}
}
void client::receive(s_AccountBalanceUpdate* m) {
	std::string ta = m->GetTradeAccount();
	if (ta == "") ta = tradeaccount_main;
	per_trade_account& pta = m_pta.find(ta)->second;

	// check if balance is correct balance to be updated. if so, update.

	// case 1: this was requested. We don't care whether or not TradeAccount is specified.
	if (
		(b.solicit == sol_AccountBalanceUpdate_RequestID) &&
		(m->GetRequestID() == b.solicit_ID) &&
		(m->GetMessageNumber() == m->GetTotalNumberMessages())
		)
	{
		pta.balance = *m;
		b.unblock(true);
	}
	else // case 2: server sent an unsolicited update. confirm tradeaccount first.
	{
		if (((std::string)m->GetTradeAccount()) == conf.tradeaccount) pta.balance = *m;
	}
}

// Logging
void client::receive(s_UserMessage* m) {
	err(m->GetUserMessage());
}
void client::receive(s_GeneralLogMessage* m) {
	err(m->GetMessageText());
}

// Historical price data
void client::receive(s_HistoricalPriceDataResponseHeader* m) {
	h_header = *m;
	h_bars.clear();
	h_ticks.clear();

	if (m->GetUseZLibCompression())
		inflate_mode = true;

	if (
		m->GetNoRecordsToReturn()
		)
	{
		b.unblock(true);
	}
	
}
void client::receive(s_HistoricalPriceDataReject* m) {
	err(m->GetRejectText());
	b.unblock(false);
}
void client::receive(s_HistoricalPriceDataRecordResponse* m) {
	
	h_bars.push_back(*m);
	if (
		m->GetIsFinalRecord() &&
		(b.solicit == sol_HistoricalPriceData_RequestID) &&
		(m->GetRequestID() == b.solicit_ID)
		)
		b.unblock(true);
}
void client::receive(s_HistoricalPriceDataTickRecordResponse* m) {
	// check if this is new request
	if (h_ticks.size())
	{
		const s_HistoricalPriceDataTickRecordResponse& last = h_ticks.back();
		if (last.GetRequestID() != m->GetRequestID())
			h_ticks.clear();
	}
	h_ticks.push_back(*m);
	if (
		m->GetIsFinalRecord() &&
		(b.solicit == sol_HistoricalPriceData_RequestID) &&
		(m->GetRequestID() == b.solicit_ID)
		)
		b.unblock(true);
}
void client::receive(s_HistoricalPriceDataRecordResponse_Int* m) {
	if (
		m->GetIsFinalRecord() &&
		(b.solicit == sol_HistoricalPriceData_RequestID) &&
		(m->GetRequestID() == b.solicit_ID)
		)
		b.unblock(true);
}
void client::receive(s_HistoricalPriceDataTickRecordResponse_Int* m) {
	if (
		m->GetIsFinalRecord() &&
		(b.solicit == sol_HistoricalPriceData_RequestID) &&
		(m->GetRequestID() == b.solicit_ID)
		)
		b.unblock(true);
}
void client::receive(s_HistoricalPriceDataResponseTrailer* m) {
	if ((b.solicit == sol_HistoricalPriceData_RequestID) && (m->GetRequestID() == b.solicit_ID))
		b.unblock(true);
}