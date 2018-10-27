#pragma once


#include "DTCTools.h"

//#include <vector>
#include <algorithm> // std::max
#include <sstream>
using namespace DTC;


namespace DTCTools
{

	s_MsgTypeIndex GetTypeIndex(const uint16_t messageType)
	{
		//struct s_MsgTypeSupportStatus members, default values:
		uint16_t Size = 0;
		int Status = MT_STATUS_SUPPORTED;
		std::string Name = "";
		

		switch (messageType)
		{

		case DTC::LOGON_REQUEST:
			Size = sizeof(DTC::s_LogonRequest);
			Name = "LogonRequest";
			break;
		case DTC::LOGON_RESPONSE:
			Size = sizeof(DTC::s_LogonResponse);
			Name = "LogonResponse";
			break;
		case DTC::HEARTBEAT:
			Size = sizeof(DTC::s_Heartbeat);
			Name = "Heartbeat";
			break;
		case DTC::LOGOFF:
			Size = sizeof(DTC::s_Logoff);
			Name = "Logoff";
			break;
		case DTC::ENCODING_REQUEST:
			Size = sizeof(DTC::s_EncodingRequest);
			Name = "EncodingRequest";
			break;
		case DTC::ENCODING_RESPONSE:
			Name = "EncodingResponse";
			Size = sizeof(DTC::s_EncodingResponse);
			break;
		case DTC::MARKET_DATA_REQUEST:
			Size = sizeof(DTC::s_MarketDataRequest);
			Name = "MarketDataRequest";
			break;
		case DTC::MARKET_DATA_REJECT:
			Size = sizeof(DTC::s_MarketDataReject);
			Name = "MarketDataReject";
			break;
		case DTC::MARKET_DATA_SNAPSHOT:
			Size = sizeof(DTC::s_MarketDataSnapshot);
			Name = "MarketDataSnapshot";
			break;
		case DTC::MARKET_DATA_SNAPSHOT_INT:
			Size = sizeof(DTC::s_MarketDataSnapshot_Int);
			Name = "MarketDataSnapshot_Int";
			break;
		case DTC::MARKET_DATA_UPDATE_TRADE:
			Size = sizeof(DTC::s_MarketDataUpdateTrade);
			Name = "MarketDataUpdateTrade";
			break;
		case DTC::MARKET_DATA_UPDATE_TRADE_COMPACT:
			Size = sizeof(DTC::s_MarketDataUpdateTradeCompact);
			Name = "MarketDataUpdateTradeCompact";
			break;
		case DTC::MARKET_DATA_UPDATE_TRADE_INT:
			Size = sizeof(DTC::s_MarketDataUpdateTrade_Int);
			Name = "MarketDataUpdateTrade_Int";
			break;
		case DTC::MARKET_DATA_UPDATE_LAST_TRADE_SNAPSHOT:
			Size = sizeof(DTC::s_MarketDataUpdateLastTradeSnapshot);
			Name = "MarketDataUpdateLastTradeSnapshot";
			break;
		case DTC::MARKET_DATA_UPDATE_BID_ASK:
			Size = sizeof(DTC::s_MarketDataUpdateBidAsk);
			Name = "MarketDataUpdateBidAsk";
			break;
		case DTC::MARKET_DATA_UPDATE_BID_ASK_COMPACT:
			Size = sizeof(DTC::s_MarketDataUpdateBidAskCompact);
			Name = "MarketDataUpdateBidAskCompact";
			break;
		case DTC::MARKET_DATA_UPDATE_BID_ASK_INT:
			Size = sizeof(DTC::s_MarketDataUpdateBidAsk_Int);
			Name = "MarketDataUpdateBidAsk_Int";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_OPEN:
			Size = sizeof(DTC::s_MarketDataUpdateSessionOpen);
			Name = "MarketDataUpdateSessionOpen";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_OPEN_INT:
			Size = sizeof(DTC::s_MarketDataUpdateSessionOpen_Int);
			Name = "MarketDataUpdateSessionOpen_Int";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_HIGH:
			Size = sizeof(DTC::s_MarketDataUpdateSessionHigh);
			Name = "MarketDataUpdateSessionHigh";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_HIGH_INT:
			Size = sizeof(DTC::s_MarketDataUpdateSessionHigh_Int);
			Name = "MarketDataUpdateSessionHigh_Int";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_LOW:
			Size = sizeof(DTC::s_MarketDataUpdateSessionLow);
			Name = "MarketDataUpdateSessionLow";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_LOW_INT:
			Size = sizeof(DTC::s_MarketDataUpdateSessionLow_Int);
			Name = "MarketDataUpdateSessionLow_Int";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_VOLUME:
			Size = sizeof(DTC::s_MarketDataUpdateSessionVolume);
			Name = "MarketDataUpdateSessionVolume";
			break;
		case DTC::MARKET_DATA_UPDATE_OPEN_INTEREST:
			Size = sizeof(DTC::s_MarketDataUpdateOpenInterest);
			Name = "MarketDataUpdateOpenInterest";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_SETTLEMENT:
			Size = sizeof(DTC::s_MarketDataUpdateSessionSettlement);
			Name = "MarketDataUpdateSessionSettlement";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_SETTLEMENT_INT:
			Size = sizeof(DTC::s_MarketDataUpdateSessionSettlement_Int);
			Name = "MarketDataUpdateSessionSettlement_Int";
			break;
		case DTC::MARKET_DATA_UPDATE_SESSION_NUM_TRADES:
			Size = sizeof(DTC::s_MarketDataUpdateSessionNumTrades);
			Name = "MarketDataUpdateSessionNumTrades";
			break;
		case DTC::MARKET_DATA_UPDATE_TRADING_SESSION_DATE:
			Size = sizeof(DTC::s_MarketDataUpdateTradingSessionDate);
			Name = "MarketDataUpdateTradingSessionDate";
			break;
		case DTC::MARKET_DEPTH_REQUEST:
			Size = sizeof(DTC::s_MarketDepthRequest);
			Name = "MarketDepthRequest";
			break;
		case DTC::MARKET_DEPTH_REJECT:
			Size = sizeof(DTC::s_MarketDepthReject);
			Name = "MarketDepthReject";
			break;
		case DTC::MARKET_DEPTH_SNAPSHOT_LEVEL:
			Size = sizeof(DTC::s_MarketDepthSnapshotLevel);
			Name = "MarketDepthSnapshotLevel";
			break;
		case DTC::MARKET_DEPTH_SNAPSHOT_LEVEL_INT:
			Size = sizeof(DTC::s_MarketDepthSnapshotLevel_Int);
			Name = "MarketDepthSnapshotLevel_Int";
			break;
		case DTC::MARKET_DEPTH_UPDATE_LEVEL:
			Size = sizeof(DTC::s_MarketDepthUpdateLevel);
			Name = "MarketDepthUpdateLevel";
			break;
		case DTC::MARKET_DEPTH_UPDATE_LEVEL_COMPACT:
			Size = sizeof(DTC::s_MarketDepthUpdateLevelCompact);
			Name = "MarketDepthUpdateLevelCompact";
			break;
		case DTC::MARKET_DEPTH_UPDATE_LEVEL_INT:
			Size = sizeof(DTC::s_MarketDepthUpdateLevel_Int);
			Name = "MarketDepthUpdateLevel_Int";
			break;
		case DTC::MARKET_DEPTH_FULL_UPDATE_10:
			Size = sizeof(DTC::s_MarketDepthFullUpdate10);
			Name = "MarketDepthFullUpdate10";
			break;
		case DTC::MARKET_DEPTH_FULL_UPDATE_20:
			Size = sizeof(DTC::s_MarketDepthFullUpdate20);
			Name = "MarketDepthFullUpdate20";
			break;
		case DTC::MARKET_DATA_FEED_STATUS:
			Size = sizeof(DTC::s_MarketDataFeedStatus);
			Name = "MarketDataFeedStatus";
			break;
		case DTC::MARKET_DATA_FEED_SYMBOL_STATUS:
			Size = sizeof(DTC::s_MarketDataFeedSymbolStatus);
			Name = "MarketDataFeedSymbolStatus";
			break;
		case DTC::SUBMIT_NEW_SINGLE_ORDER:
			Size = sizeof(DTC::s_SubmitNewSingleOrder);
			Name = "SubmitNewSingleOrder";
			break;
		case DTC::SUBMIT_NEW_SINGLE_ORDER_INT:
			Size = sizeof(DTC::s_SubmitNewSingleOrderInt);
			Name = "SubmitNewSingleOrderInt";
			break;
		case DTC::SUBMIT_NEW_OCO_ORDER:
			Size = sizeof(DTC::s_SubmitNewOCOOrder);
			Name = "SubmitNewOCOOrder";
			break;
		case DTC::SUBMIT_NEW_OCO_ORDER_INT:
			Size = sizeof(DTC::s_SubmitNewOCOOrderInt);
			Name = "SubmitNewOCOOrderInt";
			break;
		case DTC::CANCEL_ORDER:
			Size = sizeof(DTC::s_CancelOrder);
			Name = "CancelOrder";
			break;
		case DTC::CANCEL_REPLACE_ORDER:
			Size = sizeof(DTC::s_CancelReplaceOrder);
			Name = "CancelReplaceOrder";
			break;
		case DTC::CANCEL_REPLACE_ORDER_INT:
			Size = sizeof(DTC::s_CancelReplaceOrderInt);
			Name = "CancelReplaceOrder_Int";
			break;
		case DTC::OPEN_ORDERS_REQUEST:
			Size = sizeof(DTC::s_OpenOrdersRequest);
			Name = "OpenOrdersRequest";
			break;
		case DTC::OPEN_ORDERS_REJECT:
			Size = sizeof(DTC::s_OpenOrdersReject);
			Name = "OpenOrdersReject";
			break;
		case DTC::ORDER_UPDATE:
			Size = sizeof(DTC::s_OrderUpdate);
			Name = "OrderUpdate";
			break;
		case DTC::HISTORICAL_ORDER_FILLS_REQUEST:
			Size = sizeof(DTC::s_HistoricalOrderFillsRequest);
			Name = "HistoricalOrderFillsRequest";
			break;
		case DTC::HISTORICAL_ORDER_FILLS_REJECT:
			Size = sizeof(DTC::s_HistoricalOrderFillsReject);
			Name = "HistoricalOrderFillsReject";
			break;
		case DTC::HISTORICAL_ORDER_FILL_RESPONSE:
			Size = sizeof(DTC::s_HistoricalOrderFillResponse);
			Name = "HistoricalOrderFillResponse";
			break;
		case DTC::CURRENT_POSITIONS_REQUEST:
			Size = sizeof(DTC::s_CurrentPositionsRequest);
			Name = "CurrentPositionsRequest";
			break;
		case DTC::CURRENT_POSITIONS_REJECT:
			Size = sizeof(DTC::s_CurrentPositionsReject);
			Name = "CurrentPositionsReject";
			break;
		case DTC::POSITION_UPDATE:
			Size = sizeof(DTC::s_PositionUpdate);
			Name = "PositionUpdate";
			break;
		case DTC::TRADE_ACCOUNTS_REQUEST:
			Size = sizeof(DTC::s_TradeAccountsRequest);
			Name = "TradeAccountsRequest";
			break;
		case DTC::TRADE_ACCOUNT_RESPONSE:
			Size = sizeof(DTC::s_TradeAccountResponse);
			Name = "TradeAccountResponse";
			break;
		case DTC::EXCHANGE_LIST_REQUEST:
			Size = sizeof(DTC::s_ExchangeListRequest);
			Name = "ExchangeListRequest";
			break;
		case DTC::EXCHANGE_LIST_RESPONSE:
			Size = sizeof(DTC::s_ExchangeListResponse);
			Name = "ExchangeListResponse";
			break;
		case DTC::SYMBOLS_FOR_EXCHANGE_REQUEST:
			Size = sizeof(DTC::s_SymbolsForExchangeRequest);
			Name = "SymbolsForExchangeRequest";
			break;
		case DTC::UNDERLYING_SYMBOLS_FOR_EXCHANGE_REQUEST:
			Size = sizeof(DTC::s_UnderlyingSymbolsForExchangeRequest);
			Name = "UnderlyingSymbolsForExchangeRequest";
			break;
		case DTC::SYMBOLS_FOR_UNDERLYING_REQUEST:
			Size = sizeof(DTC::s_SymbolsForUnderlyingRequest);
			Name = "SymbolsForUnderlyingRequest";
			break;
		case DTC::SECURITY_DEFINITION_FOR_SYMBOL_REQUEST:
			Size = sizeof(DTC::s_SecurityDefinitionForSymbolRequest);
			Name = "SecurityDefinitionForSymbolRequest";
			break;
		case DTC::SECURITY_DEFINITION_RESPONSE:
			Size = sizeof(DTC::s_SecurityDefinitionResponse);
			Name = "SecurityDefinitionResponse";
			break;
		case DTC::SYMBOL_SEARCH_REQUEST:
			Size = sizeof(DTC::s_SymbolSearchRequest);
			Name = "SymbolSearchRequest";
			break;
		case DTC::SECURITY_DEFINITION_REJECT:
			Size = sizeof(DTC::s_SecurityDefinitionReject);
			Name = "SecurityDefinitionReject";
			break;
		case DTC::ACCOUNT_BALANCE_REQUEST:
			Size = sizeof(DTC::s_AccountBalanceRequest);
			Name = "AccountBalanceRequest";
			break;
		case DTC::ACCOUNT_BALANCE_REJECT:
			Size = sizeof(DTC::s_AccountBalanceReject);
			Name = "AccountBalanceReject";
			break;
		case DTC::ACCOUNT_BALANCE_UPDATE:
			Size = sizeof(DTC::s_AccountBalanceReject);
			Name = "AccountBalanceUpdate";
			break;
		case DTC::USER_MESSAGE:
			Size = sizeof(DTC::s_UserMessage);
			Name = "UserMessage";
			break;
		case DTC::GENERAL_LOG_MESSAGE:
			Size = sizeof(DTC::s_GeneralLogMessage);
			Name = "GeneralLogMessage";
			break;
		case DTC::HISTORICAL_PRICE_DATA_REQUEST:
			Size = sizeof(DTC::s_HistoricalPriceDataRequest);
			Name = "HistoricalPriceDataRequest";
			break;
		case DTC::HISTORICAL_PRICE_DATA_RESPONSE_HEADER:
			Size = sizeof(DTC::s_HistoricalPriceDataResponseHeader);
			Name = "HistoricalPriceDataResponseHeader";
			break;
		case DTC::HISTORICAL_PRICE_DATA_REJECT:
			Size = sizeof(DTC::s_HistoricalPriceDataReject);
			Name = "HistoricalPriceDataReject";
			break;
		case DTC::HISTORICAL_PRICE_DATA_RECORD_RESPONSE:
			Size = sizeof(DTC::s_HistoricalPriceDataRecordResponse);
			Name = "HistoricalPriceDataRecordResponse";
			break;
		case DTC::HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE:
			Size = sizeof(DTC::s_HistoricalPriceDataTickRecordResponse);
			Name = "HistoricalPriceDataTickRecordResponse";
			break;
		case DTC::HISTORICAL_PRICE_DATA_RECORD_RESPONSE_INT:
			Size = sizeof(DTC::s_HistoricalPriceDataRecordResponse_Int);
			Name = "HistoricalPriceDataRecordResponse_Int";
			break;
		case DTC::HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE_INT:
			Size = sizeof(DTC::s_HistoricalPriceDataTickRecordResponse_Int);
			Name = "HistoricalPriceDataTickRecordResponse_Int";
			break;
		case DTC::HISTORICAL_PRICE_DATA_RESPONSE_TRAILER:
			Size = sizeof(DTC::s_HistoricalPriceDataTickRecordResponse_Int);
			Name = "HistoricalPriceDataTickRecordResponse_Int";
			break;
		default:
			std::string Name = "Undefined";
			Status = MT_STATUS_UNSUPPORTED;
		}
		return(s_MsgTypeIndex{Size,Status,Name});
	}
	
	uint16_t GetMaxSize()
	{
		static uint16_t maximum = 0;
		static bool initialized = false;
		if (initialized) return maximum;  // no need to repeat iterative calculation
		for (int i = 0; i < 1000; i++)
		{
			s_MsgTypeIndex mti = GetTypeIndex(i);
			maximum = std::max(maximum, mti.Size);
		}
		initialized = true;
		return maximum;
	}
	uint16_t GetMinSize()
	{
		static uint16_t minimum = USHRT_MAX;
		static bool initialized = false;
		if (initialized) return minimum;  // no need to repeat iterative calculation
		for (int i = 0; i < 1000; i++)
		{
			s_MsgTypeIndex mti = GetTypeIndex(i);
			minimum = std::min(minimum, mti.Size);
		}
		initialized = true;
		return minimum;
	}
	std::string charVectorsToString(const std::vector<char>& cv1, const std::vector<char>& cv2)
	{
		std::vector<char> cv_out;
		cv_out.reserve(cv1.size() + cv2.size());
		cv_out.insert(cv_out.end(), cv1.begin(), cv1.end());
		cv_out.insert(cv_out.end(), cv2.begin(), cv2.end());

		return (std::string(cv_out.begin(), cv_out.end()));
	}


	std::string GetTypeName(const uint16_t messageType)
	{
		//s_MsgTypeIndex mti = GetTypeIndex(messageType);
		//return(mti.Name);
		return(GetTypeIndex(messageType).Name);
	}

	s_Header stringToHeader(std::string sbuffer)
	{
		return(*(s_Header*)sbuffer.data());
	}
	uint16_t stringToMsgType(std::string sbuffer)
	{
		return(s_Header(stringToHeader(sbuffer)).Type);
	}

	uint16_t getMsgSizeFromBuffer(std::vector<char> cbuffer)
	{
		s_Header h = *(s_Header*)cbuffer.data();
		return(h.Size);
	}

	DATE convertTime(DTC::t_DateTimeWithMilliseconds epoch_time)
	{
		return (DATE)epoch_time / (24.*60.*60.) + 25569.; // 25569. = DATE(1.1.1970 00:00)
	}
	DATE convertTime(DTC::t_DateTime epoch_time)
	{
		return (std::round(((DATE)epoch_time / (24.*60.*60.) + 25569.)*(24.*60.*60.)) / (24.*60.*60.)); // 25569. = DATE(1.1.1970 00:00)
	}
	DATE convertTime(DTC::t_DateTime4Byte epoch_time)
	{
		return (std::round(((DATE)epoch_time / (24.*60.*60.) + 25569.)*(24.*60.*60.)) / (24.*60.*60.)); // 25569. = DATE(1.1.1970 00:00)
	}



	DTC::t_DateTimeWithMilliseconds convertDate_1ms(DATE date_input)
	{
		return (DTC::t_DateTimeWithMilliseconds)((date_input - 25569.)*24.*60.*60.);
	}
	DTC::t_DateTime4Byte convertDate_1sec32bit(DATE date_input)
	{
		return (DTC::t_DateTime4Byte)round((date_input - 25569.)*24.*60.*60.);
	}
	DTC::t_DateTime convertDate_1sec64bit(DATE date_input)
	{
		return (DTC::t_DateTime)round((date_input - 25569.)*24.*60.*60.);
	}

	DTC::t_DateTime4Byte convertDate_1day(DATE date_input)
	{
		return (DTC::t_DateTime4Byte)(round(((date_input - 25569.)*24.*60.*60.) / (24.*60.*60.)) * (24.*60.*60.));
	}
	

	//int32_t RequestIDList::get_request_id(uint16_t Type)
	//{
	//	for (auto& entry : v_requestIDEntries_)
	//	{
	//		if (entry.Type == Type)
	//		{
	//			return ++entry.LastRequestID;
	//		}
	//	}

	//	// no matches, add entry
	//	s_RequestIDEntry new_entry;
	//	new_entry.Type = Type;
	//	v_requestIDEntries_.push_back(new_entry);
	//	return new_entry.LastRequestID;

	//}
	uint32_t SymbolIDList::get_symbolID(s_SecurityDefinitionResponse* def)
	{
		std::string Symbol = def->GetSymbol();
		for (auto& entry : v_symbolIDEntries_)
		{
			if (entry.Symbol == Symbol)
			{
				return entry.SymbolID;
			}
		}

		// no matches, add entry
		s_SymbolIDEntry new_entry;
		new_entry.Symbol = Symbol;
		new_entry.Exchange = def->GetExchange();
		new_entry.SymbolID = v_symbolIDEntries_.size() + 1;
		v_symbolIDEntries_.push_back(new_entry);
		return new_entry.SymbolID;
	}
	std::string SymbolIDList::get_existing_symbol(uint32_t SymbolID)
	{
		for (auto& entry : v_symbolIDEntries_)
		{
			if (entry.SymbolID == SymbolID)
			{
				return entry.Symbol;
			}
		}
		// no matches return blank
		return "";
	}


	void resize_msg_string(std::string& msg)
	{
		uint16_t t = stringToMsgType(msg);
		if (t == LOGON_RESPONSE)
		{
			s_LogonResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HEARTBEAT)
		{
			s_Heartbeat m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == LOGOFF)
		{
			s_Logoff m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == ENCODING_RESPONSE)
		{
			s_EncodingResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_REJECT)
		{
			s_MarketDataReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_SNAPSHOT)
		{
			s_MarketDataSnapshot m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_SNAPSHOT_INT)
		{
			s_MarketDataSnapshot_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_TRADE)
		{
			s_MarketDataUpdateTrade m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_TRADE_COMPACT)
		{
			s_MarketDataUpdateTradeCompact m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_TRADE_INT)
		{
			s_MarketDataUpdateTrade_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_LAST_TRADE_SNAPSHOT)
		{
			s_MarketDataUpdateLastTradeSnapshot m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR)
		{
			s_MarketDataUpdateTradeWithUnbundledIndicator m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_BID_ASK)
		{
			s_MarketDataUpdateBidAsk m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_BID_ASK_COMPACT)
		{
			s_MarketDataUpdateBidAskCompact m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_BID_ASK_INT)
		{
			s_MarketDataUpdateBidAsk_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_OPEN)
		{
			s_MarketDataUpdateSessionOpen m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_OPEN_INT)
		{
			s_MarketDataUpdateSessionOpen_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_HIGH)
		{
			s_MarketDataUpdateSessionHigh m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_HIGH_INT)
		{
			s_MarketDataUpdateSessionHigh_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_LOW)
		{
			s_MarketDataUpdateSessionLow m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_LOW_INT)
		{
			s_MarketDataUpdateSessionLow_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_VOLUME)
		{
			s_MarketDataUpdateSessionVolume m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_OPEN_INTEREST)
		{
			s_MarketDataUpdateOpenInterest m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_SETTLEMENT)
		{
			s_MarketDataUpdateSessionSettlement m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_SETTLEMENT_INT)
		{
			s_MarketDataUpdateSessionSettlement_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_SESSION_NUM_TRADES)
		{
			s_MarketDataUpdateSessionNumTrades m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_UPDATE_TRADING_SESSION_DATE)
		{
			s_MarketDataUpdateTradingSessionDate m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_REJECT)
		{
			s_MarketDepthReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_SNAPSHOT_LEVEL)
		{
			s_MarketDepthSnapshotLevel m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_SNAPSHOT_LEVEL_INT)
		{
			s_MarketDepthSnapshotLevel_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_UPDATE_LEVEL)
		{
			s_MarketDepthUpdateLevel m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_UPDATE_LEVEL_COMPACT)
		{
			s_MarketDepthUpdateLevelCompact m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_UPDATE_LEVEL_INT)
		{
			s_MarketDepthUpdateLevel_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_FULL_UPDATE_10)
		{
			s_MarketDepthFullUpdate10 m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DEPTH_FULL_UPDATE_20)
		{
			s_MarketDepthFullUpdate20 m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_FEED_STATUS)
		{
			s_MarketDataFeedStatus m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == MARKET_DATA_FEED_SYMBOL_STATUS)
		{
			s_MarketDataFeedSymbolStatus m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == OPEN_ORDERS_REJECT)
		{
			s_OpenOrdersReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == ORDER_UPDATE)
		{
			s_OrderUpdate m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_ORDER_FILLS_REJECT)
		{
			s_HistoricalOrderFillsReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_ORDER_FILL_RESPONSE)
		{
			s_HistoricalOrderFillResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == CURRENT_POSITIONS_REJECT)
		{
			s_CurrentPositionsReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == POSITION_UPDATE)
		{
			s_PositionUpdate m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == TRADE_ACCOUNT_RESPONSE)
		{
			s_TradeAccountResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == EXCHANGE_LIST_RESPONSE)
		{
			s_ExchangeListResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == SECURITY_DEFINITION_RESPONSE)
		{
			s_SecurityDefinitionResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == SECURITY_DEFINITION_REJECT)
		{
			s_SecurityDefinitionReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == ACCOUNT_BALANCE_REJECT)
		{
			s_AccountBalanceReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == ACCOUNT_BALANCE_UPDATE)
		{
			s_AccountBalanceUpdate m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == USER_MESSAGE)
		{
			s_UserMessage m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == GENERAL_LOG_MESSAGE)
		{
			s_GeneralLogMessage m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_PRICE_DATA_RESPONSE_HEADER)
		{
			s_HistoricalPriceDataResponseHeader m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_PRICE_DATA_REJECT)
		{
			s_HistoricalPriceDataReject m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_PRICE_DATA_RECORD_RESPONSE)
		{
			s_HistoricalPriceDataRecordResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE)
		{
			s_HistoricalPriceDataTickRecordResponse m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_PRICE_DATA_RECORD_RESPONSE_INT)
		{
			s_HistoricalPriceDataRecordResponse_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE_INT)
		{
			s_HistoricalPriceDataTickRecordResponse_Int m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
		else if (t == HISTORICAL_PRICE_DATA_RESPONSE_TRAILER)
		{
			s_HistoricalPriceDataResponseTrailer m;
			m.CopyFrom((void*)msg.data());
			msg.resize(sizeof(m));
			memcpy_s((void*)msg.data(), msg.size(), (void*)&m, sizeof(m));
		}
	}

}
namespace DTCTypes 
{
	const v_uint16_t t_logon =
	{
		LOGON_RESPONSE
	};
	const v_uint16_t t_market_data =
	{
		MARKET_DATA_REJECT, // = 103,
		MARKET_DATA_SNAPSHOT, // = 104,
		MARKET_DATA_SNAPSHOT_INT, // = 125,

		MARKET_DATA_UPDATE_TRADE, // = 107,
		MARKET_DATA_UPDATE_TRADE_COMPACT, // = 112,
		MARKET_DATA_UPDATE_TRADE_INT, // = 126,
		MARKET_DATA_UPDATE_LAST_TRADE_SNAPSHOT, // = 134,
		MARKET_DATA_UPDATE_TRADE_WITH_UNBUNDLED_INDICATOR, // = 137,

		MARKET_DATA_UPDATE_BID_ASK, // = 108,
		MARKET_DATA_UPDATE_BID_ASK_COMPACT, // = 117,
		MARKET_DATA_UPDATE_BID_ASK_INT, // = 127,

		MARKET_DATA_UPDATE_SESSION_OPEN, // = 120,
		MARKET_DATA_UPDATE_SESSION_OPEN_INT, // = 128,
		MARKET_DATA_UPDATE_SESSION_HIGH, // = 114,
		MARKET_DATA_UPDATE_SESSION_HIGH_INT, // = 129,
		MARKET_DATA_UPDATE_SESSION_LOW, // = 115,
		MARKET_DATA_UPDATE_SESSION_LOW_INT, // = 130,
		MARKET_DATA_UPDATE_SESSION_VOLUME, // = 113,
		MARKET_DATA_UPDATE_OPEN_INTEREST, // = 124,
		MARKET_DATA_UPDATE_SESSION_SETTLEMENT, // = 119,
		MARKET_DATA_UPDATE_SESSION_SETTLEMENT_INT, // = 131,
		MARKET_DATA_UPDATE_SESSION_NUM_TRADES, // = 135,
		MARKET_DATA_UPDATE_TRADING_SESSION_DATE, // = 136,

		MARKET_DEPTH_REJECT, // = 121,
		MARKET_DEPTH_SNAPSHOT_LEVEL, // = 122,
		MARKET_DEPTH_SNAPSHOT_LEVEL_INT, // = 132,
		MARKET_DEPTH_UPDATE_LEVEL, // = 106,
		MARKET_DEPTH_UPDATE_LEVEL_COMPACT, // = 118,
		MARKET_DEPTH_UPDATE_LEVEL_INT, // = 133,
		MARKET_DEPTH_FULL_UPDATE_10, // = 123,
		MARKET_DEPTH_FULL_UPDATE_20, // = 105,

		MARKET_DATA_FEED_STATUS, // = 100,
		MARKET_DATA_FEED_SYMBOL_STATUS, // = 116,
	};
	const v_uint16_t t_open_orders =
	{
		OPEN_ORDERS_REJECT,
		ORDER_UPDATE
	};
	const v_uint16_t t_historical_orders =
	{
		HISTORICAL_ORDER_FILLS_REJECT,
		HISTORICAL_ORDER_FILL_RESPONSE
	};
	const v_uint16_t t_positions =
	{
		CURRENT_POSITIONS_REJECT,
		POSITION_UPDATE
	};
	const v_uint16_t t_trade_accounts =
	{
		TRADE_ACCOUNT_RESPONSE
	};
	const v_uint16_t t_exchange_list =
	{
		EXCHANGE_LIST_RESPONSE, // = 501;
	};
	const v_uint16_t t_security_definition =
	{
		SECURITY_DEFINITION_RESPONSE, // = 507;
		SECURITY_DEFINITION_REJECT, // = 509; 
	};
	const v_uint16_t t_account_balance =
	{
		ACCOUNT_BALANCE_REJECT,
		ACCOUNT_BALANCE_UPDATE
	};
	const v_uint16_t t_info =
	{
		USER_MESSAGE,
		GENERAL_LOG_MESSAGE
	};
	const v_uint16_t t_historical_price_data_header =
	{
		HISTORICAL_PRICE_DATA_RESPONSE_HEADER, // = 801;
		HISTORICAL_PRICE_DATA_REJECT, // = 802;
	};
	const v_uint16_t t_historical_price_data =
	{
		HISTORICAL_PRICE_DATA_RECORD_RESPONSE, // = 803;
		HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE, // = 804;
		HISTORICAL_PRICE_DATA_RECORD_RESPONSE_INT, // = 805;
		HISTORICAL_PRICE_DATA_TICK_RECORD_RESPONSE_INT, // = 806;
		HISTORICAL_PRICE_DATA_RESPONSE_TRAILER, // = 807; 
	};

}