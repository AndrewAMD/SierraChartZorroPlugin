#ifndef _CRT_SECURE_NO_WARNINGS
#define  _CRT_SECURE_NO_WARNINGS
#endif

#include <float.h>
#include <limits.h>
#include <string.h>
#include <memory.h> 
#include <stddef.h>

#include "DTCProtocol.h"


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

namespace DTC
{

	/****************************************************************************/
	// s_EncodingRequest

	/*============================================================================
	Will get the size of the message received over the network
	----------------------------------------------------------------------------*/
	uint16_t s_EncodingRequest::GetMessageSize() const
	{
		return Size;
	}

	/*============================================================================
	Performs a safe copy of data into this structure instance from the given
	data pointer.
	----------------------------------------------------------------------------*/
	void s_EncodingRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_EncodingRequest), *static_cast<uint16_t*>( p_SourceData)  ));
	}

	/*==========================================================================*/
	int32_t s_EncodingRequest::GetProtocolVersion() const
	{
		if (Size < offsetof(s_EncodingRequest, ProtocolVersion) + sizeof(ProtocolVersion))
			return 0;

		return ProtocolVersion;
	}

	/*==========================================================================*/
	EncodingEnum s_EncodingRequest::GetEncoding() const
	{
		if (Size < offsetof(s_EncodingRequest, ProtocolVersion) + sizeof(ProtocolVersion))
			return (EncodingEnum)0;

		return Encoding;
	}

	/*==========================================================================*/
	const char* s_EncodingRequest::GetProtocolType()
	{
		if (Size < offsetof(s_EncodingRequest, ProtocolType) + sizeof(ProtocolType))
			return "";

		ProtocolType[sizeof(ProtocolType) - 1] = '\0';  // Ensure that the null terminator exists

		return ProtocolType;
	}

	/*==========================================================================*/
	void s_EncodingRequest::SetProtocolType(const char* NewValue)
	{
		//Do not use the secure version of this function. This version of the function will set the remaining bytes in the destination after the null terminator to nulls. The secure version does not do this.
		strncpy(ProtocolType, NewValue, sizeof(ProtocolType) - 1);
	}

	/****************************************************************************/
	// s_EncodingResponse

	/*============================================================================
	Will get the size of the message received over the network
	----------------------------------------------------------------------------*/
	uint16_t s_EncodingResponse::GetMessageSize() const
	{
		return Size;
	}

	/*============================================================================
	Performs a safe copy of data into this structure instance from the given
	data pointer.
	----------------------------------------------------------------------------*/
	void s_EncodingResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_EncodingResponse), *static_cast<uint16_t*>( p_SourceData)  ));
	}

	/*==========================================================================*/
	int32_t s_EncodingResponse::GetProtocolVersion() const
	{
		if (Size < offsetof(s_EncodingResponse, ProtocolVersion) + sizeof(ProtocolVersion))
			return 0;

		return ProtocolVersion;
	}

	/*==========================================================================*/
	EncodingEnum s_EncodingResponse::GetEncoding() const
	{
		if (Size < offsetof(s_EncodingResponse, ProtocolVersion) + sizeof(ProtocolVersion))
			return (EncodingEnum)0;

		return Encoding;
	}

	/*==========================================================================*/
	const char* s_EncodingResponse::GetProtocolType()
	{
		if (Size < offsetof(s_EncodingResponse, ProtocolType) + sizeof(ProtocolType))
			return "";

		ProtocolType[sizeof(ProtocolType) - 1] = '\0';  // Ensure that the null terminator exists

		return ProtocolType;
	}

	/*==========================================================================*/
	void s_EncodingResponse::SetProtocolType(const char* NewValue)
	{
		strncpy(ProtocolType, NewValue, sizeof(ProtocolType) - 1);
	}

	/****************************************************************************/
	// s_LogonRequest

	/*============================================================================
	Will get the size of the message received over the network
	----------------------------------------------------------------------------*/
	uint16_t s_LogonRequest::GetMessageSize() const
	{
		return Size;
	}

	/*============================================================================
	Performs a safe copy of data into this structure instance from the given
	data pointer.
	----------------------------------------------------------------------------*/
	void s_LogonRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_LogonRequest), *static_cast<uint16_t*>( p_SourceData)  ));
	}

	/*==========================================================================*/
	int32_t s_LogonRequest::GetProtocolVersion() const
	{
		if (Size < offsetof(s_LogonRequest, ProtocolVersion) + sizeof(ProtocolVersion))
			return 0;

		return ProtocolVersion;
	}

	/*==========================================================================*/
	const char* s_LogonRequest::GetUsername()
	{
		if (Size < offsetof(s_LogonRequest, Username) + sizeof(Username))
			return "";

		Username[sizeof(Username) - 1] = '\0';  // Ensure that the null terminator exists

		return Username;
	}

	/*==========================================================================*/
	void s_LogonRequest::SetUsername(const char* NewValue)
	{
		strncpy(Username, NewValue, sizeof(Username) - 1);
	}

	/*==========================================================================*/
	const char* s_LogonRequest::GetPassword()
	{
		if (Size < offsetof(s_LogonRequest, Password) + sizeof(Password))
			return "";

		Password[sizeof(Password) - 1] = '\0';

		return Password;
	}

	/*==========================================================================*/
	void s_LogonRequest::SetPassword(const char* NewValue)
	{
		strncpy(Password, NewValue, sizeof(Password) - 1);
	}

	/*==========================================================================*/
	const char* s_LogonRequest::GetGeneralTextData()
	{
		if (Size < offsetof(s_LogonRequest, GeneralTextData) + sizeof(GeneralTextData))
			return "";

		GeneralTextData[sizeof(GeneralTextData) - 1] = '\0';

		return GeneralTextData;
	}

	/*==========================================================================*/
	void s_LogonRequest::SetGeneralTextData(const char* NewValue)
	{
		strncpy(GeneralTextData, NewValue, sizeof(GeneralTextData) - 1);
	}

	/*==========================================================================*/
	int32_t s_LogonRequest::GetInteger_1() const
	{
		if (Size < offsetof(s_LogonRequest, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}
	
	/*==========================================================================*/
	int32_t s_LogonRequest::GetInteger_2() const
	{
		if (Size < offsetof(s_LogonRequest, Integer_2) + sizeof(Integer_2))
			return 0;

		return Integer_2;
	}

	/*==========================================================================*/
	int32_t s_LogonRequest::GetHeartbeatIntervalInSeconds() const
	{
		if (Size < offsetof(s_LogonRequest, HeartbeatIntervalInSeconds) + sizeof(HeartbeatIntervalInSeconds))
			return 0;

		return HeartbeatIntervalInSeconds;
	}

	/*==========================================================================*/
	TradeModeEnum s_LogonRequest::GetTradeMode() const
	{
		if (Size < offsetof(s_LogonRequest, TradeMode) + sizeof(TradeMode))
			return (TradeModeEnum)0;

		return TradeMode;
	}

	/*==========================================================================*/
	const char* s_LogonRequest::GetTradeAccount()
	{
		if (Size < offsetof(s_LogonRequest, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}

	/*==========================================================================*/
	void s_LogonRequest::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_LogonRequest::GetHardwareIdentifier()
	{
		if (Size < offsetof(s_LogonRequest, HardwareIdentifier) + sizeof(HardwareIdentifier))
			return "";

		HardwareIdentifier[sizeof(HardwareIdentifier) - 1] = '\0';

		return HardwareIdentifier;
	}

	/*==========================================================================*/
	void s_LogonRequest::SetHardwareIdentifier(const char* NewValue)
	{
		strncpy(HardwareIdentifier, NewValue, sizeof(HardwareIdentifier) - 1);
	}

	/*==========================================================================*/
	const char* s_LogonRequest::GetClientName()
	{
		if (Size < offsetof(s_LogonRequest, ClientName) + sizeof(ClientName))
			return "";

		ClientName[sizeof(ClientName) - 1] = '\0';

		return ClientName;
	}

	/*==========================================================================*/
	void s_LogonRequest::SetClientName(const char* NewValue)
	{
		strncpy(ClientName, NewValue, sizeof(ClientName) - 1);
	}

	/*==========================================================================*/
	int32_t s_LogonRequest::GetMarketDataTransmissionInterval() const
	{
		if (Size < offsetof(s_LogonRequest, MarketDataTransmissionInterval) + sizeof(MarketDataTransmissionInterval))
			return 0;

		return MarketDataTransmissionInterval;
	}

	/****************************************************************************/
	// s_LogonResponse

	/*==========================================================================*/
	uint16_t s_LogonResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_LogonResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_LogonResponse), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	int32_t s_LogonResponse::GetProtocolVersion() const
	{
		if (Size < offsetof(s_LogonResponse, ProtocolVersion) + sizeof(ProtocolVersion))
			return 0;

		return ProtocolVersion;
	}

	/*==========================================================================*/
	LogonStatusEnum s_LogonResponse::GetResult() const
	{
		if (Size < offsetof(s_LogonResponse, Result) + sizeof(Result))
			return (LogonStatusEnum)0;

		return Result;
	}
	
	/*==========================================================================*/
	const char* s_LogonResponse::GetResultText()
	{
		if (Size < offsetof(s_LogonResponse, ResultText) + sizeof(ResultText))
			return "";

		ResultText[sizeof(ResultText) - 1] = '\0';

		return ResultText;
	}

	/*==========================================================================*/
	void s_LogonResponse::SetResultText(const char* NewValue)
	{
		strncpy(ResultText, NewValue, sizeof(ResultText) - 1);
	}

	/*==========================================================================*/
	const char* s_LogonResponse::GetReconnectAddress()
	{
		if (Size < offsetof(s_LogonResponse, ReconnectAddress) + sizeof(ReconnectAddress))
			return "";

		ReconnectAddress[sizeof(ReconnectAddress) - 1] = '\0';

		return ReconnectAddress;
	}

	/*==========================================================================*/
	void s_LogonResponse::SetReconnectAddress(const char* NewValue)
	{
		strncpy(ReconnectAddress, NewValue, sizeof(ReconnectAddress) - 1);
	}

	/*==========================================================================*/
	int32_t s_LogonResponse::GetInteger_1() const
	{
		if (Size < offsetof(s_LogonResponse, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}


	/*==========================================================================*/
	const char* s_LogonResponse::GetServerName()
	{
		if (Size < offsetof(s_LogonResponse, ServerName) + sizeof(ServerName))
			return "";

		ServerName[sizeof(ServerName) - 1] = '\0';

		return ServerName;
	}

	/*==========================================================================*/
	void s_LogonResponse::SetServerName(const char* NewValue)
	{
		strncpy(ServerName, NewValue, sizeof(ServerName) - 1);
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetMarketDepthUpdatesBestBidAndAsk() const
	{
		if (Size < offsetof(s_LogonResponse, MarketDepthUpdatesBestBidAndAsk) + sizeof(MarketDepthUpdatesBestBidAndAsk))
			return 0;

		return MarketDepthUpdatesBestBidAndAsk;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetTradingIsSupported() const
	{
		if (Size < offsetof(s_LogonResponse, TradingIsSupported) + sizeof(TradingIsSupported))
			return 0;

		return TradingIsSupported;
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetOCOOrdersSupported() const
	{
		if (Size < offsetof(s_LogonResponse, OCOOrdersSupported) + sizeof(OCOOrdersSupported))
			return 0;

		return OCOOrdersSupported;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetOrderCancelReplaceSupported() const
	{
		if (Size < offsetof(s_LogonResponse, OrderCancelReplaceSupported) + sizeof(OrderCancelReplaceSupported))
			return 0;

		return OrderCancelReplaceSupported;
	}


	/*==========================================================================*/
	const char* s_LogonResponse::GetSymbolExchangeDelimiter()
	{
		if (Size < offsetof(s_LogonResponse, SymbolExchangeDelimiter) + sizeof(SymbolExchangeDelimiter))
			return "";

		SymbolExchangeDelimiter[sizeof(SymbolExchangeDelimiter) - 1] = '\0';

		return SymbolExchangeDelimiter;
	}

	/*==========================================================================*/
	void s_LogonResponse::SetSymbolExchangeDelimiter(const char* NewValue)
	{
		strncpy(SymbolExchangeDelimiter, NewValue, sizeof(SymbolExchangeDelimiter) - 1);
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetSecurityDefinitionsSupported() const
	{
		if (Size < offsetof(s_LogonResponse, SecurityDefinitionsSupported) + sizeof(SecurityDefinitionsSupported))
			return 0;

		return SecurityDefinitionsSupported;
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetHistoricalPriceDataSupported() const
	{
		if (Size < offsetof(s_LogonResponse, HistoricalPriceDataSupported) + sizeof(HistoricalPriceDataSupported))
			return 0;

		return HistoricalPriceDataSupported;
	}


	/*==========================================================================*/
	uint8_t s_LogonResponse::GetResubscribeWhenMarketDataFeedAvailable() const
	{
		if (Size < offsetof(s_LogonResponse, ResubscribeWhenMarketDataFeedAvailable) + sizeof(ResubscribeWhenMarketDataFeedAvailable))
			return 0;

		return ResubscribeWhenMarketDataFeedAvailable;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetMarketDepthIsSupported() const
	{
		if (Size < offsetof(s_LogonResponse, MarketDepthIsSupported) + sizeof(MarketDepthIsSupported))
			return 0;

		return MarketDepthIsSupported;
	}
	/*==========================================================================*/
	uint8_t s_LogonResponse::GetOneHistoricalPriceDataRequestPerConnection() const
	{
		if (Size < offsetof(s_LogonResponse, OneHistoricalPriceDataRequestPerConnection) + sizeof(OneHistoricalPriceDataRequestPerConnection))
			return 0;

		return OneHistoricalPriceDataRequestPerConnection;
	}
	/*==========================================================================*/
	uint8_t s_LogonResponse::GetUseIntegerPriceOrderMessages() const
	{
		if (Size < offsetof(s_LogonResponse, UseIntegerPriceOrderMessages) + sizeof(UseIntegerPriceOrderMessages))
			return 0;

		return UseIntegerPriceOrderMessages;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetBracketOrdersSupported() const
	{
		if (Size < offsetof(s_LogonResponse, BracketOrdersSupported) + sizeof(BracketOrdersSupported))
			return 0;

		return BracketOrdersSupported;
	}
	
	/*==========================================================================*/
	uint8_t s_LogonResponse::GetUsesMultiplePositionsPerSymbolAndTradeAccount() const
	{
		if (Size < offsetof(s_LogonResponse, UsesMultiplePositionsPerSymbolAndTradeAccount) + sizeof(UsesMultiplePositionsPerSymbolAndTradeAccount))
			return 0;

		return UsesMultiplePositionsPerSymbolAndTradeAccount;
	}

	/*==========================================================================*/
	uint8_t s_LogonResponse::GetMarketDataSupported() const
	{
		if (Size < offsetof(s_LogonResponse, MarketDataSupported) + sizeof(MarketDataSupported))
			return 0;

		return MarketDataSupported;
	}

	/****************************************************************************/
	// s_LogoffRequest

	/*==========================================================================*/
	uint16_t s_Logoff::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_Logoff::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_Logoff), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	const char* s_Logoff::GetReason()
	{
		if (Size < offsetof(s_Logoff, Reason) + sizeof(Reason))
			return "";

		Reason[sizeof(Reason) - 1] = '\0';

		return Reason;
	}
	/*==========================================================================*/
	void s_Logoff::SetReason(const char* NewValue)
	{
		strncpy(Reason, NewValue, sizeof(Reason) - 1);
	}
	/*==========================================================================*/
	uint8_t s_Logoff::GetDoNotReconnect() const
	{
		if (Size < offsetof(s_Logoff, DoNotReconnect) + sizeof(DoNotReconnect))
			return 0;

		return DoNotReconnect;
	}


	/****************************************************************************/
	// s_Heartbeat

	/*==========================================================================*/
	uint16_t s_Heartbeat::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_Heartbeat::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_Heartbeat), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_Heartbeat::GetNumDroppedMessages() const
	{
		if (Size < offsetof(s_Heartbeat, NumDroppedMessages) + sizeof(NumDroppedMessages))
			return 0;

		return NumDroppedMessages;
	}

	/*==========================================================================*/
	t_DateTime s_Heartbeat::GetCurrentDateTime() const
	{
		if (Size < offsetof(s_Heartbeat, CurrentDateTime) + sizeof(CurrentDateTime))
			return 0;

		return CurrentDateTime;
	}

	/****************************************************************************/
	// s_MarketDataFeedStatus

	/*==========================================================================*/
	uint16_t s_MarketDataFeedStatus::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataFeedStatus::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataFeedStatus), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	MarketDataFeedStatusEnum s_MarketDataFeedStatus::GetStatus() const
	{
		if (Size < offsetof(s_MarketDataFeedStatus, Status) + sizeof(Status))
			return (MarketDataFeedStatusEnum)0;

		return Status;
	}


	/****************************************************************************/
	// s_MarketDataFeedSymbolStatus

	/*==========================================================================*/
	uint16_t s_MarketDataFeedSymbolStatus::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataFeedSymbolStatus::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataFeedSymbolStatus), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataFeedSymbolStatus::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataFeedSymbolStatus, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	MarketDataFeedStatusEnum s_MarketDataFeedSymbolStatus::GetStatus() const
	{
		if (Size < offsetof(s_MarketDataFeedSymbolStatus, Status) + sizeof(Status))
			return (MarketDataFeedStatusEnum)0;

		return Status;
	}


	/****************************************************************************/
	// s_TradingSymbolStatus
	/*==========================================================================*/
	uint16_t s_TradingSymbolStatus::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_TradingSymbolStatus::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_TradingSymbolStatus), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_TradingSymbolStatus::GetSymbolID() const
	{
		if (Size < offsetof(s_TradingSymbolStatus, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	TradingStatusEnum s_TradingSymbolStatus::GetStatus() const
	{
		if (Size < offsetof(s_TradingSymbolStatus, Status) + sizeof(Status))
			return (TradingStatusEnum)0;

		return Status;
	}

	/****************************************************************************/
	// s_MarketDataRequest

	/*==========================================================================*/
	uint16_t s_MarketDataRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	RequestActionEnum s_MarketDataRequest::GetRequestAction() const
	{
		if (Size < offsetof(s_MarketDataRequest, RequestAction) + sizeof(RequestAction))
			return (RequestActionEnum)0;

		return RequestAction;
	}


	/*==========================================================================*/
	uint32_t s_MarketDataRequest::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataRequest, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}


	/*==========================================================================*/
	const char* s_MarketDataRequest::GetSymbol()
	{
		if (Size < offsetof(s_MarketDataRequest, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_MarketDataRequest::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_MarketDataRequest::GetExchange()
	{
		if (Size < offsetof(s_MarketDataRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_MarketDataRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	uint32_t s_MarketDataRequest::GetIntervalForSnapshotUpdatesInMilliseconds() const
	{
		if (Size < offsetof(s_MarketDataRequest, IntervalForSnapshotUpdatesInMilliseconds) + sizeof(IntervalForSnapshotUpdatesInMilliseconds))
			return 0;

		return IntervalForSnapshotUpdatesInMilliseconds;
	}

	/****************************************************************************/
	// s_MarketDepthRequest

	/*==========================================================================*/
	uint16_t s_MarketDepthRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	RequestActionEnum s_MarketDepthRequest::GetRequestAction() const
	{
		if (Size < offsetof(s_MarketDepthRequest, RequestAction) + sizeof(RequestAction))
			return (RequestActionEnum)0;

		return RequestAction;
	}


	/*==========================================================================*/
	uint32_t s_MarketDepthRequest::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthRequest, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}


	/*==========================================================================*/
	const char* s_MarketDepthRequest::GetSymbol()
	{
		if (Size < offsetof(s_MarketDepthRequest, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_MarketDepthRequest::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_MarketDepthRequest::GetExchange()
	{
		if (Size < offsetof(s_MarketDepthRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_MarketDepthRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	int32_t s_MarketDepthRequest::GetNumLevels() const
	{
		if (Size < offsetof(s_MarketDepthRequest, NumLevels) + sizeof(NumLevels))
			return 0;

		return NumLevels;
	}


	/****************************************************************************/
	// s_MarketDataReject

	/*==========================================================================*/
	uint16_t s_MarketDataReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataReject), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataReject::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataReject, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	const char* s_MarketDataReject::GetRejectText()
	{
		if (Size < offsetof(s_MarketDataReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}

	/*==========================================================================*/
	void s_MarketDataReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/****************************************************************************/
	// s_MarketDepthReject

	/*==========================================================================*/
	uint16_t s_MarketDepthReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthReject), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthReject::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthReject, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	const char* s_MarketDepthReject::GetRejectText()
	{
		if (Size < offsetof(s_MarketDepthReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}

	/*==========================================================================*/
	void s_MarketDepthReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/****************************************************************************/
	// s_MarketDataSnapshot

	/*==========================================================================*/
	uint16_t s_MarketDataSnapshot::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataSnapshot::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataSnapshot), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataSnapshot::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}


	/*==========================================================================*/
	double s_MarketDataSnapshot::GetSessionSettlementPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SessionSettlementPrice) + sizeof(SessionSettlementPrice))
			return 0;

		return SessionSettlementPrice;
	}


	/*==========================================================================*/
	double s_MarketDataSnapshot::GetSessionOpenPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SessionOpenPrice) + sizeof(SessionOpenPrice))
			return 0;

		return SessionOpenPrice;
	}


	/*==========================================================================*/
	double s_MarketDataSnapshot::GetSessionHighPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SessionHighPrice) + sizeof(SessionHighPrice))
			return 0;

		return SessionHighPrice;
	}


	/*==========================================================================*/
	double s_MarketDataSnapshot::GetSessionLowPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SessionLowPrice) + sizeof(SessionLowPrice))
			return 0;

		return SessionLowPrice;
	}


	/*==========================================================================*/
	double s_MarketDataSnapshot::GetSessionVolume() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SessionVolume) + sizeof(SessionVolume))
			return 0;

		return SessionVolume;
	}


	/*==========================================================================*/
	uint32_t s_MarketDataSnapshot::GetSessionNumTrades() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SessionNumTrades) + sizeof(SessionNumTrades))
			return 0;

		return SessionNumTrades;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataSnapshot::GetOpenInterest() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, OpenInterest) + sizeof(OpenInterest))
			return 0;

		return OpenInterest;
	}


	/*==========================================================================*/
	double s_MarketDataSnapshot::GetBidPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, BidPrice) + sizeof(BidPrice))
			return 0;

		return BidPrice;
	}

	/*==========================================================================*/
	double s_MarketDataSnapshot::GetAskPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, AskPrice) + sizeof(AskPrice))
			return 0;

		return AskPrice;
	}

	/*==========================================================================*/
	double s_MarketDataSnapshot::GetAskQuantity() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, AskQuantity) + sizeof(AskQuantity))
			return 0;

		return AskQuantity;
	}


	/*==========================================================================*/
	double s_MarketDataSnapshot::GetBidQuantity() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, BidQuantity) + sizeof(BidQuantity))
			return 0;

		return BidQuantity;
	}

	/*==========================================================================*/
	double s_MarketDataSnapshot::GetLastTradePrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, LastTradePrice) + sizeof(LastTradePrice))
			return 0;

		return LastTradePrice;
	}

	/*==========================================================================*/
	double s_MarketDataSnapshot::GetLastTradeVolume() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, LastTradeVolume) + sizeof(LastTradeVolume))
			return 0;

		return LastTradeVolume;
	}
	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataSnapshot::GetLastTradeDateTime() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, LastTradeDateTime) + sizeof(LastTradeDateTime))
			return 0.0;

		return LastTradeDateTime;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataSnapshot::GetBidAskDateTime() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, BidAskDateTime) + sizeof(BidAskDateTime))
			return 0.0;

		return BidAskDateTime;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataSnapshot::GetSessionSettlementDateTime() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, SessionSettlementDateTime) + sizeof(SessionSettlementDateTime))
			return 0;

		return SessionSettlementDateTime;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataSnapshot::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/*==========================================================================*/
	TradingStatusEnum s_MarketDataSnapshot::GetTradingStatus() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, TradingStatus) + sizeof(TradingStatus))
			return TRADING_STATUS_UNKNOWN;

		return TradingStatus;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataSnapshot::GetMarketDepthUpdateDateTime() const
	{
		if (Size < offsetof(s_MarketDataSnapshot, MarketDepthUpdateDateTime) + sizeof(MarketDepthUpdateDateTime))
			return 0.0;

		return MarketDepthUpdateDateTime;
	}

	/****************************************************************************/
	// s_MarketDataSnapshot_Int

	/*==========================================================================*/
	uint16_t s_MarketDataSnapshot_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataSnapshot_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataSnapshot_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataSnapshot_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}


	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetSessionSettlementPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SessionSettlementPrice) + sizeof(SessionSettlementPrice))
			return 0;

		return SessionSettlementPrice;
	}


	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetSessionOpenPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SessionOpenPrice) + sizeof(SessionOpenPrice))
			return 0;

		return SessionOpenPrice;
	}


	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetSessionHighPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SessionHighPrice) + sizeof(SessionHighPrice))
			return 0;

		return SessionHighPrice;
	}


	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetSessionLowPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SessionLowPrice) + sizeof(SessionLowPrice))
			return 0;

		return SessionLowPrice;
	}


	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetSessionVolume() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SessionVolume) + sizeof(SessionVolume))
			return 0;

		return SessionVolume;
	}


	/*==========================================================================*/
	uint32_t s_MarketDataSnapshot_Int::GetSessionNumTrades() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SessionNumTrades) + sizeof(SessionNumTrades))
			return 0;

		return SessionNumTrades;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataSnapshot_Int::GetOpenInterest() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, OpenInterest) + sizeof(OpenInterest))
			return 0;

		return OpenInterest;
	}

	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetBidPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, BidPrice) + sizeof(BidPrice))
			return 0;

		return BidPrice;
	}
	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetAskPrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, AskPrice) + sizeof(AskPrice))
			return 0;

		return AskPrice;
	}

	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetAskQuantity() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, AskQuantity) + sizeof(AskQuantity))
			return 0;

		return AskQuantity;
	}


	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetBidQuantity() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, BidQuantity) + sizeof(BidQuantity))
			return 0;

		return BidQuantity;
	}

	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetLastTradePrice() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, LastTradePrice) + sizeof(LastTradePrice))
			return 0;

		return LastTradePrice;
	}

	/*==========================================================================*/
	int32_t s_MarketDataSnapshot_Int::GetLastTradeVolume() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, LastTradeVolume) + sizeof(LastTradeVolume))
			return 0;

		return LastTradeVolume;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataSnapshot_Int::GetLastTradeDateTime() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, LastTradeDateTime) + sizeof(LastTradeDateTime))
			return 0;

		return LastTradeDateTime;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataSnapshot_Int::GetBidAskDateTime() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, BidAskDateTime) + sizeof(BidAskDateTime))
			return 0;

		return BidAskDateTime;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataSnapshot_Int::GetSessionSettlementDateTime() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, SessionSettlementDateTime) + sizeof(SessionSettlementDateTime))
			return 0;

		return SessionSettlementDateTime;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataSnapshot_Int::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/*==========================================================================*/
	TradingStatusEnum s_MarketDataSnapshot_Int::GetTradingStatus() const
	{
		if (Size < offsetof(s_MarketDataSnapshot_Int, TradingStatus) + sizeof(TradingStatus))
			return TRADING_STATUS_UNKNOWN;

		return TradingStatus;
	}

	/****************************************************************************/
	// s_MarketDepthSnapshotLevelFloat

	/*==========================================================================*/
	uint16_t s_MarketDepthSnapshotLevelFloat::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthSnapshotLevelFloat::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthSnapshotLevelFloat), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthSnapshotLevelFloat::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevelFloat, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	float s_MarketDepthSnapshotLevelFloat::GetPrice() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevelFloat, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	float s_MarketDepthSnapshotLevelFloat::GetQuantity() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevelFloat, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthSnapshotLevelFloat::GetNumOrders() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevelFloat, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/*==========================================================================*/
	uint16_t s_MarketDepthSnapshotLevelFloat::GetLevel() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevelFloat, Level) + sizeof(Level))
			return 0;

		return Level;
	}

	/*==========================================================================*/
	AtBidOrAskEnum8 s_MarketDepthSnapshotLevelFloat::GetSide() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevelFloat, Side) + sizeof(Side))
			return BID_ASK_UNSET_8;

		return Side;
	}

	/*==========================================================================*/
	FinalUpdateInBatchEnum s_MarketDepthSnapshotLevelFloat::GetFinalUpdateInBatch() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevelFloat, FinalUpdateInBatch) + sizeof(FinalUpdateInBatch))
			return FINAL_UPDATE_UNSET;

		return FinalUpdateInBatch;
	}

	/****************************************************************************/
	// s_MarketDepthSnapshotLevel

	/*==========================================================================*/
	uint16_t s_MarketDepthSnapshotLevel::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthSnapshotLevel::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	AtBidOrAskEnum s_MarketDepthSnapshotLevel::GetSide() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, Side) + sizeof(Side))
			return BID_ASK_UNSET;

		return Side;
	}

	/*==========================================================================*/
	double s_MarketDepthSnapshotLevel::GetPrice() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	double s_MarketDepthSnapshotLevel::GetQuantity() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}

	/*==========================================================================*/
	uint16_t s_MarketDepthSnapshotLevel::GetLevel() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, Level) + sizeof(Level))
			return 0;

		return Level;
	}

	/*==========================================================================*/
	uint8_t s_MarketDepthSnapshotLevel::GetIsFirstMessageInBatch() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, IsFirstMessageInBatch) + sizeof(IsFirstMessageInBatch))
			return 0;

		return IsFirstMessageInBatch;
	}

	/*==========================================================================*/
	uint8_t s_MarketDepthSnapshotLevel::GetIsLastMessageInBatch() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, IsLastMessageInBatch) + sizeof(IsLastMessageInBatch))
			return 0;

		return IsLastMessageInBatch;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDepthSnapshotLevel::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, DateTime) + sizeof(DateTime))
			return 0.0;

		return DateTime;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthSnapshotLevel::GetNumOrders() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/*==========================================================================*/
	void s_MarketDepthSnapshotLevel::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthSnapshotLevel), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/****************************************************************************/
	// s_MarketDepthSnapshotLevel_Int

	/*==========================================================================*/
	uint16_t s_MarketDepthSnapshotLevel_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthSnapshotLevel_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthSnapshotLevel_Int), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthSnapshotLevel_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	AtBidOrAskEnum s_MarketDepthSnapshotLevel_Int::GetSide() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, Side) + sizeof(Side))
			return BID_ASK_UNSET;

		return Side;
	}

	/*==========================================================================*/
	int32_t s_MarketDepthSnapshotLevel_Int::GetPrice() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	int32_t s_MarketDepthSnapshotLevel_Int::GetQuantity() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	uint16_t s_MarketDepthSnapshotLevel_Int::GetLevel() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, Level) + sizeof(Level))
			return 0;

		return Level;
	}

	/*==========================================================================*/
	uint8_t s_MarketDepthSnapshotLevel_Int::GetIsFirstMessageInBatch() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, IsFirstMessageInBatch) + sizeof(IsFirstMessageInBatch))
			return 0;

		return IsFirstMessageInBatch;
	}

	/*==========================================================================*/
	uint8_t s_MarketDepthSnapshotLevel_Int::GetIsLastMessageInBatch() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, IsLastMessageInBatch) + sizeof(IsLastMessageInBatch))
			return 0;

		return IsLastMessageInBatch;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDepthSnapshotLevel_Int::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, DateTime) + sizeof(DateTime))
			return 0.0;

		return DateTime;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthSnapshotLevel_Int::GetNumOrders() const
	{
		if (Size < offsetof(s_MarketDepthSnapshotLevel_Int, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/****************************************************************************/
	// s_MarketDepthIncrementalUpdate

	/*==========================================================================*/
	uint16_t s_MarketDepthUpdateLevel::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthUpdateLevel::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthUpdateLevel), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	uint32_t s_MarketDepthUpdateLevel::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	AtBidOrAskEnum s_MarketDepthUpdateLevel::GetSide() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel, Side) + sizeof(Side))
			return BID_ASK_UNSET;

		return Side;
	}
	/*==========================================================================*/
	double s_MarketDepthUpdateLevel::GetPrice() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	double s_MarketDepthUpdateLevel::GetQuantity() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	MarketDepthUpdateTypeEnum s_MarketDepthUpdateLevel::GetUpdateType() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel, UpdateType) + sizeof(UpdateType))
			return MARKET_DEPTH_UNSET;

		return UpdateType;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDepthUpdateLevel::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel, DateTime) + sizeof(DateTime))
			return 0.0;

		return DateTime;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthUpdateLevel::GetNumOrders() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/****************************************************************************/
	// s_MarketDepthIncrementalUpdate_Int

	/*==========================================================================*/
	uint16_t s_MarketDepthUpdateLevel_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthUpdateLevel_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthUpdateLevel_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	uint32_t s_MarketDepthUpdateLevel_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	AtBidOrAskEnum s_MarketDepthUpdateLevel_Int::GetSide() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel_Int, Side) + sizeof(Side))
			return BID_ASK_UNSET;

		return Side;
	}


	/*==========================================================================*/
	int32_t s_MarketDepthUpdateLevel_Int::GetPrice() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	int32_t s_MarketDepthUpdateLevel_Int::GetQuantity() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel_Int, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	MarketDepthUpdateTypeEnum s_MarketDepthUpdateLevel_Int::GetUpdateType() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel_Int, UpdateType) + sizeof(UpdateType))
			return MARKET_DEPTH_UNSET;

		return UpdateType;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDepthUpdateLevel_Int::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel_Int, DateTime) + sizeof(DateTime))
			return 0.0;

		return DateTime;
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthUpdateLevel_Int::GetNumOrders() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevel_Int, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/****************************************************************************/
	// s_MarketDepthUpdateLevelFloatWithMilliseconds

	/*==========================================================================*/
	uint16_t s_MarketDepthUpdateLevelFloatWithMilliseconds::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthUpdateLevelFloatWithMilliseconds::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthUpdateLevelFloatWithMilliseconds), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthUpdateLevelFloatWithMilliseconds::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	t_DateTimeWithMillisecondsInt s_MarketDepthUpdateLevelFloatWithMilliseconds::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	float s_MarketDepthUpdateLevelFloatWithMilliseconds::GetPrice() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	float s_MarketDepthUpdateLevelFloatWithMilliseconds::GetQuantity() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}
	/*==========================================================================*/
	int8_t s_MarketDepthUpdateLevelFloatWithMilliseconds::GetSide() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, Side) + sizeof(Side))
			return 0;

		return Side;
	}

	/*==========================================================================*/
	int8_t s_MarketDepthUpdateLevelFloatWithMilliseconds::GetUpdateType() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, UpdateType) + sizeof(UpdateType))
			return 0;

		return UpdateType;
	}

	/*==========================================================================*/
	uint16_t s_MarketDepthUpdateLevelFloatWithMilliseconds::GetNumOrders() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/*==========================================================================*/
	DTC::FinalUpdateInBatchEnum s_MarketDepthUpdateLevelFloatWithMilliseconds::GetFinalUpdateInBatch() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelFloatWithMilliseconds, FinalUpdateInBatch) + sizeof(FinalUpdateInBatch))
			return FINAL_UPDATE_UNSET;

		return FinalUpdateInBatch;
	}

	/****************************************************************************/
	// s_MarketDepthUpdateLevelNoTimestamp

	/*==========================================================================*/
	uint16_t s_MarketDepthUpdateLevelNoTimestamp::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDepthUpdateLevelNoTimestamp::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDepthUpdateLevelNoTimestamp), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDepthUpdateLevelNoTimestamp::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelNoTimestamp, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	float s_MarketDepthUpdateLevelNoTimestamp::GetPrice() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelNoTimestamp, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	float s_MarketDepthUpdateLevelNoTimestamp::GetQuantity() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelNoTimestamp, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}

	/*==========================================================================*/
	uint16_t s_MarketDepthUpdateLevelNoTimestamp::GetNumOrders() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelNoTimestamp, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/*==========================================================================*/
	int8_t s_MarketDepthUpdateLevelNoTimestamp::GetSide() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelNoTimestamp, Side) + sizeof(Side))
			return 0;

		return Side;
	}

	/*==========================================================================*/
	int8_t s_MarketDepthUpdateLevelNoTimestamp::GetUpdateType() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelNoTimestamp, UpdateType) + sizeof(UpdateType))
			return 0;

		return UpdateType;
	}

	/*==========================================================================*/
	FinalUpdateInBatchEnum s_MarketDepthUpdateLevelNoTimestamp::GetFinalUpdateInBatch() const
	{
		if (Size < offsetof(s_MarketDepthUpdateLevelNoTimestamp, FinalUpdateInBatch) + sizeof(FinalUpdateInBatch))
			return FINAL_UPDATE_UNSET;

		return FinalUpdateInBatch;
	}

	/****************************************************************************/
	// s_MarketDataUpdateTradeNoTimestamp

	uint16_t s_MarketDataUpdateTradeNoTimestamp::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateTradeNoTimestamp::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateTradeNoTimestamp), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradeNoTimestamp::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeNoTimestamp, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateTradeNoTimestamp::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeNoTimestamp, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradeNoTimestamp::GetVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeNoTimestamp, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}

	/*==========================================================================*/
	AtBidOrAskEnum8 s_MarketDataUpdateTradeNoTimestamp::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeNoTimestamp, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET_8;

		return AtBidOrAsk;
	}

	/*==========================================================================*/
	UnbundledTradeIndicatorEnum s_MarketDataUpdateTradeNoTimestamp::GetUnbundledTradeIndicator() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeNoTimestamp, UnbundledTradeIndicator) + sizeof(UnbundledTradeIndicator))
			return UNBUNDLED_TRADE_NONE;

		return UnbundledTradeIndicator;
	}

	/*==========================================================================*/
	DTC::TradeConditionEnum s_MarketDataUpdateTradeNoTimestamp::GetTradeCondition() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeNoTimestamp, TradeCondition) + sizeof(TradeCondition))
			return TRADE_CONDITION_NONE;

		return TradeCondition;
	}

	/****************************************************************************/
	// s_SettlementIncrementalUpdate

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionSettlement::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionSettlement::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionSettlement), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionSettlement::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionSettlement, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateSessionSettlement::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionSettlement, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionSettlement::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionSettlement, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

		/****************************************************************************/
	// s_SettlementIncrementalUpdate_Int

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionSettlement_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionSettlement_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionSettlement_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionSettlement_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionSettlement_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateSessionSettlement_Int::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionSettlement_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionSettlement_Int::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionSettlement_Int, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionOpen

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionOpen::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionOpen::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionOpen), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionOpen::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionOpen, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateSessionOpen::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionOpen, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionOpen::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionOpen, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionOpen_Int

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionOpen_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionOpen_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionOpen_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionOpen_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionOpen_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateSessionOpen_Int::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionOpen_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionOpen_Int::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionOpen_Int, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionNumTrades

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionNumTrades::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionNumTrades::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionNumTrades), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionNumTrades::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionNumTrades, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateSessionNumTrades::GetNumTrades() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionNumTrades, NumTrades) + sizeof(NumTrades))
			return 0;

		return NumTrades;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionNumTrades::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionNumTrades, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateTradingSessionDate

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateTradingSessionDate::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateTradingSessionDate::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateTradingSessionDate), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradingSessionDate::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradingSessionDate, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateTradingSessionDate::GetDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradingSessionDate, Date) + sizeof(Date))
			return 0;

		return Date;
	}


	/****************************************************************************/
	// s_TradeIncrementalUpdate

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateTrade::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateTrade::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateTrade), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTrade::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}
	/*==========================================================================*/
	AtBidOrAskEnum s_MarketDataUpdateTrade::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET;

		return AtBidOrAsk;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateTrade::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateTrade::GetVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}
	/*==========================================================================*/

	t_DateTimeWithMilliseconds s_MarketDataUpdateTrade::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}


	/****************************************************************************/
	// s_TradeIncrementalUpdate_Int

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateTrade_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateTrade_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateTrade_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTrade_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}
	/*==========================================================================*/
	AtBidOrAskEnum s_MarketDataUpdateTrade_Int::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade_Int, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET;

		return AtBidOrAsk;
	}
	/*==========================================================================*/
	int32_t s_MarketDataUpdateTrade_Int::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}
	/*==========================================================================*/
	int32_t s_MarketDataUpdateTrade_Int::GetVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade_Int, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}
	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataUpdateTrade_Int::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateTrade_Int, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_MarketDataUpdateTradeWithUnbundledIndicator

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateTradeWithUnbundledIndicator::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateTradeWithUnbundledIndicator::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateTradeWithUnbundledIndicator), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradeWithUnbundledIndicator::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	AtBidOrAskEnum8 s_MarketDataUpdateTradeWithUnbundledIndicator::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET_8;

		return AtBidOrAsk;
	}

	/*==========================================================================*/
	UnbundledTradeIndicatorEnum s_MarketDataUpdateTradeWithUnbundledIndicator::GetUnbundledTradeIndicator() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator, UnbundledTradeIndicator) + sizeof(UnbundledTradeIndicator))
			return UNBUNDLED_TRADE_NONE;

		return UnbundledTradeIndicator;
	}

	/*==========================================================================*/
	uint8_t s_MarketDataUpdateTradeWithUnbundledIndicator::GetTradeCondition() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator, TradeCondition) + sizeof(TradeCondition))
			return 0;

		return TradeCondition;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateTradeWithUnbundledIndicator::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradeWithUnbundledIndicator::GetVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataUpdateTradeWithUnbundledIndicator::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_MarketDataUpdateTradeWithUnbundledIndicator2

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateTradeWithUnbundledIndicator2::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateTradeWithUnbundledIndicator2::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateTradeWithUnbundledIndicator2), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradeWithUnbundledIndicator2::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator2, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateTradeWithUnbundledIndicator2::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator2, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradeWithUnbundledIndicator2::GetVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator2, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_MarketDataUpdateTradeWithUnbundledIndicator2::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator2, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	AtBidOrAskEnum8 s_MarketDataUpdateTradeWithUnbundledIndicator2::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator2, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET_8;

		return AtBidOrAsk;
	}

	/*==========================================================================*/
	UnbundledTradeIndicatorEnum s_MarketDataUpdateTradeWithUnbundledIndicator2::GetUnbundledTradeIndicator() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeWithUnbundledIndicator2, UnbundledTradeIndicator) + sizeof(UnbundledTradeIndicator))
			return UNBUNDLED_TRADE_NONE;

		return UnbundledTradeIndicator;
	}

	/****************************************************************************/
	// s_QuoteIncrementalUpdate

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateBidAsk::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateBidAsk::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateBidAsk), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateBidAsk::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateBidAsk::GetBidPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk, BidPrice) + sizeof(BidPrice))
			return 0.0;

		return BidPrice;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAsk::GetBidQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk, BidQuantity) + sizeof(BidQuantity))
			return 0;

		return BidQuantity;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateBidAsk::GetAskPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk, AskPrice) + sizeof(AskPrice))
			return 0.0;

		return AskPrice;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAsk::GetAskQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk, AskQuantity) + sizeof(AskQuantity))
			return 0;

		return AskQuantity;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateBidAsk::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_QuoteIncrementalUpdate_Int

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateBidAsk_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateBidAsk_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateBidAsk_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateBidAsk_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateBidAsk_Int::GetBidPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk_Int, BidPrice) + sizeof(BidPrice))
			return 0;

		return BidPrice;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateBidAsk_Int::GetBidQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk_Int, BidQuantity) + sizeof(BidQuantity))
			return 0;

		return BidQuantity;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateBidAsk_Int::GetAskPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk_Int, AskPrice) + sizeof(AskPrice))
			return 0;

		return AskPrice;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateBidAsk_Int::GetAskQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk_Int, AskQuantity) + sizeof(AskQuantity))
			return 0;

		return AskQuantity;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateBidAsk_Int::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAsk_Int, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}


	/****************************************************************************/
	// s_MarketDataUpdateBidAskCompact

	/*==========================================================================*/

	uint16_t s_MarketDataUpdateBidAskCompact::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateBidAskCompact::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateBidAskCompact), *static_cast<uint16_t*>(p_SourceData) ));
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskCompact::GetBidPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskCompact, BidPrice) + sizeof(BidPrice))
			return 0;

		return BidPrice;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskCompact::GetBidQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskCompact, BidQuantity) + sizeof(BidQuantity))
			return 0;

		return BidQuantity;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskCompact::GetAskPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskCompact, AskPrice) + sizeof(AskPrice))
			return  0;

		return AskPrice;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskCompact::GetAskQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskCompact, AskQuantity) + sizeof(AskQuantity))
			return 0;

		return AskQuantity;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateBidAskCompact::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskCompact, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateBidAskCompact::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskCompact, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/****************************************************************************/
	// s_MarketDataUpdateBidAskFloatWithMilliseconds

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateBidAskFloatWithMicroseconds::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateBidAskFloatWithMicroseconds::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateBidAskFloatWithMicroseconds), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateBidAskFloatWithMicroseconds::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskFloatWithMicroseconds, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskFloatWithMicroseconds::GetBidPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskFloatWithMicroseconds, BidPrice) + sizeof(BidPrice))
			return 0.0;

		return BidPrice;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskFloatWithMicroseconds::GetBidQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskFloatWithMicroseconds, BidQuantity) + sizeof(BidQuantity))
			return 0.0;

		return BidQuantity;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskFloatWithMicroseconds::GetAskPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskFloatWithMicroseconds, AskPrice) + sizeof(AskPrice))
			return 0.0;

		return AskPrice;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskFloatWithMicroseconds::GetAskQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskFloatWithMicroseconds, AskQuantity) + sizeof(AskQuantity))
			return 0.0;

		return AskQuantity;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_MarketDataUpdateBidAskFloatWithMicroseconds::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskFloatWithMicroseconds, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_MarketDataUpdateBidAskNoTimeStamp

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateBidAskNoTimeStamp::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateBidAskNoTimeStamp::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateBidAskNoTimeStamp), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateBidAskNoTimeStamp::GetSize() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskNoTimeStamp, Size) + sizeof(Size))
			return 0;

		return Size;
	}

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateBidAskNoTimeStamp::GetType() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskNoTimeStamp, Type) + sizeof(Type))
			return 0;

		return Type;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateBidAskNoTimeStamp::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskNoTimeStamp, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskNoTimeStamp::GetBidPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskNoTimeStamp, BidPrice) + sizeof(BidPrice))
			return 0.0;

		return BidPrice;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateBidAskNoTimeStamp::GetBidQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskNoTimeStamp, BidQuantity) + sizeof(BidQuantity))
			return 0;

		return BidQuantity;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateBidAskNoTimeStamp::GetAskPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskNoTimeStamp, AskPrice) + sizeof(AskPrice))
			return 0.0;

		return AskPrice;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateBidAskNoTimeStamp::GetAskQuantity() const
	{
		if (Size < offsetof(s_MarketDataUpdateBidAskNoTimeStamp, AskQuantity) + sizeof(AskQuantity))
			return 0;

		return AskQuantity;
	}

	/****************************************************************************/
	// s_TradeIncrementalUpdateCompact

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateTradeCompact::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateTradeCompact::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateTradeCompact), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	float s_MarketDataUpdateTradeCompact::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeCompact, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	float s_MarketDataUpdateTradeCompact::GetVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeCompact, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateTradeCompact::GetDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeCompact, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateTradeCompact::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeCompact, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	AtBidOrAskEnum s_MarketDataUpdateTradeCompact::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_MarketDataUpdateTradeCompact, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET;

		return AtBidOrAsk;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionVolume

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionVolume::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionVolume::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionVolume), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionVolume::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionVolume, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateSessionVolume::GetVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionVolume, Volume) + sizeof(Volume))
			return 0.0;

		return Volume;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionVolume::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionVolume, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/*==========================================================================*/
	uint8_t s_MarketDataUpdateSessionVolume::GetIsFinalSessionVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionVolume, IsFinalSessionVolume) + sizeof(IsFinalSessionVolume))
			return 0;

		return IsFinalSessionVolume;
	}

	/****************************************************************************/
	// s_OpenInterestIncrementalUpdate

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateOpenInterest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateOpenInterest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateOpenInterest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateOpenInterest::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionVolume, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateOpenInterest::GetOpenInterest() const
	{
		if (Size < offsetof(s_MarketDataUpdateOpenInterest, OpenInterest) + sizeof(OpenInterest))
			return 0;

		return OpenInterest;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateOpenInterest::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateOpenInterest, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionHigh

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionHigh::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionHigh::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionHigh), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionHigh::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionHigh, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateSessionHigh::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionHigh, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionHigh::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionHigh, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionHigh_Int

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionHigh_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionHigh_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionHigh_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionHigh_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionHigh_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateSessionHigh_Int::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionHigh_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionHigh_Int::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionHigh_Int, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionLow

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionLow::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionLow::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionLow), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionLow::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionLow, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateSessionLow::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionLow, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionLow::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionLow, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateSessionLow_Int

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateSessionLow_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateSessionLow_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateSessionLow_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateSessionLow_Int::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionLow_Int, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	int32_t s_MarketDataUpdateSessionLow_Int::GetPrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionLow_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_MarketDataUpdateSessionLow_Int::GetTradingSessionDate() const
	{
		if (Size < offsetof(s_MarketDataUpdateSessionLow_Int, TradingSessionDate) + sizeof(TradingSessionDate))
			return 0;

		return TradingSessionDate;
	}

	/****************************************************************************/
	// s_MarketDataUpdateLastTradeSnapshot

	/*==========================================================================*/
	uint16_t s_MarketDataUpdateLastTradeSnapshot::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketDataUpdateLastTradeSnapshot::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketDataUpdateLastTradeSnapshot), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketDataUpdateLastTradeSnapshot::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketDataUpdateLastTradeSnapshot, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateLastTradeSnapshot::GetLastTradePrice() const
	{
		if (Size < offsetof(s_MarketDataUpdateLastTradeSnapshot, LastTradePrice) + sizeof(LastTradePrice))
			return 0.0;

		return LastTradePrice;
	}

	/*==========================================================================*/
	double s_MarketDataUpdateLastTradeSnapshot::GetLastTradeVolume() const
	{
		if (Size < offsetof(s_MarketDataUpdateLastTradeSnapshot, LastTradeVolume) + sizeof(LastTradeVolume))
			return 0.0;

		return LastTradeVolume;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_MarketDataUpdateLastTradeSnapshot::GetLastTradeDateTime() const
	{
		if (Size < offsetof(s_MarketDataUpdateLastTradeSnapshot, LastTradeDateTime) + sizeof(LastTradeDateTime))
			return 0.0;

		return LastTradeDateTime;
	}

	/****************************************************************************/
	// s_MarketOrdersRequest

	/*==========================================================================*/
	uint16_t s_MarketOrdersRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketOrdersRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketOrdersRequest), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	RequestActionEnum s_MarketOrdersRequest::GetRequestAction() const
	{
		if (Size < offsetof(s_MarketOrdersRequest, RequestAction) + sizeof(RequestAction))
			return RequestActionEnum::SUBSCRIBE;

		return RequestAction;
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersRequest::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketOrdersRequest, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	const char* s_MarketOrdersRequest::GetSymbol()
	{
		if (Size < offsetof(s_MarketOrdersRequest, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_MarketOrdersRequest::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_MarketOrdersRequest::GetExchange()
	{
		if (Size < offsetof(s_MarketOrdersRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_MarketOrdersRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	int32_t s_MarketOrdersRequest::GetSendQuantitiesGreaterOrEqualTo() const
	{
		if (Size < offsetof(s_MarketOrdersRequest, SendQuantitiesGreaterOrEqualTo) + sizeof(SendQuantitiesGreaterOrEqualTo))
			return 0;

		return SendQuantitiesGreaterOrEqualTo;
	}

	/****************************************************************************/
	// s_MarketOrdersReject

	/*==========================================================================*/
	uint16_t s_MarketOrdersReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketOrdersReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketOrdersReject), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersReject::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketOrdersReject, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	const char* s_MarketOrdersReject::GetRejectText()
	{
		if (Size < offsetof(s_MarketOrdersReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}

	/*==========================================================================*/
	void s_MarketOrdersReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/****************************************************************************/
	// s_MarketOrdersAdd

	/*==========================================================================*/
	uint16_t s_MarketOrdersAdd::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketOrdersAdd::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketOrdersAdd), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersAdd::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketOrdersAdd, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	BuySellEnum s_MarketOrdersAdd::GetSide() const
	{
		if (Size < offsetof(s_MarketOrdersAdd, Side) + sizeof(Side))
			return DTC::BUY_SELL_UNSET;

		return Side;
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersAdd::GetQuantity() const
	{
		if (Size < offsetof(s_MarketOrdersAdd, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	double s_MarketOrdersAdd::GetPrice() const
	{
		if (Size < offsetof(s_MarketOrdersAdd, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	uint64_t s_MarketOrdersAdd::GetOrderID() const
	{
		if (Size < offsetof(s_MarketOrdersAdd, OrderID) + sizeof(OrderID))
			return 0;

		return OrderID;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_MarketOrdersAdd::GetDateTime() const
	{
		if (Size < offsetof(s_MarketOrdersAdd, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_MarketOrdersModify

	/*==========================================================================*/
	uint16_t s_MarketOrdersModify::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketOrdersModify::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketOrdersModify), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersModify::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketOrdersModify, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersModify::GetQuantity() const
	{
		if (Size < offsetof(s_MarketOrdersModify, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	double s_MarketOrdersModify::GetPrice() const
	{
		if (Size < offsetof(s_MarketOrdersModify, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	uint64_t s_MarketOrdersModify::GetOrderID() const
	{
		if (Size < offsetof(s_MarketOrdersModify, OrderID) + sizeof(OrderID))
			return 0;

		return OrderID;
	}

	/*==========================================================================*/
	double s_MarketOrdersModify::GetPriorPrice() const
	{
		if (Size < offsetof(s_MarketOrdersModify, PriorPrice) + sizeof(PriorPrice))
			return 0;

		return PriorPrice;
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersModify::GetPriorQuantity() const
	{
		if (Size < offsetof(s_MarketOrdersModify, PriorQuantity) + sizeof(PriorQuantity))
			return 0;

		return PriorQuantity;
	}

	/*==========================================================================*/
	uint64_t s_MarketOrdersModify::GetPriorOrderID() const
	{
		if (Size < offsetof(s_MarketOrdersModify, PriorOrderID) + sizeof(PriorOrderID))
			return 0;

		return PriorOrderID;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_MarketOrdersModify::GetDateTime() const
	{
		if (Size < offsetof(s_MarketOrdersModify, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_MarketOrdersRemove

	/*==========================================================================*/
	uint16_t s_MarketOrdersRemove::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketOrdersRemove::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketOrdersRemove), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersRemove::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketOrdersRemove, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersRemove::GetQuantity() const
	{
		if (Size < offsetof(s_MarketOrdersRemove, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	double s_MarketOrdersRemove::GetPrice() const
	{
		if (Size < offsetof(s_MarketOrdersRemove, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	uint64_t s_MarketOrdersRemove::GetOrderID() const
	{
		if (Size < offsetof(s_MarketOrdersRemove, OrderID) + sizeof(OrderID))
			return 0;

		return OrderID;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_MarketOrdersRemove::GetDateTime() const
	{
		if (Size < offsetof(s_MarketOrdersRemove, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}
	
	/*==========================================================================*/
	DTC::BuySellEnum s_MarketOrdersRemove::GetSide() const
	{
		if (Size < offsetof(s_MarketOrdersRemove, Side) + sizeof(Side))
			return BUY_SELL_UNSET;

		return Side;
	}

	/****************************************************************************/
	// s_MarketOrdersSnapshotMessageBoundary

	/*==========================================================================*/
	uint16_t s_MarketOrdersSnapshotMessageBoundary::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_MarketOrdersSnapshotMessageBoundary::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_MarketOrdersSnapshotMessageBoundary), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_MarketOrdersSnapshotMessageBoundary::GetSymbolID() const
	{
		if (Size < offsetof(s_MarketOrdersSnapshotMessageBoundary, SymbolID) + sizeof(SymbolID))
			return 0;

		return SymbolID;
	}

	/*==========================================================================*/
	MessageSetBoundaryEnum s_MarketOrdersSnapshotMessageBoundary::GetMessageBoundary() const
	{
		if (Size < offsetof(s_MarketOrdersSnapshotMessageBoundary, MessageBoundary) + sizeof(MessageBoundary))
			return MESSAGE_SET_BOUNDARY_UNSET;

		return MessageBoundary;
	}

	/****************************************************************************/
	// s_SubmitNewSingleOrder

	/*==========================================================================*/
	uint16_t s_SubmitNewSingleOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SubmitNewSingleOrder::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SubmitNewSingleOrder), *static_cast<uint16_t*>( p_SourceData) ));
	}
	
	/*==========================================================================*/
	const char* s_SubmitNewSingleOrder::GetSymbol()
	{
		if (Size < offsetof( s_SubmitNewSingleOrder, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrder::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}
	/*==========================================================================*/
	const char* s_SubmitNewSingleOrder::GetExchange()
	{
		if (Size < offsetof( s_SubmitNewSingleOrder, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrder::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}	
	/*==========================================================================*/
	const char* s_SubmitNewSingleOrder::GetTradeAccount()
	{
		if (Size < offsetof( s_SubmitNewSingleOrder, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrder::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}	

	/*==========================================================================*/
	const char* s_SubmitNewSingleOrder::GetClientOrderID()
	{
		if (Size < offsetof( s_SubmitNewSingleOrder, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrder::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}
	/*==========================================================================*/
	OrderTypeEnum s_SubmitNewSingleOrder::GetOrderType() const
	{			
		if (Size < offsetof(s_SubmitNewSingleOrder, OrderType) + sizeof(OrderType))
			return ORDER_TYPE_UNSET;

		return OrderType;	
	}

	/*==========================================================================*/
	BuySellEnum s_SubmitNewSingleOrder::GetBuySell() const
	{			
		if (Size < offsetof(s_SubmitNewSingleOrder, BuySell) + sizeof(BuySell))
			return BUY_SELL_UNSET;

		return BuySell;	
	}
	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetPrice1() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, Price1) + sizeof(Price1))
			return 0.0;

		return Price1;
	}
	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetPrice2() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, Price2) + sizeof(Price2))
			return 0.0;

		return Price2;
	}
	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetQuantity() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}

	/*==========================================================================*/
	TimeInForceEnum s_SubmitNewSingleOrder::GetTimeInForce() const
	{			
		if (Size < offsetof(s_SubmitNewSingleOrder, TimeInForce) + sizeof(TimeInForce))
			return TIF_UNSET;

		return TimeInForce;	
	}

	/*==========================================================================*/	 
	t_DateTime s_SubmitNewSingleOrder::GetGoodTillDateTime() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}
	/*==========================================================================*/
	uint8_t s_SubmitNewSingleOrder::GetIsAutomatedOrder() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}
	/*==========================================================================*/
	uint8_t s_SubmitNewSingleOrder::GetIsParentOrder() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, IsParentOrder) + sizeof(IsParentOrder))
			return 0;

		return IsParentOrder;
	}

	/*==========================================================================*/
	const char* s_SubmitNewSingleOrder::GetFreeFormText()
	{
		if (Size < offsetof( s_SubmitNewSingleOrder, FreeFormText) + sizeof(FreeFormText))
			return "";

		FreeFormText[sizeof(FreeFormText) - 1] = '\0';

		return FreeFormText;

	}

	/*==========================================================================*/
	void s_SubmitNewSingleOrder::SetFreeFormText(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(FreeFormText) - 1);
	}

	/*==========================================================================*/
	OpenCloseTradeEnum s_SubmitNewSingleOrder::GetOpenOrClose() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, OpenOrClose) + sizeof(OpenOrClose))
			return TRADE_UNSET;

		return OpenOrClose;
	}

	/*==========================================================================*/
	double s_SubmitNewSingleOrder::GetMaxShowQuantity() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrder, MaxShowQuantity) + sizeof(MaxShowQuantity))
			return 0.0;

		return MaxShowQuantity;
	}

	/****************************************************************************/
	// s_SubmitNewSingleOrderInt

	/*==========================================================================*/
	uint16_t s_SubmitNewSingleOrderInt::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SubmitNewSingleOrderInt::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SubmitNewSingleOrderInt), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_SubmitNewSingleOrderInt::GetSymbol()
	{
		if (Size < offsetof( s_SubmitNewSingleOrderInt, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrderInt::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}
	/*==========================================================================*/
	const char* s_SubmitNewSingleOrderInt::GetExchange()
	{
		if (Size < offsetof( s_SubmitNewSingleOrderInt, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrderInt::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}	
	/*==========================================================================*/
	const char* s_SubmitNewSingleOrderInt::GetTradeAccount()
	{
		if (Size < offsetof( s_SubmitNewSingleOrderInt, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrderInt::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}	

	/*==========================================================================*/
	const char* s_SubmitNewSingleOrderInt::GetClientOrderID()
	{
		if (Size < offsetof( s_SubmitNewSingleOrderInt, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}
	/*==========================================================================*/
	void s_SubmitNewSingleOrderInt::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}
	/*==========================================================================*/
	OrderTypeEnum s_SubmitNewSingleOrderInt::GetOrderType() const
	{			
		if (Size < offsetof(s_SubmitNewSingleOrderInt, OrderType) + sizeof(OrderType))
			return ORDER_TYPE_UNSET;

		return OrderType;	
	}

	/*==========================================================================*/
	BuySellEnum s_SubmitNewSingleOrderInt::GetBuySell() const
	{			
		if (Size < offsetof(s_SubmitNewSingleOrderInt, BuySell) + sizeof(BuySell))
			return BUY_SELL_UNSET;

		return BuySell;	
	}
	/*==========================================================================*/
	int64_t s_SubmitNewSingleOrderInt::GetPrice1() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, Price1) + sizeof(Price1))
			return 0;

		return Price1;
	}
	/*==========================================================================*/
	int64_t s_SubmitNewSingleOrderInt::GetPrice2() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, Price2) + sizeof(Price2))
			return 0;

		return Price2;
	}

	/*==========================================================================*/
	float s_SubmitNewSingleOrderInt::GetDivisor() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, Divisor) + sizeof(Divisor))
			return 0.0;

		return Divisor;
	}
	/*==========================================================================*/
	int64_t s_SubmitNewSingleOrderInt::GetQuantity() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	TimeInForceEnum s_SubmitNewSingleOrderInt::GetTimeInForce() const
	{			
		if (Size < offsetof(s_SubmitNewSingleOrderInt, TimeInForce) + sizeof(TimeInForce))
			return TIF_UNSET;

		return TimeInForce;	
	}

	/*==========================================================================*/	 
	t_DateTime s_SubmitNewSingleOrderInt::GetGoodTillDateTime() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}
	/*==========================================================================*/
	uint8_t s_SubmitNewSingleOrderInt::GetIsAutomatedOrder() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}
	/*==========================================================================*/
	uint8_t s_SubmitNewSingleOrderInt::GetIsParentOrder() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, IsParentOrder) + sizeof(IsParentOrder))
			return 0;

		return IsParentOrder;
	}

	/*==========================================================================*/
	const char* s_SubmitNewSingleOrderInt::GetFreeFormText()
	{
		if (Size < offsetof( s_SubmitNewSingleOrderInt, FreeFormText) + sizeof(FreeFormText))
			return "";

		FreeFormText[sizeof(FreeFormText) - 1] = '\0';

		return FreeFormText;

	}

	/*==========================================================================*/
	void s_SubmitNewSingleOrderInt::SetFreeFormText(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(FreeFormText) - 1);
	}

	/*==========================================================================*/
	OpenCloseTradeEnum s_SubmitNewSingleOrderInt::GetOpenOrClose() const
	{
		if (Size < offsetof(s_SubmitNewSingleOrderInt, OpenOrClose) + sizeof(OpenOrClose))
			return TRADE_UNSET;

		return OpenOrClose;
	}

	/****************************************************************************/
	// s_SubmitFlattenPositionOrder

	/*==========================================================================*/
	uint16_t s_SubmitFlattenPositionOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SubmitFlattenPositionOrder::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SubmitFlattenPositionOrder), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	const char* s_SubmitFlattenPositionOrder::GetSymbol()
	{
		if (Size < offsetof(s_SubmitFlattenPositionOrder, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_SubmitFlattenPositionOrder::SetSymbol(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitFlattenPositionOrder::GetExchange()
	{
		if (Size < offsetof(s_SubmitFlattenPositionOrder, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_SubmitFlattenPositionOrder::SetExchange(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitFlattenPositionOrder::GetTradeAccount()
	{
		if (Size < offsetof(s_SubmitFlattenPositionOrder, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}

	/*==========================================================================*/
	void s_SubmitFlattenPositionOrder::SetTradeAccount(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitFlattenPositionOrder::GetClientOrderID()
	{
		if (Size < offsetof(s_SubmitFlattenPositionOrder, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}

	/*==========================================================================*/
	void s_SubmitFlattenPositionOrder::SetClientOrderID(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(ClientOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitFlattenPositionOrder::GetFreeFormText()
	{
		if (Size < offsetof(s_SubmitFlattenPositionOrder, FreeFormText) + sizeof(FreeFormText))
			return "";

		FreeFormText[sizeof(FreeFormText) - 1] = '\0';

		return FreeFormText;
	}

	/*==========================================================================*/
	void s_SubmitFlattenPositionOrder::SetFreeFormText(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(FreeFormText) - 1);
	}

	/*==========================================================================*/
	uint8_t s_SubmitFlattenPositionOrder::GetIsAutomatedOrder() const
	{
		if (Size < offsetof(s_SubmitFlattenPositionOrder, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}

	/****************************************************************************/
	// s_CancelReplaceOrder

	/*==========================================================================*/
	uint16_t s_CancelReplaceOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_CancelReplaceOrder::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_CancelReplaceOrder), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_CancelReplaceOrder::GetServerOrderID()
	{
		if (Size < offsetof( s_CancelReplaceOrder, ServerOrderID) + sizeof(ServerOrderID))
			return "";

		ServerOrderID[sizeof(ServerOrderID) - 1] = '\0';

		return ServerOrderID;
	}

	/*==========================================================================*/
	void s_CancelReplaceOrder::SetServerOrderID(const char* NewValue)
	{
		strncpy(ServerOrderID, NewValue, sizeof(ServerOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_CancelReplaceOrder::GetClientOrderID()
	{
		if (Size < offsetof( s_CancelReplaceOrder, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}

	/*==========================================================================*/
	void s_CancelReplaceOrder::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_CancelReplaceOrder::GetTradeAccount()
	{
		if (Size < offsetof(s_CancelReplaceOrder, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}

	/*==========================================================================*/
	void s_CancelReplaceOrder::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	double s_CancelReplaceOrder::GetPrice1() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, Price1) + sizeof(Price1))
			return 0.0;

		return Price1;
	}

	/*==========================================================================*/
	double s_CancelReplaceOrder::GetPrice2() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, Price2) + sizeof(Price2))
			return 0.0;

		return Price2;
	}

	/*==========================================================================*/
	double s_CancelReplaceOrder::GetQuantity() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, Quantity) + sizeof(Quantity))
			return 0.0;

		return Quantity;
	}

	/*==========================================================================*/
	uint8_t s_CancelReplaceOrder::GetPrice1IsSet() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, Price1IsSet) + sizeof(Price1IsSet))
			return 1;

		return Price1IsSet;
	}

	/*==========================================================================*/
	uint8_t s_CancelReplaceOrder::GetPrice2IsSet() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, Price2IsSet) + sizeof(Price2IsSet))
			return 1;

		return Price2IsSet;
	}

	/*==========================================================================*/
	TimeInForceEnum s_CancelReplaceOrder::GetTimeInForce() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, TimeInForce) + sizeof(TimeInForce))
			return TIF_UNSET;

		return TimeInForce;
	}

	/*==========================================================================*/
	t_DateTime s_CancelReplaceOrder::GetGoodTillDateTime() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}

	/*==========================================================================*/
	uint8_t s_CancelReplaceOrder::GetUpdatePrice1OffsetToParent() const
	{
		if (Size < offsetof(s_CancelReplaceOrder, UpdatePrice1OffsetToParent) + sizeof(UpdatePrice1OffsetToParent))
			return 0;

		return UpdatePrice1OffsetToParent;
	}

	/****************************************************************************/
	// s_CancelReplaceOrderInt

	/*==========================================================================*/
	uint16_t s_CancelReplaceOrderInt::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_CancelReplaceOrderInt::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_CancelReplaceOrderInt), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_CancelReplaceOrderInt::GetServerOrderID()
	{
		if (Size < offsetof( s_CancelReplaceOrderInt, ServerOrderID) + sizeof(ServerOrderID))
			return "";

		ServerOrderID[sizeof(ServerOrderID) - 1] = '\0';

		return ServerOrderID;
	}

	/*==========================================================================*/
	void s_CancelReplaceOrderInt::SetServerOrderID(const char* NewValue)
	{
		strncpy(ServerOrderID, NewValue, sizeof(ServerOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_CancelReplaceOrderInt::GetClientOrderID()
	{
		if (Size < offsetof( s_CancelReplaceOrderInt, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}

	/*==========================================================================*/
	void s_CancelReplaceOrderInt::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}

	/*==========================================================================*/
	int64_t s_CancelReplaceOrderInt::GetPrice1() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, Price1) + sizeof(Price1))
			return 0;

		return Price1;
	}

	/*==========================================================================*/
	int64_t s_CancelReplaceOrderInt::GetPrice2() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, Price2) + sizeof(Price2))
			return 0;

		return Price2;
	}

	/*==========================================================================*/
	float s_CancelReplaceOrderInt::GetDivisor() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, Divisor) + sizeof(Divisor))
			return 1.0f;

		return Divisor;
	}

	/*==========================================================================*/
	int64_t s_CancelReplaceOrderInt::GetQuantity() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	uint8_t s_CancelReplaceOrderInt::GetPrice1IsSet() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, Price1IsSet) + sizeof(Price1IsSet))
			return 1;

		return Price1IsSet;
	}

	/*==========================================================================*/
	uint8_t s_CancelReplaceOrderInt::GetPrice2IsSet() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, Price2IsSet) + sizeof(Price2IsSet))
			return 1;

		return Price2IsSet;
	}

	/*==========================================================================*/
	TimeInForceEnum s_CancelReplaceOrderInt::GetTimeInForce() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, TimeInForce) + sizeof(TimeInForce))
			return TIF_UNSET;

		return TimeInForce;
	}

	/*==========================================================================*/
	t_DateTime s_CancelReplaceOrderInt::GetGoodTillDateTime() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}

	/*==========================================================================*/
	uint8_t s_CancelReplaceOrderInt::GetUpdatePrice1OffsetToParent() const
	{
		if (Size < offsetof(s_CancelReplaceOrderInt, UpdatePrice1OffsetToParent) + sizeof(UpdatePrice1OffsetToParent))
			return 0;

		return UpdatePrice1OffsetToParent;
	}

	/****************************************************************************/
	// s_CancelOrder

	/*==========================================================================*/
	uint16_t s_CancelOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_CancelOrder::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_CancelOrder), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_CancelOrder::GetServerOrderID()
	{
		if (Size < offsetof( s_CancelOrder, ServerOrderID) + sizeof(ServerOrderID))
			return "";

		ServerOrderID[sizeof(ServerOrderID) - 1] = '\0';

		return ServerOrderID;
	}

	/*==========================================================================*/
	void s_CancelOrder::SetServerOrderID(const char* NewValue)
	{
		strncpy(ServerOrderID, NewValue, sizeof(ServerOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_CancelOrder::GetClientOrderID()
	{
		if (Size < offsetof( s_CancelOrder, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}

	/*==========================================================================*/
	void s_CancelOrder::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_CancelOrder::GetTradeAccount()
	{
		if (Size < offsetof(s_CancelOrder, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}

	/*==========================================================================*/
	void s_CancelOrder::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/****************************************************************************/
	// s_SubmitNewOCOOrder

	/*==========================================================================*/
	uint16_t s_SubmitNewOCOOrder::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SubmitNewOCOOrder::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SubmitNewOCOOrder), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrder::SetClientOrderID_1(const char* NewValue)
	{
		strncpy(ClientOrderID_1, NewValue, sizeof(ClientOrderID_1) - 1);
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrder::SetClientOrderID_2(const char* NewValue)
	{
		strncpy(ClientOrderID_2, NewValue, sizeof(ClientOrderID_2) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitNewOCOOrder::GetFreeFormText()
	{
		if (Size < offsetof( s_SubmitNewOCOOrder, FreeFormText) + sizeof(FreeFormText))
			return "";

		FreeFormText[sizeof(FreeFormText) - 1] = '\0';

		return FreeFormText;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrder::SetFreeFormText(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(FreeFormText) - 1);
	}
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrder::GetClientOrderID_1()
	{
		if (Size < offsetof( s_SubmitNewOCOOrder, ClientOrderID_1) + sizeof(ClientOrderID_1))
			return "";

		ClientOrderID_1[sizeof(ClientOrderID_1) - 1] = '\0';

		return ClientOrderID_1;
	}
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrder::GetClientOrderID_2()
	{
		if (Size < offsetof( s_SubmitNewOCOOrder, ClientOrderID_2) + sizeof(ClientOrderID_2))
			return "";

		ClientOrderID_2[sizeof(ClientOrderID_2) - 1] = '\0';

		return ClientOrderID_2;
	}
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrder::GetSymbol()
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_SubmitNewOCOOrder::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitNewOCOOrder::GetExchange()
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrder::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	OrderTypeEnum s_SubmitNewOCOOrder::GetOrderType_1() const
	{			
		if (Size < offsetof(s_SubmitNewOCOOrder, OrderType_1) + sizeof(OrderType_1))
			return ORDER_TYPE_UNSET;

		return OrderType_1;	
	}
	/*==========================================================================*/
	OrderTypeEnum s_SubmitNewOCOOrder::GetOrderType_2() const
	{			
		if (Size < offsetof(s_SubmitNewOCOOrder, OrderType_2) + sizeof(OrderType_2))
			return ORDER_TYPE_UNSET;

		return OrderType_2;	
	}
	/*==========================================================================*/			 
	BuySellEnum s_SubmitNewOCOOrder::GetBuySell_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, BuySell_1) + sizeof(BuySell_1))
			return (BuySellEnum)0;

		return BuySell_1;
	}
	/*==========================================================================*/
	BuySellEnum s_SubmitNewOCOOrder::GetBuySell_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, BuySell_2) + sizeof(BuySell_2))
			return (BuySellEnum)0;

		return BuySell_2;
	}
	/*==========================================================================*/
	TimeInForceEnum s_SubmitNewOCOOrder::GetTimeInForce() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, TimeInForce) + sizeof(TimeInForce))
			return (TimeInForceEnum)0;

		return TimeInForce;
	}
	/*==========================================================================*/
	t_DateTime s_SubmitNewOCOOrder::GetGoodTillDateTime() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}	
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrder::GetParentTriggerClientOrderID()
	{
		if (Size < offsetof( s_SubmitNewOCOOrder, ParentTriggerClientOrderID) + sizeof(ParentTriggerClientOrderID))
			return "";

		ParentTriggerClientOrderID[sizeof(ParentTriggerClientOrderID) - 1] = '\0';

		return ParentTriggerClientOrderID;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrder::SetParentTriggerClientOrderID(const char* NewValue)
	{
		strncpy(ParentTriggerClientOrderID, NewValue, sizeof(ParentTriggerClientOrderID) - 1);
	}
	/*==========================================================================*/
	uint8_t s_SubmitNewOCOOrder::GetIsAutomatedOrder() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}
	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice1_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Price1_1) + sizeof(Price1_1))
			return 0.0;

		return Price1_1;
	}
	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice2_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Price2_1) + sizeof(Price2_1))
			return 0.0;

		return Price2_1;
	}
	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice1_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Price1_2) + sizeof(Price1_2))
			return 0.0;

		return Price1_2;
	}
	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetPrice2_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Price2_2) + sizeof(Price2_2))
			return 0.0;

		return Price2_2;
	}

	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetQuantity_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Quantity_1) + sizeof(Quantity_1))
			return 0.0;

		return Quantity_1;
	}
	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetQuantity_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, Quantity_2) + sizeof(Quantity_2))
			return 0.0;

		return Quantity_2;
	}
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrder::GetTradeAccount()
	{
		if (Size < offsetof( s_SubmitNewOCOOrder, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrder::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}
	/*==========================================================================*/
	OpenCloseTradeEnum s_SubmitNewOCOOrder::GetOpenOrClose() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, OpenOrClose) + sizeof(OpenOrClose))
			return TRADE_UNSET;

		return OpenOrClose;
	}
	/*==========================================================================*/
	PartialFillHandlingEnum s_SubmitNewOCOOrder::GetPartialFillHandling() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, PartialFillHandling) + sizeof(PartialFillHandling))
			return PARTIAL_FILL_UNSET;

		return PartialFillHandling;
	}
	/*==========================================================================*/
	uint8_t s_SubmitNewOCOOrder::GetUseOffsets() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, UseOffsets) + sizeof(UseOffsets))
			return 0;

		return UseOffsets;
	}
	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetOffsetFromParent1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, OffsetFromParent1) + sizeof(OffsetFromParent1))
			return 0.0;

		return OffsetFromParent1;
	}
	/*==========================================================================*/
	double s_SubmitNewOCOOrder::GetOffsetFromParent2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, OffsetFromParent2) + sizeof(OffsetFromParent2))
			return 0.0;

		return OffsetFromParent2;
	}

	/*==========================================================================*/
	uint8_t s_SubmitNewOCOOrder::GetMaintainSamePricesOnParentFill() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrder, MaintainSamePricesOnParentFill) + sizeof(MaintainSamePricesOnParentFill))
			return 0;

		return MaintainSamePricesOnParentFill;
	}


	/****************************************************************************/
	// s_SubmitNewOCOOrderInt

	/*==========================================================================*/
	uint16_t s_SubmitNewOCOOrderInt::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SubmitNewOCOOrderInt), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::SetClientOrderID_1(const char* NewValue)
	{
		strncpy(ClientOrderID_1, NewValue, sizeof(ClientOrderID_1) - 1);
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::SetClientOrderID_2(const char* NewValue)
	{
		strncpy(ClientOrderID_2, NewValue, sizeof(ClientOrderID_2) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitNewOCOOrderInt::GetFreeFormText()
	{
		if (Size < offsetof( s_SubmitNewOCOOrderInt, FreeFormText) + sizeof(FreeFormText))
			return "";

		FreeFormText[sizeof(FreeFormText) - 1] = '\0';

		return FreeFormText;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::SetFreeFormText(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(FreeFormText) - 1);
	}
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrderInt::GetClientOrderID_1()
	{
		if (Size < offsetof( s_SubmitNewOCOOrderInt, ClientOrderID_1) + sizeof(ClientOrderID_1))
			return "";

		ClientOrderID_1[sizeof(ClientOrderID_1) - 1] = '\0';

		return ClientOrderID_1;
	}
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrderInt::GetClientOrderID_2()
	{
		if (Size < offsetof( s_SubmitNewOCOOrderInt, ClientOrderID_2) + sizeof(ClientOrderID_2))
			return "";

		ClientOrderID_2[sizeof(ClientOrderID_2) - 1] = '\0';

		return ClientOrderID_2;
	}
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrderInt::GetSymbol()
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_SubmitNewOCOOrderInt::GetExchange()
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	OrderTypeEnum s_SubmitNewOCOOrderInt::GetOrderType_1() const
	{			
		if (Size < offsetof(s_SubmitNewOCOOrderInt, OrderType_1) + sizeof(OrderType_1))
			return ORDER_TYPE_UNSET;

		return OrderType_1;	
	}
	/*==========================================================================*/
	OrderTypeEnum s_SubmitNewOCOOrderInt::GetOrderType_2() const
	{			
		if (Size < offsetof(s_SubmitNewOCOOrderInt, OrderType_2) + sizeof(OrderType_2))
			return ORDER_TYPE_UNSET;

		return OrderType_2;	
	}
	/*==========================================================================*/			 
	BuySellEnum s_SubmitNewOCOOrderInt::GetBuySell_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, BuySell_1) + sizeof(BuySell_1))
			return (BuySellEnum)0;

		return BuySell_1;
	}
	/*==========================================================================*/
	BuySellEnum s_SubmitNewOCOOrderInt::GetBuySell_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, BuySell_2) + sizeof(BuySell_2))
			return (BuySellEnum)0;

		return BuySell_2;
	}
	/*==========================================================================*/
	TimeInForceEnum s_SubmitNewOCOOrderInt::GetTimeInForce() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, TimeInForce) + sizeof(TimeInForce))
			return (TimeInForceEnum)0;

		return TimeInForce;
	}
	/*==========================================================================*/
	t_DateTime s_SubmitNewOCOOrderInt::GetGoodTillDateTime() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}	
	/*==========================================================================*/
	const char* s_SubmitNewOCOOrderInt::GetParentTriggerClientOrderID()
	{
		if (Size < offsetof( s_SubmitNewOCOOrderInt, ParentTriggerClientOrderID) + sizeof(ParentTriggerClientOrderID))
			return "";

		ParentTriggerClientOrderID[sizeof(ParentTriggerClientOrderID) - 1] = '\0';

		return ParentTriggerClientOrderID;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::SetParentTriggerClientOrderID(const char* NewValue)
	{
		strncpy(ParentTriggerClientOrderID, NewValue, sizeof(ParentTriggerClientOrderID) - 1);
	}
	/*==========================================================================*/
	uint8_t s_SubmitNewOCOOrderInt::GetIsAutomatedOrder() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, IsAutomatedOrder) + sizeof(IsAutomatedOrder))
			return 0;

		return IsAutomatedOrder;
	}
	/*==========================================================================*/
	int64_t s_SubmitNewOCOOrderInt::GetPrice1_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Price1_1) + sizeof(Price1_1))
			return 0;

		return Price1_1;
	}
	/*==========================================================================*/
	int64_t s_SubmitNewOCOOrderInt::GetPrice2_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Price2_1) + sizeof(Price2_1))
			return 0;

		return Price2_1;
	}
	/*==========================================================================*/
	int64_t s_SubmitNewOCOOrderInt::GetPrice1_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Price1_2) + sizeof(Price1_2))
			return 0;

		return Price1_2;
	}
	/*==========================================================================*/
	int64_t s_SubmitNewOCOOrderInt::GetPrice2_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Price2_2) + sizeof(Price2_2))
			return 0;

		return Price2_2;
	}

	/*==========================================================================*/
	int64_t s_SubmitNewOCOOrderInt::GetQuantity_1() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Quantity_1) + sizeof(Quantity_1))
			return 0;

		return Quantity_1;
	}

	/*==========================================================================*/
	int64_t s_SubmitNewOCOOrderInt::GetQuantity_2() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Quantity_2) + sizeof(Quantity_2))
			return 0;

		return Quantity_2;
	}

	/*==========================================================================*/
	const char* s_SubmitNewOCOOrderInt::GetTradeAccount()
	{
		if (Size < offsetof( s_SubmitNewOCOOrderInt, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_SubmitNewOCOOrderInt::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}
	/*==========================================================================*/
	float s_SubmitNewOCOOrderInt::GetDivisor() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, Divisor) + sizeof(Divisor))
			return 0.0;

		return Divisor;
	}
	/*==========================================================================*/
	OpenCloseTradeEnum s_SubmitNewOCOOrderInt::GetOpenOrClose() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, OpenOrClose) + sizeof(OpenOrClose))
			return TRADE_UNSET;

		return OpenOrClose;
	}
	/*==========================================================================*/
	PartialFillHandlingEnum s_SubmitNewOCOOrderInt::GetPartialFillHandling() const
	{
		if (Size < offsetof(s_SubmitNewOCOOrderInt, PartialFillHandling) + sizeof(PartialFillHandling))
			return PARTIAL_FILL_UNSET;

		return PartialFillHandling;
	}


	/****************************************************************************/
	// s_OpenOrdersRequest

	/*==========================================================================*/
	uint16_t s_OpenOrdersRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_OpenOrdersRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_OpenOrdersRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_OpenOrdersRequest::GetRequestID() const
	{
		if (Size < offsetof(s_OpenOrdersRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	int32_t s_OpenOrdersRequest::GetRequestAllOrders() const
	{
		if (Size < offsetof(s_OpenOrdersRequest, RequestAllOrders) + sizeof(RequestAllOrders))
			return 0;

		return RequestAllOrders;
	}

	/*==========================================================================*/
	void s_OpenOrdersRequest::SetServerOrderID(const char* NewValue)
	{
		strncpy(ServerOrderID, NewValue, sizeof(ServerOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_OpenOrdersRequest::GetServerOrderID()
	{
		if (Size < offsetof( s_OpenOrdersRequest, ServerOrderID) + sizeof(ServerOrderID))
			return "";

		ServerOrderID[sizeof(ServerOrderID) - 1] = '\0';

		return ServerOrderID;
	}

	/*==========================================================================*/
	void s_OpenOrdersRequest::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_OpenOrdersRequest::GetTradeAccount()
	{
		if (Size < offsetof(s_OpenOrdersRequest, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}

	/****************************************************************************/
	// s_HistoricalOrderFillsRequest

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillsRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalOrderFillsRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalOrderFillsRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_HistoricalOrderFillsRequest::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalOrderFillsRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	int32_t s_HistoricalOrderFillsRequest::GetNumberOfDays() const
	{
		if (Size < offsetof(s_HistoricalOrderFillsRequest, NumberOfDays) + sizeof(NumberOfDays))
			return 0;

		return NumberOfDays;
	}
	/*==========================================================================*/
	t_DateTime s_HistoricalOrderFillsRequest::GetStartDateTime() const
	{
		if (Size < offsetof(s_HistoricalOrderFillsRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/*==========================================================================*/
	const char* s_HistoricalOrderFillsRequest::GetServerOrderID()
	{
		if (Size < offsetof( s_HistoricalOrderFillsRequest, ServerOrderID) + sizeof(ServerOrderID))
			return "";

		ServerOrderID[sizeof(ServerOrderID) - 1] = '\0';

		return ServerOrderID;
	}
	/*==========================================================================*/
	void s_HistoricalOrderFillsRequest::SetServerOrderID(const char* NewValue)
	{
		strncpy(ServerOrderID, NewValue, sizeof(ServerOrderID) - 1);
	}
	/*==========================================================================*/
	const char* s_HistoricalOrderFillsRequest::GetTradeAccount()
	{
		if (Size < offsetof( s_HistoricalOrderFillsRequest, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_HistoricalOrderFillsRequest::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/****************************************************************************/
	// s_HistoricalOrderFillsReject

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillsReject::GetMessageSize() const
	{
		return Size;
	}
	/*==========================================================================*/
	void s_HistoricalOrderFillsReject::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalOrderFillsReject), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_HistoricalOrderFillsReject::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalOrderFillsReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	void s_HistoricalOrderFillsReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}
	/*==========================================================================*/
	const char* s_HistoricalOrderFillsReject::GetRejectText()
	{
		if (Size < offsetof( s_HistoricalOrderFillsReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}

	/****************************************************************************/
	// s_CurrentPositionsRequest

	/*==========================================================================*/
	uint16_t s_CurrentPositionsRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_CurrentPositionsRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_CurrentPositionsRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_CurrentPositionsRequest::GetRequestID() const
	{
		if (Size < offsetof(s_CurrentPositionsRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	const char* s_CurrentPositionsRequest::GetTradeAccount()
	{
		if (Size < offsetof( s_CurrentPositionsRequest, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_CurrentPositionsRequest::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/****************************************************************************/
	// s_CurrentPositionsRequestReject

	/*==========================================================================*/
	uint16_t s_CurrentPositionsReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_CurrentPositionsReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_CurrentPositionsReject), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_CurrentPositionsReject::GetRequestID() const
	{
		if (Size < offsetof(s_CurrentPositionsReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	const char* s_CurrentPositionsReject::GetRejectText()
	{
		if (Size < offsetof( s_CurrentPositionsReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}
	/*==========================================================================*/
	void s_CurrentPositionsReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}


	/****************************************************************************/
	// s_OrderUpdateReport

	/*==========================================================================*/
	uint16_t s_OrderUpdate::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_OrderUpdate::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_OrderUpdate), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_OrderUpdate::GetSymbol()
	{
		if (Size < offsetof(s_OrderUpdate, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_OrderUpdate::GetExchange()
	{
		if (Size < offsetof(s_OrderUpdate, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	const char* s_OrderUpdate::GetPreviousServerOrderID()
	{
		if (Size < offsetof(s_OrderUpdate, PreviousServerOrderID) + sizeof(PreviousServerOrderID))
			return "";

		PreviousServerOrderID[sizeof(PreviousServerOrderID) - 1] = '\0';

		return PreviousServerOrderID;
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetPreviousServerOrderID(const char* NewValue)
	{
		strncpy(PreviousServerOrderID, NewValue, sizeof(PreviousServerOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_OrderUpdate::GetServerOrderID()
	{
		if (Size < offsetof(s_OrderUpdate, ServerOrderID) + sizeof(ServerOrderID))
			return "";

		ServerOrderID[sizeof(ServerOrderID) - 1] = '\0';

		return ServerOrderID;
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetServerOrderID(const char* NewValue)
	{
		strncpy(ServerOrderID, NewValue, sizeof(ServerOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_OrderUpdate::GetClientOrderID()
	{
		if (Size < offsetof(s_OrderUpdate, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_OrderUpdate::GetExchangeOrderID()
	{
		if (Size < offsetof(s_OrderUpdate, ExchangeOrderID) + sizeof(ExchangeOrderID))
			return "";

		ExchangeOrderID[sizeof(ExchangeOrderID) - 1] = '\0';

		return ExchangeOrderID;
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetExchangeOrderID(const char* NewValue)
	{
		strncpy(ExchangeOrderID, NewValue, sizeof(ExchangeOrderID) - 1);
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetLastFillExecutionID(const char* NewValue)
	{
		strncpy(LastFillExecutionID, NewValue, sizeof(LastFillExecutionID) - 1);
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetInfoText(const char* NewValue)
	{
		strncpy(InfoText, NewValue, sizeof(InfoText) - 1);
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetOrderQuantity() const
	{
		if (Size < offsetof(s_OrderUpdate, OrderQuantity) + sizeof(OrderQuantity))
			return DBL_MAX;

		return OrderQuantity;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetFilledQuantity() const
	{
		if (Size < offsetof(s_OrderUpdate, FilledQuantity) + sizeof(FilledQuantity))
			return DBL_MAX;

		return FilledQuantity;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetRemainingQuantity() const
	{
		if (Size < offsetof(s_OrderUpdate, RemainingQuantity) + sizeof(RemainingQuantity))
			return DBL_MAX;

		return RemainingQuantity;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetLastFillQuantity() const
	{
		if (Size < offsetof(s_OrderUpdate, LastFillQuantity) + sizeof(LastFillQuantity))
			return DBL_MAX;

		return LastFillQuantity;
	}
	/*==========================================================================*/
	int32_t s_OrderUpdate::GetRequestID() const
	{
		if (Size < offsetof(s_OrderUpdate, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	int32_t s_OrderUpdate::GetTotalNumMessages() const
	{
		if (Size < offsetof(s_OrderUpdate, TotalNumMessages) + sizeof(TotalNumMessages))
			return 0;

		return TotalNumMessages;
	}

	/*==========================================================================*/
	int32_t s_OrderUpdate::GetMessageNumber() const
	{
		if (Size < offsetof(s_OrderUpdate, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}
	/*==========================================================================*/
	OrderStatusEnum s_OrderUpdate::GetOrderStatus() const
	{
		if (Size < offsetof(s_OrderUpdate, OrderStatus) + sizeof(OrderStatus))
			return (OrderStatusEnum)0;

		return OrderStatus;
	}
	/*==========================================================================*/
	OrderUpdateReasonEnum s_OrderUpdate::GetOrderUpdateReason() const
	{
		if (Size < offsetof(s_OrderUpdate, OrderUpdateReason) + sizeof(OrderUpdateReason))
			return (OrderUpdateReasonEnum)0;

		return OrderUpdateReason;
	}
	/*==========================================================================*/
	OrderTypeEnum s_OrderUpdate::GetOrderType() const
	{
		if (Size < offsetof(s_OrderUpdate, OrderType) + sizeof(OrderType))
			return (OrderTypeEnum)0;

		return OrderType;
	}
	/*==========================================================================*/
	BuySellEnum s_OrderUpdate::GetBuySell() const
	{
		if (Size < offsetof(s_OrderUpdate, BuySell) + sizeof(BuySell))
			return (BuySellEnum)0;

		return BuySell;
	}
	/*==========================================================================*/
	double s_OrderUpdate::GetPrice1() const
	{
		if (Size < offsetof(s_OrderUpdate, Price1) + sizeof(Price1))
			return DBL_MAX;

		return Price1;
	}
	/*==========================================================================*/
	double s_OrderUpdate::GetPrice2() const
	{
		if (Size < offsetof(s_OrderUpdate, Price2) + sizeof(Price2))
			return DBL_MAX;

		return Price2;
	}

	/*==========================================================================*/
	TimeInForceEnum s_OrderUpdate::GetTimeInForce() const
	{
		if (Size < offsetof(s_OrderUpdate, TimeInForce) + sizeof(TimeInForce))
			return (TimeInForceEnum)0;

		return TimeInForce;
	}
	/*==========================================================================*/
	t_DateTime s_OrderUpdate::GetGoodTillDateTime() const
	{
		if (Size < offsetof(s_OrderUpdate, GoodTillDateTime) + sizeof(GoodTillDateTime))
			return 0;

		return GoodTillDateTime;
	}

	/*==========================================================================*/
	double s_OrderUpdate::GetAverageFillPrice() const
	{
		if (Size < offsetof(s_OrderUpdate, AverageFillPrice) + sizeof(AverageFillPrice))
			return DBL_MAX;

		return AverageFillPrice;
	}
	/*==========================================================================*/
	double s_OrderUpdate::GetLastFillPrice() const
	{
		if (Size < offsetof(s_OrderUpdate, LastFillPrice) + sizeof(LastFillPrice))
			return DBL_MAX;

		return LastFillPrice;
	}
	/*==========================================================================*/
	t_DateTime s_OrderUpdate::GetLastFillDateTime() const
	{
		if (Size < offsetof(s_OrderUpdate, LastFillDateTime) + sizeof(LastFillDateTime))
			return 0;

		return LastFillDateTime;
	}
	/*==========================================================================*/
	const char* s_OrderUpdate::GetLastFillExecutionID()
	{
		if (Size < offsetof(s_OrderUpdate, LastFillExecutionID) + sizeof(LastFillExecutionID))
			return "";

		LastFillExecutionID[sizeof(LastFillExecutionID) - 1] = '\0';

		return LastFillExecutionID;
	}
	/*==========================================================================*/
	const char* s_OrderUpdate::GetTradeAccount()
	{
		if (Size < offsetof(s_OrderUpdate, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	const char* s_OrderUpdate::GetInfoText()
	{
		if (Size < offsetof(s_OrderUpdate, InfoText) + sizeof(InfoText))
			return "";

		InfoText[sizeof(InfoText) - 1] = '\0';

		return InfoText;
	}
	/*==========================================================================*/	
	uint8_t s_OrderUpdate::GetNoOrders() const
	{
		if (Size < offsetof(s_OrderUpdate, NoOrders) + sizeof(NoOrders))
			return 0;

		return NoOrders;
	}
	/*==========================================================================*/
	const char* s_OrderUpdate::GetParentServerOrderID()
	{
		if (Size < offsetof(s_OrderUpdate, ParentServerOrderID) + sizeof(ParentServerOrderID))
			return "";

		ParentServerOrderID[sizeof(ParentServerOrderID) - 1] = '\0';

		return ParentServerOrderID;
	}
	/*==========================================================================*/
	void s_OrderUpdate::SetParentServerOrderID(const char* NewValue)
	{
		strncpy(ParentServerOrderID, NewValue, sizeof(ParentServerOrderID) - 1);
	}
	/*==========================================================================*/
	const char* s_OrderUpdate::GetOCOLinkedOrderServerOrderID()
	{
		if (Size < offsetof(s_OrderUpdate, OCOLinkedOrderServerOrderID) + sizeof(OCOLinkedOrderServerOrderID))
			return "";

		OCOLinkedOrderServerOrderID[sizeof(OCOLinkedOrderServerOrderID) - 1] = '\0';

		return OCOLinkedOrderServerOrderID;
	}
	/*==========================================================================*/
	void s_OrderUpdate::SetOCOLinkedOrderServerOrderID(const char* NewValue)
	{
		strncpy(OCOLinkedOrderServerOrderID, NewValue, sizeof(OCOLinkedOrderServerOrderID) - 1);
	}
	/*==========================================================================*/
	OpenCloseTradeEnum s_OrderUpdate::GetOpenOrClose() const
	{
		if (Size < offsetof(s_OrderUpdate, OpenOrClose) + sizeof(OpenOrClose))
			return TRADE_UNSET;

		return OpenOrClose;
	}
	/*==========================================================================*/
	t_DateTime s_OrderUpdate::GetOrderReceivedDateTime() const
	{
		if (Size < offsetof(s_OrderUpdate, OrderReceivedDateTime) + sizeof(OrderReceivedDateTime))
			return 0;

		return OrderReceivedDateTime;
	}
	/*==========================================================================*/
	const char* s_OrderUpdate::GetPreviousClientOrderID()
	{
		if (Size < offsetof(s_OrderUpdate, PreviousClientOrderID) + sizeof(PreviousClientOrderID))
			return "";

		PreviousClientOrderID[sizeof(PreviousClientOrderID) - 1] = '\0';

		return PreviousClientOrderID;
	}
	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_OrderUpdate::GetLatestTransactionDateTime() const
	{
		if (Size < offsetof(s_OrderUpdate, LatestTransactionDateTime) + sizeof(LatestTransactionDateTime))
			return 0.0;

		return LatestTransactionDateTime;
	}
	/*==========================================================================*/
	void s_OrderUpdate::SetPreviousClientOrderID(const char* NewValue)
	{
		strncpy(PreviousClientOrderID, NewValue, sizeof(PreviousClientOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_OrderUpdate::GetFreeFormText()
	{
		if (Size < offsetof(s_OrderUpdate, FreeFormText) + sizeof(FreeFormText))
			return "";

		FreeFormText[sizeof(FreeFormText) - 1] = '\0';

		return FreeFormText;
	}

	/*==========================================================================*/
	void s_OrderUpdate::SetFreeFormText(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(FreeFormText) - 1);
	}

	/****************************************************************************/
	// s_OpenOrdersRequestReject

	/*==========================================================================*/
	uint16_t s_OpenOrdersReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_OpenOrdersReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_OpenOrdersReject), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_OpenOrdersReject::GetRequestID() const
	{
		if (Size < offsetof(s_OpenOrdersReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	void s_OpenOrdersReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}
	/*==========================================================================*/
	const char* s_OpenOrdersReject::GetRejectText()
	{
		if (Size < offsetof(s_OpenOrdersReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}


	/****************************************************************************/
	// s_HistoricalOrderFillReport

	/*==========================================================================*/
	uint16_t s_HistoricalOrderFillResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalOrderFillResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalOrderFillResponse), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_HistoricalOrderFillResponse::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	const char* s_HistoricalOrderFillResponse::GetSymbol()
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_HistoricalOrderFillResponse::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalOrderFillResponse::GetExchange()
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_HistoricalOrderFillResponse::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	int32_t s_HistoricalOrderFillResponse::GetMessageNumber() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}
	/*==========================================================================*/
	int32_t s_HistoricalOrderFillResponse::GetTotalNumberMessages() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}
	/*==========================================================================*/
	const char* s_HistoricalOrderFillResponse::GetServerOrderID()
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, ServerOrderID) + sizeof(ServerOrderID))
			return "";

		ServerOrderID[sizeof(ServerOrderID) - 1] = '\0';

		return ServerOrderID;
	}

	/*==========================================================================*/
	void s_HistoricalOrderFillResponse::SetServerOrderID(const char* NewValue)
	{
		strncpy(ServerOrderID, NewValue, sizeof(ServerOrderID) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalOrderFillResponse::GetTradeAccount()
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_HistoricalOrderFillResponse::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}
	/*==========================================================================*/
	const char* s_HistoricalOrderFillResponse::GetUniqueExecutionID()
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, UniqueExecutionID) + sizeof(UniqueExecutionID))
			return "";

		UniqueExecutionID[sizeof(UniqueExecutionID) - 1] = '\0';

		return UniqueExecutionID;
	}
	/*==========================================================================*/
	void s_HistoricalOrderFillResponse::SetUniqueExecutionID(const char* NewValue)
	{
		strncpy(UniqueExecutionID, NewValue, sizeof(UniqueExecutionID) - 1);
	}
	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetPrice() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, Price) + sizeof(Price))
			return 0;

		return Price;
	}
	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetQuantity() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	t_DateTime s_HistoricalOrderFillResponse::GetDateTime() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	BuySellEnum s_HistoricalOrderFillResponse::GetBuySell() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, BuySell) + sizeof(BuySell))
			return (BuySellEnum)0;

		return BuySell;
	}

	/*==========================================================================*/
	OpenCloseTradeEnum s_HistoricalOrderFillResponse::GetOpenClose() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, OpenClose) + sizeof(OpenClose))
			return (OpenCloseTradeEnum)0;

		return OpenClose;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalOrderFillResponse::GetNoOrderFills() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, NoOrderFills) + sizeof(NoOrderFills))
			return 0;

		return NoOrderFills;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetHighPriceDuringPosition() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, HighPriceDuringPosition) + sizeof(HighPriceDuringPosition))
			return 0.0;

		return HighPriceDuringPosition;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetLowPriceDuringPosition() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, LowPriceDuringPosition) + sizeof(LowPriceDuringPosition))
			return 0.0;

		return LowPriceDuringPosition;
	}

	/*==========================================================================*/
	double s_HistoricalOrderFillResponse::GetPositionQuantity() const
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, PositionQuantity) + sizeof(PositionQuantity))
			return DBL_MAX;

		return PositionQuantity;
	}

	/*==========================================================================*/
	void s_HistoricalOrderFillResponse::SetInfoText(const char* NewValue)
	{
		strncpy(InfoText, NewValue, sizeof(InfoText) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalOrderFillResponse::GetInfoText()
	{
		if (Size < offsetof(s_HistoricalOrderFillResponse, InfoText) + sizeof(InfoText))
			return "";

		InfoText[sizeof(InfoText) - 1] = '\0';

		return InfoText;
	}

	/****************************************************************************/
	// s_PositionUpdate

	/*==========================================================================*/
	uint16_t s_PositionUpdate::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_PositionUpdate::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_PositionUpdate), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	void s_PositionUpdate::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	void s_PositionUpdate::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}
	/*==========================================================================*/
	int32_t s_PositionUpdate::GetRequestID() const
	{
		if (Size < offsetof(s_PositionUpdate, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	const char* s_PositionUpdate::GetSymbol()
	{
		if (Size < offsetof(s_PositionUpdate, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}
	/*==========================================================================*/
	const char* s_PositionUpdate::GetExchange()
	{
		if (Size < offsetof(s_PositionUpdate, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_PositionUpdate::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	int32_t s_PositionUpdate::GetMessageNumber() const
	{
		if (Size < offsetof(s_PositionUpdate, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}
	/*==========================================================================*/
	int32_t s_PositionUpdate::GetTotalNumberMessages() const
	{
		if (Size < offsetof(s_PositionUpdate, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}	
	/*==========================================================================*/
	const char* s_PositionUpdate::GetTradeAccount()
	{
		if (Size < offsetof(s_PositionUpdate, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_PositionUpdate::SetPositionIdentifier(const char* NewValue)
	{
		strncpy(PositionIdentifier, NewValue, sizeof(PositionIdentifier) - 1);
	}
	/*==========================================================================*/
	const char* s_PositionUpdate::GetPositionIdentifier()
	{
		if (Size < offsetof(s_PositionUpdate, PositionIdentifier) + sizeof(PositionIdentifier))
			return "";

		PositionIdentifier[sizeof(PositionIdentifier) - 1] = '\0';

		return PositionIdentifier;
	}
	/*==========================================================================*/
	double s_PositionUpdate::GetQuantity() const
	{
		if (Size < offsetof(s_PositionUpdate, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}/*==========================================================================*/
	double s_PositionUpdate::GetAveragePrice() const
	{
		if (Size < offsetof(s_PositionUpdate, AveragePrice) + sizeof(AveragePrice))
			return 0;

		return AveragePrice;
	}
	/*==========================================================================*/	
	uint8_t s_PositionUpdate::GetNoPositions() const
	{
		if (Size < offsetof(s_PositionUpdate, NoPositions) + sizeof(NoPositions))
			return 0;

		return NoPositions;
	}
	/*==========================================================================*/
	uint8_t s_PositionUpdate::GetUnsolicited() const
	{
		if (Size < offsetof(s_PositionUpdate, Unsolicited) + sizeof(Unsolicited))
			return 0;

		return Unsolicited;
	}
	/*==========================================================================*/
	double s_PositionUpdate::GetMarginRequirement() const
	{
		if (Size < offsetof(s_PositionUpdate, MarginRequirement) + sizeof(MarginRequirement))
			return 0.0;

		return MarginRequirement;
	}
	/*==========================================================================*/
	t_DateTime4Byte s_PositionUpdate::GetEntryDateTime() const
	{
		if (Size < offsetof(s_PositionUpdate, EntryDateTime) + sizeof(EntryDateTime))
			return 0;

		return EntryDateTime;
	}
	/*==========================================================================*/
	double s_PositionUpdate::GetQuantityLimit() const
	{
		if (Size < offsetof(s_PositionUpdate, QuantityLimit) + sizeof(QuantityLimit))
			return 0.0;

		return QuantityLimit;
	}

	/****************************************************************************/
	// s_AddCorrectingOrderFill

	/*==========================================================================*/
	uint16_t s_AddCorrectingOrderFill::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AddCorrectingOrderFill::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AddCorrectingOrderFill), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	void s_AddCorrectingOrderFill::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}
	/*==========================================================================*/
	const char* s_AddCorrectingOrderFill::GetSymbol()
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}
	/*==========================================================================*/
	void s_AddCorrectingOrderFill::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	const char* s_AddCorrectingOrderFill::GetExchange()
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}
	/*==========================================================================*/
	void s_AddCorrectingOrderFill::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}
	/*==========================================================================*/
	const char* s_AddCorrectingOrderFill::GetTradeAccount()
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	void s_AddCorrectingOrderFill::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}
	/*==========================================================================*/
	const char* s_AddCorrectingOrderFill::GetClientOrderID()
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}
	/*==========================================================================*/
	DTC::BuySellEnum s_AddCorrectingOrderFill::GetBuySell() const
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, BuySell) + sizeof(BuySell))
			return DTC::BUY_SELL_UNSET;

		return BuySell;
	}
	/*==========================================================================*/
	double s_AddCorrectingOrderFill::GetFillPrice() const
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, FillPrice) + sizeof(FillPrice))
			return 0;

		return FillPrice;
	}
	/*==========================================================================*/
	double s_AddCorrectingOrderFill::GetFillQuantity() const
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, FillQuantity) + sizeof(FillQuantity))
			return 0;

		return FillQuantity;
	}
	/*==========================================================================*/
	void s_AddCorrectingOrderFill::SetFreeFormText(const char* NewValue)
	{
		strncpy(FreeFormText, NewValue, sizeof(FreeFormText) - 1);
	}
	/*==========================================================================*/
	const char* s_AddCorrectingOrderFill::GetFreeFormText()
	{
		if (Size < offsetof(s_AddCorrectingOrderFill, FreeFormText) + sizeof(FreeFormText))
			return "";

		FreeFormText[sizeof(FreeFormText) - 1] = '\0';

		return FreeFormText;
	}


	/****************************************************************************/
	// s_CorrectingOrderFillResponse

	/*==========================================================================*/
	uint16_t s_CorrectingOrderFillResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_CorrectingOrderFillResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_CorrectingOrderFillResponse), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	void s_CorrectingOrderFillResponse::SetClientOrderID(const char* NewValue)
	{
		strncpy(ClientOrderID, NewValue, sizeof(ClientOrderID) - 1);
	}
	/*==========================================================================*/
	const char* s_CorrectingOrderFillResponse::GetClientOrderID()
	{
		if (Size < offsetof(s_CorrectingOrderFillResponse, ClientOrderID) + sizeof(ClientOrderID))
			return "";

		ClientOrderID[sizeof(ClientOrderID) - 1] = '\0';

		return ClientOrderID;
	}
	
	/*==========================================================================*/
	void s_CorrectingOrderFillResponse::SetResultText(const char* NewValue)
	{
		strncpy(ResultText, NewValue, sizeof(ResultText) - 1);
	}
	/*==========================================================================*/
	const char* s_CorrectingOrderFillResponse::GetResultText()
	{
		if (Size < offsetof(s_CorrectingOrderFillResponse, ResultText) + sizeof(ResultText))
			return "";

		ResultText[sizeof(ResultText) - 1] = '\0';

		return ResultText;
	}


	/****************************************************************************/
	// s_AccountsRequest

	/*==========================================================================*/
	uint16_t s_TradeAccountsRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_TradeAccountsRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_TradeAccountsRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	int32_t s_TradeAccountsRequest::GetRequestID() const
	{
		if (Size < offsetof(s_TradeAccountsRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_AccountListResponse

	/*==========================================================================*/
	uint16_t s_TradeAccountResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_TradeAccountResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_TradeAccountResponse), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_TradeAccountResponse::GetMessageNumber() const
	{
		if (Size < offsetof(s_TradeAccountResponse, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}
	/*==========================================================================*/
	int32_t s_TradeAccountResponse::GetTotalNumberMessages() const
	{
		if (Size < offsetof(s_TradeAccountResponse, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}		
	/*==========================================================================*/
	void s_TradeAccountResponse::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}
	/*==========================================================================*/
	const char* s_TradeAccountResponse::GetTradeAccount()
	{
		if (Size < offsetof(s_TradeAccountResponse, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}
	/*==========================================================================*/
	int32_t s_TradeAccountResponse::GetRequestID() const
	{
		if (Size < offsetof(s_TradeAccountResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/****************************************************************************/
	// s_ExchangeListRequest

	/*==========================================================================*/
	uint16_t s_ExchangeListRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_ExchangeListRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_ExchangeListRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_ExchangeListRequest::GetRequestID() const
	{
		if (Size < offsetof(s_ExchangeListRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}


	/****************************************************************************/
	// s_ExchangeListResponse

	/*==========================================================================*/
	uint16_t s_ExchangeListResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_ExchangeListResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_ExchangeListResponse), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_ExchangeListResponse::GetExchange()
	{
		if (Size < offsetof(s_ExchangeListResponse, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_ExchangeListResponse::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	const char* s_ExchangeListResponse::GetDescription()
	{
		if (Size < offsetof(s_ExchangeListResponse, Description) + sizeof(Description))
			return "";

		Description[sizeof(Exchange) - 1] = '\0';

		return Description;
	}

	/*==========================================================================*/
	void s_ExchangeListResponse::SetDescription(const char* NewValue)
	{
		strncpy(Description, NewValue, sizeof(Description) - 1);
	}
	/*==========================================================================*/
	int32_t s_ExchangeListResponse::GetRequestID() const
	{
		if (Size < offsetof(s_ExchangeListResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	uint8_t s_ExchangeListResponse::GetIsFinalMessage() const
	{
		if (Size < offsetof(s_ExchangeListResponse, IsFinalMessage) + sizeof(IsFinalMessage))
			return 0;

		return IsFinalMessage;
	}


	/****************************************************************************/
	// s_SymbolsForExchangeRequest

	/*==========================================================================*/
	uint16_t s_SymbolsForExchangeRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SymbolsForExchangeRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SymbolsForExchangeRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_SymbolsForExchangeRequest::GetRequestID() const
	{
		if (Size < offsetof(s_SymbolsForExchangeRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	const char* s_SymbolsForExchangeRequest::GetExchange()
	{
		if (Size < offsetof(s_SymbolsForExchangeRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_SymbolsForExchangeRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	SecurityTypeEnum s_SymbolsForExchangeRequest::GetSecurityType() const
	{
		if (Size < offsetof(s_SymbolsForExchangeRequest, SecurityType) + sizeof(SecurityType))
			return (SecurityTypeEnum)0;

		return SecurityType;
	}

	/*==========================================================================*/
	RequestActionEnum s_SymbolsForExchangeRequest::GetRequestAction() const
	{
		if (Size < offsetof(s_SymbolsForExchangeRequest, RequestAction) + sizeof(RequestAction))
			return RequestActionEnum::SUBSCRIBE;

		return RequestAction;
	}

	/*==========================================================================*/
	const char* s_SymbolsForExchangeRequest::GetSymbol()
	{
		if (Size < offsetof(s_SymbolsForExchangeRequest, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_SymbolsForExchangeRequest::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/****************************************************************************/
	// s_UnderlyingSymbolsForExchangeRequest

	/*==========================================================================*/
	uint16_t s_UnderlyingSymbolsForExchangeRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_UnderlyingSymbolsForExchangeRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_UnderlyingSymbolsForExchangeRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_UnderlyingSymbolsForExchangeRequest::GetRequestID() const
	{
		if (Size < offsetof(s_UnderlyingSymbolsForExchangeRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	const char* s_UnderlyingSymbolsForExchangeRequest::GetExchange()
	{
		if (Size < offsetof(s_UnderlyingSymbolsForExchangeRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_UnderlyingSymbolsForExchangeRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	SecurityTypeEnum s_UnderlyingSymbolsForExchangeRequest::GetSecurityType() const
	{
		if (Size < offsetof(s_UnderlyingSymbolsForExchangeRequest, SecurityType) + sizeof(SecurityType))
			return (SecurityTypeEnum)0;

		return SecurityType;
	}

	/****************************************************************************/
	// s_SymbolsForUnderlyingRequest

	/*==========================================================================*/
	uint16_t s_SymbolsForUnderlyingRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SymbolsForUnderlyingRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SymbolsForUnderlyingRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_SymbolsForUnderlyingRequest::GetRequestID() const
	{
		if (Size < offsetof(s_SymbolsForUnderlyingRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	const char* s_SymbolsForUnderlyingRequest::GetExchange()
	{
		if (Size < offsetof(s_SymbolsForUnderlyingRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}
	/*==========================================================================*/
	void s_SymbolsForUnderlyingRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	void s_SymbolsForUnderlyingRequest::SetUnderlyingSymbol(const char* NewValue)
	{
		strncpy(UnderlyingSymbol, NewValue, sizeof(UnderlyingSymbol) - 1);
	}
	/*==========================================================================*/
	const char* s_SymbolsForUnderlyingRequest::GetUnderlyingSymbol()
	{
		if (Size < offsetof(s_SymbolsForUnderlyingRequest, UnderlyingSymbol) + sizeof(UnderlyingSymbol))
			return "";

		UnderlyingSymbol[sizeof(UnderlyingSymbol) - 1] = '\0';

		return UnderlyingSymbol;
	}


	/*==========================================================================*/
	SecurityTypeEnum s_SymbolsForUnderlyingRequest::GetSecurityType() const
	{
		if (Size < offsetof(s_SymbolsForUnderlyingRequest, SecurityType) + sizeof(SecurityType))
			return (SecurityTypeEnum)0;

		return SecurityType;
	}


	/****************************************************************************/
	// s_SymbolSearchRequest

	/*==========================================================================*/
	uint16_t s_SymbolSearchRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SymbolSearchRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SymbolSearchRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_SymbolSearchRequest::GetExchange()
	{
		if (Size < offsetof(s_SymbolSearchRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_SymbolSearchRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	const char* s_SymbolSearchRequest::GetSearchText()
	{
		if (Size < offsetof(s_SymbolSearchRequest, SearchText) + sizeof(SearchText))
			return "";

		SearchText[sizeof(SearchText) - 1] = '\0';

		return SearchText;
	}

	/*==========================================================================*/
	void s_SymbolSearchRequest::SetSearchText(const char* NewValue)
	{
		strncpy(SearchText, NewValue, sizeof(SearchText) - 1);
	}

	/*==========================================================================*/
	int32_t s_SymbolSearchRequest::GetRequestID() const
	{
		if (Size < offsetof(s_SymbolSearchRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	SecurityTypeEnum s_SymbolSearchRequest::GetSecurityType() const
	{
		if (Size < offsetof(s_SymbolSearchRequest, SecurityType) + sizeof(SecurityType))
			return (SecurityTypeEnum)0;

		return SecurityType;
	}

	/*==========================================================================*/
	SearchTypeEnum s_SymbolSearchRequest::GetSearchType() const
	{
		if (Size < offsetof(s_SymbolSearchRequest, SearchType) + sizeof(SearchType))
			return (SearchTypeEnum)0;

		return SearchType;
	}

	/****************************************************************************/
	// s_SecurityDefinitionForSymbolRequest

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionForSymbolRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionForSymbolRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SecurityDefinitionForSymbolRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionForSymbolRequest::GetSymbol()
	{
		if (Size < offsetof(s_SecurityDefinitionForSymbolRequest, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionForSymbolRequest::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionForSymbolRequest::GetExchange()
	{
		if (Size < offsetof(s_SecurityDefinitionForSymbolRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionForSymbolRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	int32_t s_SecurityDefinitionForSymbolRequest::GetRequestID() const
	{
		if (Size < offsetof(s_SecurityDefinitionForSymbolRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}


	/****************************************************************************/
	// s_SecurityDefinitionResponse

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SecurityDefinitionResponse), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	int32_t s_SecurityDefinitionResponse::GetRequestID() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionResponse::GetSymbol()
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';  // Ensure that the null terminator exists

		return Symbol;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionResponse::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionResponse::GetExchange()
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';  // Ensure that the null terminator exists

		return Exchange;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionResponse::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	SecurityTypeEnum s_SecurityDefinitionResponse::GetSecurityType() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, SecurityType) + sizeof(SecurityType))
			return SECURITY_TYPE_UNSET;

		return SecurityType;
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionResponse::GetDescription()
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, Description) + sizeof(Description))
			return "";

		Description[sizeof(Description) - 1] = '\0';  // Ensure that the null terminator exists

		return Description;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionResponse::SetDescription(const char* NewValue)
	{
		strncpy(Description, NewValue, sizeof(Description) - 1);
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetMinPriceIncrement() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, MinPriceIncrement) + sizeof(MinPriceIncrement))
			return 0;

		return MinPriceIncrement;
	}

	/*==========================================================================*/
	PriceDisplayFormatEnum s_SecurityDefinitionResponse::GetPriceDisplayFormat() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, PriceDisplayFormat) + sizeof(PriceDisplayFormat))
			return PRICE_DISPLAY_FORMAT_UNSET;

		return PriceDisplayFormat;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetCurrencyValuePerIncrement() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, CurrencyValuePerIncrement) + sizeof(CurrencyValuePerIncrement))
			return 0;

		return CurrencyValuePerIncrement;
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetIsFinalMessage() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, IsFinalMessage) + sizeof(IsFinalMessage))
			return 0;

		return IsFinalMessage;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetFloatToIntPriceMultiplier() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, FloatToIntPriceMultiplier) + sizeof(FloatToIntPriceMultiplier))
			return 1.0f;

		return FloatToIntPriceMultiplier;
	}
	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetIntToFloatPriceDivisor() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, IntToFloatPriceDivisor) + sizeof(IntToFloatPriceDivisor))
			return 1.0f;

		return IntToFloatPriceDivisor;
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionResponse::GetUnderlyingSymbol()
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, UnderlyingSymbol) + sizeof(UnderlyingSymbol))
			return "";

		UnderlyingSymbol[sizeof(UnderlyingSymbol) - 1] = '\0';  // Ensure that the null terminator exists

		return UnderlyingSymbol;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionResponse::SetUnderlyingSymbol(const char* NewValue)
	{
		strncpy(UnderlyingSymbol, NewValue, sizeof(UnderlyingSymbol) - 1);
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetUpdatesBidAskOnly() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, UpdatesBidAskOnly) + sizeof(UpdatesBidAskOnly))
			return 0;

		return UpdatesBidAskOnly;
	}


	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetStrikePrice() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, StrikePrice) + sizeof(StrikePrice))
			return 0.0;

		return StrikePrice;
	}


	/*==========================================================================*/
	PutCallEnum s_SecurityDefinitionResponse::GetPutOrCall() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, PutOrCall) + sizeof(PutOrCall))
			return PC_UNSET;

		return PutOrCall;
	}


	/*==========================================================================*/
	uint32_t s_SecurityDefinitionResponse::GetShortInterest() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, ShortInterest) + sizeof(ShortInterest))
			return 0;

		return ShortInterest;
	}


	/*==========================================================================*/
	t_DateTime4Byte s_SecurityDefinitionResponse::GetSecurityExpirationDate() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, SecurityExpirationDate) + sizeof(SecurityExpirationDate))
			return 0;

		return SecurityExpirationDate;
	}


	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetBuyRolloverInterest() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, BuyRolloverInterest) + sizeof(BuyRolloverInterest))
			return 0.0;

		return BuyRolloverInterest;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetSellRolloverInterest() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, SellRolloverInterest) + sizeof(SellRolloverInterest))
			return 0.0;

		return SellRolloverInterest;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetEarningsPerShare() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, EarningsPerShare) + sizeof(EarningsPerShare))
			return 0.0;

		return EarningsPerShare;
	}

	/*==========================================================================*/
	uint32_t s_SecurityDefinitionResponse::GetSharesOutstanding() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, SharesOutstanding) + sizeof(SharesOutstanding))
			return 0;

		return SharesOutstanding;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetIntToFloatQuantityDivisor() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, IntToFloatQuantityDivisor) + sizeof(IntToFloatQuantityDivisor))
			return 0.0;

		return IntToFloatQuantityDivisor;
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetHasMarketDepthData() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, HasMarketDepthData) + sizeof(HasMarketDepthData))
			return 1;

		return HasMarketDepthData;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetDisplayPriceMultiplier() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, DisplayPriceMultiplier) + sizeof(DisplayPriceMultiplier))
			return 1.0;

		return DisplayPriceMultiplier;
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionResponse::GetExchangeSymbol()
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, ExchangeSymbol) + sizeof(ExchangeSymbol))
			return "";

		ExchangeSymbol[sizeof(ExchangeSymbol) - 1] = '\0';  // Ensure that the null terminator exists

		return ExchangeSymbol;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionResponse::SetExchangeSymbol(const char* NewValue)
	{
		strncpy(ExchangeSymbol, NewValue, sizeof(ExchangeSymbol) - 1);
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetInitialMarginRequirement() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, InitialMarginRequirement) + sizeof(InitialMarginRequirement))
			return 0.0;

		return InitialMarginRequirement;
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetMaintenanceMarginRequirement() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, MaintenanceMarginRequirement) + sizeof(MaintenanceMarginRequirement))
			return 0.0;

		return MaintenanceMarginRequirement;
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionResponse::GetCurrency()
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, Currency) + sizeof(Currency))
			return "";

		Currency[sizeof(Currency) - 1] = '\0';  // Ensure that the null terminator exists

		return Currency;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionResponse::SetCurrency(const char* NewValue)
	{
		strncpy(Currency, NewValue, sizeof(Currency) - 1);
	}

	/*==========================================================================*/
	float s_SecurityDefinitionResponse::GetContractSize() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, ContractSize) + sizeof(ContractSize))
			return 0.0;

		return ContractSize;
	}

	/*==========================================================================*/
	uint32_t s_SecurityDefinitionResponse::GetOpenInterest() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, OpenInterest) + sizeof(OpenInterest))
			return 0;

		return OpenInterest;
	}

	/*==========================================================================*/
	t_DateTime4Byte s_SecurityDefinitionResponse::GetRolloverDate() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, RolloverDate) + sizeof(RolloverDate))
			return 0;

		return RolloverDate;
	}

	/*==========================================================================*/
	uint8_t s_SecurityDefinitionResponse::GetIsDelayed() const
	{
		if (Size < offsetof(s_SecurityDefinitionResponse, IsDelayed) + sizeof(IsDelayed))
			return 0;

		return IsDelayed;
	}

	/****************************************************************************/
	// s_SecurityDefinitionReject

	/*==========================================================================*/
	uint16_t s_SecurityDefinitionReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_SecurityDefinitionReject), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_SecurityDefinitionReject::GetRequestID() const
	{
		return RequestID;
	}

	/*==========================================================================*/
	void s_SecurityDefinitionReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/*==========================================================================*/
	const char* s_SecurityDefinitionReject::GetRejectText()
	{
		if (Size < offsetof(s_SecurityDefinitionReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';  // Ensure that the null terminator exists

		return RejectText;
	}

	/****************************************************************************/
	// s_AccountBalanceRequest

	/*==========================================================================*/
	uint16_t s_AccountBalanceRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AccountBalanceRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AccountBalanceRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceRequest::GetRequestID() const
	{
		return RequestID;
	}

	/*==========================================================================*/
	void s_AccountBalanceRequest::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_AccountBalanceRequest::GetTradeAccount()
	{
		if (Size < offsetof(s_AccountBalanceRequest, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';  // Ensure that the null terminator exists

		return TradeAccount;
	}

	/****************************************************************************/
	// s_AccountBalanceReject

	/*==========================================================================*/
	uint16_t s_AccountBalanceReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AccountBalanceReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AccountBalanceReject), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	uint32_t s_AccountBalanceReject::GetRequestID() const
	{
		return RequestID;
	}

	/*==========================================================================*/
	void s_AccountBalanceReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/*==========================================================================*/
	const char* s_AccountBalanceReject::GetRejectText()
	{
		if (Size < offsetof(s_AccountBalanceReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';  // Ensure that the null terminator exists

		return RejectText;
	}


	/****************************************************************************/
	// s_AccountBalanceUpdate

	/*==========================================================================*/
	uint16_t s_AccountBalanceUpdate::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AccountBalanceUpdate::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AccountBalanceUpdate), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	void s_AccountBalanceUpdate::SetAccountCurrency(const char* NewValue)
	{
		strncpy(AccountCurrency, NewValue, sizeof(AccountCurrency) - 1);
	}
	/*==========================================================================*/
	void s_AccountBalanceUpdate::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}
	/*==========================================================================*/
	const char* s_AccountBalanceUpdate::GetAccountCurrency()
	{
		if (Size < offsetof(s_AccountBalanceUpdate, AccountCurrency) + sizeof(AccountCurrency))
			return "";

		AccountCurrency[sizeof(AccountCurrency) - 1] = '\0';  // Ensure that the null terminator exists

		return AccountCurrency;
	}
	/*==========================================================================*/
	const char* s_AccountBalanceUpdate::GetTradeAccount()
	{
		if (Size < offsetof(s_AccountBalanceUpdate, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';  // Ensure that the null terminator exists

		return TradeAccount;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceUpdate::GetRequestID() const
	{
		return RequestID;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetCashBalance() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, CashBalance) + sizeof(CashBalance))
			return 0;

		return CashBalance;
	}
	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetBalanceAvailableForNewPositions() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, BalanceAvailableForNewPositions) + sizeof(BalanceAvailableForNewPositions))
			return 0;

		return BalanceAvailableForNewPositions;
	}
	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetSecuritiesValue() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, SecuritiesValue) + sizeof(SecuritiesValue))
			return 0;

		return SecuritiesValue;
	}
	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetMarginRequirement() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, MarginRequirement) + sizeof(MarginRequirement))
			return 0;

		return MarginRequirement;
	}
	
	/*==========================================================================*/
	int32_t s_AccountBalanceUpdate::GetTotalNumberMessages() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, TotalNumberMessages) + sizeof(TotalNumberMessages))
			return 0;

		return TotalNumberMessages;
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceUpdate::GetMessageNumber() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, MessageNumber) + sizeof(MessageNumber))
			return 0;

		return MessageNumber;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetNoAccountBalances() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, NoAccountBalances) + sizeof(NoAccountBalances))
			return 0;

		return NoAccountBalances;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetUnsolicited() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, Unsolicited) + sizeof(Unsolicited))
			return 0;

		return Unsolicited;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetOpenPositionsProfitLoss() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, OpenPositionsProfitLoss) + sizeof(OpenPositionsProfitLoss))
			return 0.0;

		return OpenPositionsProfitLoss;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetDailyProfitLoss() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, DailyProfitLoss) + sizeof(DailyProfitLoss))
			return 0.0;

		return DailyProfitLoss;
	}

	/*==========================================================================*/
	void s_AccountBalanceUpdate::SetInfoText(const char* NewValue)
	{
		strncpy(InfoText, NewValue, sizeof(InfoText) - 1);
	}

	/*==========================================================================*/
	const char* s_AccountBalanceUpdate::GetInfoText()
	{
		if (Size < offsetof(s_AccountBalanceUpdate, InfoText) + sizeof(InfoText))
			return "";

		InfoText[sizeof(InfoText) - 1] = '\0';  // Ensure that the null terminator exists

		return InfoText;
	}

	/*==========================================================================*/
	uint64_t s_AccountBalanceUpdate::GetTransactionIdentifier() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, TransactionIdentifier) + sizeof(TransactionIdentifier))
			return 0;

		return TransactionIdentifier;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetDailyNetLossLimit() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, DailyNetLossLimit) + sizeof(DailyNetLossLimit))
			return 0.0;

		return DailyNetLossLimit;
	}

	/*==========================================================================*/
	double s_AccountBalanceUpdate::GetTrailingAccountValueToLimitPositions() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, TrailingAccountValueToLimitPositions) + sizeof(TrailingAccountValueToLimitPositions))
			return 0.0;

		return TrailingAccountValueToLimitPositions;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetDailyNetLossLimitReached() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, DailyNetLossLimitReached) + sizeof(DailyNetLossLimitReached))
			return 0;

		return DailyNetLossLimitReached;
	}

	/*==========================================================================*/
	uint8_t s_AccountBalanceUpdate::GetIsUnderRequiredMargin() const
	{
		if (Size < offsetof(s_AccountBalanceUpdate, IsUnderRequiredMargin) + sizeof(IsUnderRequiredMargin))
			return 0;

		return IsUnderRequiredMargin;
	}

	/****************************************************************************/
	// struct s_AccountBalanceAdjustment

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustment::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AccountBalanceAdjustment::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AccountBalanceAdjustment), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceAdjustment::GetRequestID() const
	{
		if (Size < offsetof(s_AccountBalanceAdjustment, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	void s_AccountBalanceAdjustment::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_AccountBalanceAdjustment::GetTradeAccount()
	{
		if (Size < offsetof(s_AccountBalanceAdjustment, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';  // Ensure that the null terminator exists

		return TradeAccount;
	}

	/*==========================================================================*/
	double s_AccountBalanceAdjustment::GetCreditAmount() const
	{
		if (Size < offsetof(s_AccountBalanceAdjustment, CreditAmount) + sizeof(CreditAmount))
			return 0.0;

		return CreditAmount;
	}

	/*==========================================================================*/
	double s_AccountBalanceAdjustment::GetDebitAmount() const
	{
		if (Size < offsetof(s_AccountBalanceAdjustment, DebitAmount) + sizeof(DebitAmount))
			return 0.0;

		return DebitAmount;
	}

	/*==========================================================================*/
	void s_AccountBalanceAdjustment::SetCurrency(const char* NewValue)
	{
		strncpy(Currency, NewValue, sizeof(Currency) - 1);
	}

	/*==========================================================================*/
	const char* s_AccountBalanceAdjustment::GetCurrency()
	{
		if (Size < offsetof(s_AccountBalanceAdjustment, Currency) + sizeof(Currency))
			return "";

		Currency[sizeof(Currency) - 1] = '\0';  // Ensure that the null terminator exists

		return Currency;
	}

	/*==========================================================================*/
	void s_AccountBalanceAdjustment::SetReason(const char* NewValue)
	{
		strncpy(Reason, NewValue, sizeof(Reason) - 1);
	}

	/*==========================================================================*/
	const char* s_AccountBalanceAdjustment::GetReason()
	{
		if (Size < offsetof(s_AccountBalanceAdjustment, Reason) + sizeof(Reason))
			return "";

		Reason[sizeof(Reason) - 1] = '\0';  // Ensure that the null terminator exists

		return Reason;
	}

	/****************************************************************************/
	// struct s_AccountBalanceAdjustmentReject

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustmentReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AccountBalanceAdjustmentReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AccountBalanceAdjustmentReject), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceAdjustmentReject::GetRequestID() const
	{
		if (Size < offsetof(s_AccountBalanceAdjustmentReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	void s_AccountBalanceAdjustmentReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/*==========================================================================*/
	const char* s_AccountBalanceAdjustmentReject::GetRejectText()
	{
		if (Size < offsetof(s_AccountBalanceAdjustmentReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';  // Ensure that the null terminator exists

		return RejectText;
	}

	/****************************************************************************/
	// struct s_AccountBalanceAdjustmentComplete

	/*==========================================================================*/
	uint16_t s_AccountBalanceAdjustmentComplete::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AccountBalanceAdjustmentComplete::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AccountBalanceAdjustmentComplete), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_AccountBalanceAdjustmentComplete::GetRequestID() const
	{
		if (Size < offsetof(s_AccountBalanceAdjustmentComplete, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	int64_t s_AccountBalanceAdjustmentComplete::GetTransactionID() const
	{
		if (Size < offsetof(s_AccountBalanceAdjustmentComplete, TransactionID) + sizeof(TransactionID))
			return 0;

		return TransactionID;
	}

	/****************************************************************************/
	// struct s_HistoricalAccountBalancesRequest

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalancesRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalancesRequest::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalAccountBalancesRequest), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_HistoricalAccountBalancesRequest::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalAccountBalancesRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalancesRequest::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalAccountBalancesRequest::GetTradeAccount()
	{
		if (Size < offsetof(s_HistoricalAccountBalancesRequest, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';  // Ensure that the null terminator exists

		return TradeAccount;
	}

	/*==========================================================================*/
	t_DateTime s_HistoricalAccountBalancesRequest::GetStartDateTime() const
	{
		if (Size < offsetof(s_HistoricalAccountBalancesRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/****************************************************************************/
	// struct s_HistoricalAccountBalancesReject

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalancesReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalancesReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalAccountBalancesReject), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	uint32_t s_HistoricalAccountBalancesReject::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalAccountBalancesReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalancesReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalAccountBalancesReject::GetRejectText()
	{
		if (Size < offsetof(s_HistoricalAccountBalancesReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';  // Ensure that the null terminator exists

		return RejectText;
	}

	/****************************************************************************/
	// struct s_HistoricalAccountBalanceResponse

	/*==========================================================================*/
	uint16_t s_HistoricalAccountBalanceResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalanceResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalAccountBalanceResponse), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_HistoricalAccountBalanceResponse::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_HistoricalAccountBalanceResponse::GetDateTime() const
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	double s_HistoricalAccountBalanceResponse::GetCashBalance() const
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, CashBalance) + sizeof(CashBalance))
			return 0.0;

		return CashBalance;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalanceResponse::SetAccountCurrency(const char* NewValue)
	{
		strncpy(AccountCurrency, NewValue, sizeof(AccountCurrency) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalAccountBalanceResponse::GetAccountCurrency()
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, AccountCurrency) + sizeof(AccountCurrency))
			return "";

		AccountCurrency[sizeof(AccountCurrency) - 1] = '\0';  // Ensure that the null terminator exists

		return AccountCurrency;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalanceResponse::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalAccountBalanceResponse::GetTradeAccount()
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';  // Ensure that the null terminator exists

		return TradeAccount;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalAccountBalanceResponse::GetIsFinalResponse() const
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, IsFinalResponse) + sizeof(IsFinalResponse))
			return 0;

		return IsFinalResponse;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalAccountBalanceResponse::GetNoAccountBalances() const
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, NoAccountBalances) + sizeof(NoAccountBalances))
			return 0;

		return NoAccountBalances;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalanceResponse::SetInfoText(const char* NewValue)
	{
		strncpy(InfoText, NewValue, sizeof(InfoText) - 1);
	}
	
	/*==========================================================================*/
	const char* s_HistoricalAccountBalanceResponse::GetInfoText()
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, InfoText) + sizeof(InfoText))
			return "";

		InfoText[sizeof(InfoText) - 1] = '\0';  // Ensure that the null terminator exists

		return InfoText;
	}

	/*==========================================================================*/
	void s_HistoricalAccountBalanceResponse::SetTransactionId(const char* NewValue)
	{
		strncpy(TransactionId, NewValue, sizeof(TransactionId) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalAccountBalanceResponse::GetTransactionId()
	{
		if (Size < offsetof(s_HistoricalAccountBalanceResponse, TransactionId) + sizeof(TransactionId))
			return "";

		TransactionId[sizeof(TransactionId) - 1] = '\0';  // Ensure that the null terminator exists

		return TransactionId;
	}

	/****************************************************************************/
	// s_UserMessage

	/*==========================================================================*/
	uint16_t s_UserMessage::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_UserMessage::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_UserMessage), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	void s_UserMessage::SetUserMessage(const char* NewValue)
	{
		strncpy(UserMessage, NewValue, sizeof(UserMessage) - 1);
	}
	/*==========================================================================*/
	const char* s_UserMessage::GetUserMessage()
	{
		if (Size < offsetof(s_UserMessage, UserMessage) + sizeof(UserMessage))
			return "";

		UserMessage[sizeof(UserMessage) - 1] = '\0';  // Ensure that the null terminator exists

		return UserMessage;
	}

	/*==========================================================================*/
	uint8_t s_UserMessage::GetIsPopupMessage() const
	{
		if (Size < offsetof(s_UserMessage, IsPopupMessage) + sizeof(IsPopupMessage))
			return 0;

		return IsPopupMessage;
	}


	/****************************************************************************/
	// s_GeneralLogMessage

	/*==========================================================================*/
	uint16_t s_GeneralLogMessage::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_GeneralLogMessage::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_GeneralLogMessage), *static_cast<uint16_t*>( p_SourceData) ));
	}


	/*==========================================================================*/
	const char* s_GeneralLogMessage::GetMessageText()
	{
		if (Size < offsetof(s_GeneralLogMessage, MessageText) + sizeof(MessageText))
			return "";

		MessageText[sizeof(MessageText) - 1] = '\0';

		return MessageText;
	}

	/*==========================================================================*/
	void s_GeneralLogMessage::SetMessageText(const char* NewValue)
	{
		strncpy(MessageText, NewValue, sizeof(MessageText) - 1);
	}

	/****************************************************************************/
	// s_AlertMessage

	/*==========================================================================*/
	uint16_t s_AlertMessage::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_AlertMessage::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_AlertMessage), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	void s_AlertMessage::SetMessageText(const char* NewValue)
	{
		strncpy(MessageText, NewValue, sizeof(MessageText) - 1);
	}

	/*==========================================================================*/
	const char* s_AlertMessage::GetMessageText()
	{
		if (Size < offsetof(s_AlertMessage, MessageText) + sizeof(MessageText))
			return "";

		MessageText[sizeof(MessageText) - 1] = '\0';

		return MessageText;
	}

	/*==========================================================================*/
	void s_AlertMessage::SetTradeAccount(const char* NewValue)
	{
		strncpy(TradeAccount, NewValue, sizeof(TradeAccount) - 1);
	}

	/*==========================================================================*/
	const char* s_AlertMessage::GetTradeAccount()
	{
		if (Size < offsetof(s_AlertMessage, TradeAccount) + sizeof(TradeAccount))
			return "";

		TradeAccount[sizeof(TradeAccount) - 1] = '\0';

		return TradeAccount;
	}

	/****************************************************************************/
	// s_JournalEntryAdd

	/*==========================================================================*/
	uint16_t s_JournalEntryAdd::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_JournalEntryAdd::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_JournalEntryAdd), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	void s_JournalEntryAdd::SetJournalEntry(const char* NewValue)
	{
		strncpy(JournalEntry, NewValue, sizeof(JournalEntry) - 1);
	}

	/*==========================================================================*/
	const char* s_JournalEntryAdd::GetJournalEntry()
	{
		if (Size < offsetof(s_JournalEntryAdd, JournalEntry) + sizeof(JournalEntry))
			return "";

		JournalEntry[sizeof(JournalEntry) - 1] = '\0';

		return JournalEntry;
	}

	/*==========================================================================*/
	t_DateTime s_JournalEntryAdd::GetDateTime() const
	{
		if (Size < offsetof(s_JournalEntryAdd, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/****************************************************************************/
	// s_JournalEntriesRequest

	/*==========================================================================*/
	uint16_t s_JournalEntriesRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_JournalEntriesRequest::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_JournalEntriesRequest), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_JournalEntriesRequest::GetRequestID() const
	{
		if (Size < offsetof(s_JournalEntriesRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	t_DateTime s_JournalEntriesRequest::GetStartDateTime() const
	{
		if (Size < offsetof(s_JournalEntriesRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/****************************************************************************/
	// s_JournalEntriesReject

	/*==========================================================================*/
	uint16_t s_JournalEntriesReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_JournalEntriesReject::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_JournalEntriesReject), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_JournalEntriesReject::GetRequestID() const
	{
		if (Size < offsetof(s_JournalEntriesReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	void s_JournalEntriesReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/*==========================================================================*/
	const char* s_JournalEntriesReject::GetRejectText()
	{
		if (Size < offsetof(s_JournalEntriesReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}

	/****************************************************************************/
	// s_JournalEntryResponse

	/*==========================================================================*/
	uint16_t s_JournalEntryResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_JournalEntryResponse::CopyFrom(void * p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_JournalEntryResponse), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	void s_JournalEntryResponse::SetJournalEntry(const char* NewValue)
	{
		strncpy(JournalEntry, NewValue, sizeof(JournalEntry) - 1);
	}

	/*==========================================================================*/
	const char* s_JournalEntryResponse::GetJournalEntry()
	{
		if (Size < offsetof(s_JournalEntryResponse, JournalEntry) + sizeof(JournalEntry))
			return "";

		JournalEntry[sizeof(JournalEntry) - 1] = '\0';

		return JournalEntry;
	}

	/*==========================================================================*/
	t_DateTime s_JournalEntryResponse::GetDateTime() const
	{
		if (Size < offsetof(s_JournalEntryResponse, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	uint8_t s_JournalEntryResponse::GetIsFinalResponse() const
	{
		if (Size < offsetof(s_JournalEntryResponse, IsFinalResponse) + sizeof(IsFinalResponse))
			return 0;

		return IsFinalResponse;
	}

	/****************************************************************************/
	// s_HistoricalPriceDataRequest

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataRequest), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_HistoricalPriceDataRequest::GetSymbol()
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataRequest::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalPriceDataRequest::GetExchange()
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRequest::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	uint32_t s_HistoricalPriceDataRequest::GetMaxDaysToReturn() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, MaxDaysToReturn) + sizeof(MaxDaysToReturn))
			return 0;

		return MaxDaysToReturn;
	}
	/*==========================================================================*/
	t_DateTime s_HistoricalPriceDataRequest::GetEndDateTime() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, EndDateTime) + sizeof(EndDateTime))
			return 0;

		return EndDateTime;
	}
	/*==========================================================================*/
	t_DateTime s_HistoricalPriceDataRequest::GetStartDateTime() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}
	/*==========================================================================*/
	HistoricalDataIntervalEnum s_HistoricalPriceDataRequest::GetRecordInterval() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, RecordInterval) + sizeof(RecordInterval))
			return (HistoricalDataIntervalEnum)0;

		return RecordInterval;
	}
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataRequest::GetUseZLibCompression() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, UseZLibCompression) + sizeof(UseZLibCompression))
			return 0;

		return UseZLibCompression;
	}
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataRequest::GetRequestDividendAdjustedStockData() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, RequestDividendAdjustedStockData) + sizeof(RequestDividendAdjustedStockData))
			return 0;

		return RequestDividendAdjustedStockData;
	}
	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataRequest::GetInteger_1() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRequest, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}


	/****************************************************************************/
	// s_HistoricalPriceDataHeaderResponse

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataResponseHeader::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataResponseHeader::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataResponseHeader), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataResponseHeader::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataResponseHeader, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	HistoricalDataIntervalEnum s_HistoricalPriceDataResponseHeader::GetRecordInterval() const
	{
		if (Size < offsetof(s_HistoricalPriceDataResponseHeader, RecordInterval) + sizeof(RecordInterval))
			return (HistoricalDataIntervalEnum)0;

		return RecordInterval;
	}
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataResponseHeader::GetUseZLibCompression() const
	{
		if (Size < offsetof(s_HistoricalPriceDataResponseHeader, UseZLibCompression) + sizeof(UseZLibCompression))
			return 0;

		return UseZLibCompression;
	}
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataResponseHeader::GetNoRecordsToReturn() const
	{
		if (Size < offsetof(s_HistoricalPriceDataResponseHeader, NoRecordsToReturn) + sizeof(NoRecordsToReturn))
			return 0;

		return NoRecordsToReturn;
	}
	/*==========================================================================*/
	float s_HistoricalPriceDataResponseHeader::GetIntToFloatPriceDivisor() const
	{
		if (Size < offsetof(s_HistoricalPriceDataResponseHeader, IntToFloatPriceDivisor) + sizeof(IntToFloatPriceDivisor))
			return 1.0f;

		return IntToFloatPriceDivisor;
	}

	/****************************************************************************/
	// s_HistoricalPriceDataReject

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataReject),*static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	const char* s_HistoricalPriceDataReject::GetRejectText()
	{
		if (Size < offsetof(s_MarketDataReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}

	/*==========================================================================*/
	HistoricalPriceDataRejectReasonCodeEnum s_HistoricalPriceDataReject::GetRejectReasonCode() const
	{
		if (Size < offsetof(s_HistoricalPriceDataReject, RejectReasonCode) + sizeof(RejectReasonCode))
			return HPDR_UNSET;

		return RejectReasonCode;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataReject::GetRetryTimeInSeconds() const
	{
		if (Size < offsetof(s_HistoricalPriceDataReject, RetryTimeInSeconds) + sizeof(RetryTimeInSeconds))
			return 0;

		return RetryTimeInSeconds;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataReject::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}



	/****************************************************************************/
	// s_HistoricalPriceDataRecordResponse

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataRecordResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataRecordResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataRecordResponse), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataRecordResponse::GetOpenPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, OpenPrice) + sizeof(OpenPrice))
			return 0;

		return OpenPrice;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataRecordResponse::GetHighPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, HighPrice) + sizeof(HighPrice))
			return 0;

		return HighPrice;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataRecordResponse::GetLowPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, LowPrice) + sizeof(LowPrice))
			return 0;

		return LowPrice;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataRecordResponse::GetLastPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, LastPrice) + sizeof(LastPrice))
			return 0;

		return LastPrice;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataRecordResponse::GetVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}
	/*==========================================================================*/
	uint32_t s_HistoricalPriceDataRecordResponse::GetOpenInterest() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, OpenInterest) + sizeof(OpenInterest))
			return 0;

		return OpenInterest;
	}
	/*==========================================================================*/
	uint32_t s_HistoricalPriceDataRecordResponse::GetNumTrades() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, NumTrades) + sizeof(NumTrades))
			return 0;

		return NumTrades;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataRecordResponse::GetBidVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, BidVolume) + sizeof(BidVolume))
			return 0;

		return BidVolume;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataRecordResponse::GetAskVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, AskVolume) + sizeof(AskVolume))
			return 0;

		return AskVolume;
	}
	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_HistoricalPriceDataRecordResponse::GetStartDateTime() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataRecordResponse::GetIsFinalRecord() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse, IsFinalRecord) + sizeof(IsFinalRecord))
			return 0;

		return IsFinalRecord;
	}


	/****************************************************************************/
	// s_HistoricalPriceDataTickRecordResponse

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataTickRecordResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataTickRecordResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataTickRecordResponse), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	int32_t s_HistoricalPriceDataTickRecordResponse::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_HistoricalPriceDataTickRecordResponse::GetDateTime() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataTickRecordResponse::GetPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse, Price) + sizeof(Price))
			return 0;

		return Price;
	}
	/*==========================================================================*/
	double s_HistoricalPriceDataTickRecordResponse::GetVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}
	/*==========================================================================*/
	AtBidOrAskEnum s_HistoricalPriceDataTickRecordResponse::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET;

		return AtBidOrAsk;
	}
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataTickRecordResponse::GetIsFinalRecord() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse, IsFinalRecord) + sizeof(IsFinalRecord))
			return 0;

		return IsFinalRecord;
	}


	/****************************************************************************/
	// s_HistoricalPriceDataRecordResponse_Int

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataRecordResponse_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataRecordResponse_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataRecordResponse_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetOpenPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, OpenPrice) + sizeof(OpenPrice))
			return 0;

		return OpenPrice;
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetHighPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, HighPrice) + sizeof(HighPrice))
			return 0;

		return HighPrice;
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetLowPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, LowPrice) + sizeof(LowPrice))
			return 0;

		return LowPrice;
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetLastPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, LastPrice) + sizeof(LastPrice))
			return 0;

		return LastPrice;
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}
	/*==========================================================================*/
	uint32_t s_HistoricalPriceDataRecordResponse_Int::GetOpenInterest() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, OpenInterest) + sizeof(OpenInterest))
			return 0;

		return OpenInterest;
	}
	/*==========================================================================*/
	uint32_t s_HistoricalPriceDataRecordResponse_Int::GetNumTrades() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, NumTrades) + sizeof(NumTrades))
			return 0;

		return NumTrades;
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetBidVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, BidVolume) + sizeof(BidVolume))
			return 0;

		return BidVolume;
	}
	/*==========================================================================*/
	int32_t s_HistoricalPriceDataRecordResponse_Int::GetAskVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, AskVolume) + sizeof(AskVolume))
			return 0;

		return AskVolume;
	}
	/*==========================================================================*/
	t_DateTime s_HistoricalPriceDataRecordResponse_Int::GetStartDateTime() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}
	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataRecordResponse_Int::GetIsFinalRecord() const
	{
		if (Size < offsetof(s_HistoricalPriceDataRecordResponse_Int, IsFinalRecord) + sizeof(IsFinalRecord))
			return 0;

		return IsFinalRecord;
	}


	/****************************************************************************/
	// s_HistoricalPriceDataTickRecordResponse_Int

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataTickRecordResponse_Int::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataTickRecordResponse_Int::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataTickRecordResponse_Int), *static_cast<uint16_t*>( p_SourceData) ));
	}

	/*==========================================================================*/
	int32_t s_HistoricalPriceDataTickRecordResponse_Int::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse_Int, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	t_DateTimeWithMilliseconds s_HistoricalPriceDataTickRecordResponse_Int::GetDateTime() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse_Int, DateTime) + sizeof(DateTime))
			return 0;

		return DateTime;
	}

	/*==========================================================================*/
	int32_t s_HistoricalPriceDataTickRecordResponse_Int::GetPrice() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse_Int, Price) + sizeof(Price))
			return 0;

		return Price;
	}

	/*==========================================================================*/
	int32_t s_HistoricalPriceDataTickRecordResponse_Int::GetVolume() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse_Int, Volume) + sizeof(Volume))
			return 0;

		return Volume;
	}

	/*==========================================================================*/
	AtBidOrAskEnum s_HistoricalPriceDataTickRecordResponse_Int::GetAtBidOrAsk() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse_Int, AtBidOrAsk) + sizeof(AtBidOrAsk))
			return BID_ASK_UNSET;

		return AtBidOrAsk;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalPriceDataTickRecordResponse_Int::GetIsFinalRecord() const
	{
		if (Size < offsetof(s_HistoricalPriceDataTickRecordResponse_Int, IsFinalRecord) + sizeof(IsFinalRecord))
			return 0;

		return IsFinalRecord;
	}

	/****************************************************************************/
	// s_HistoricalPriceDataResponseTrailer

	/*==========================================================================*/
	uint16_t s_HistoricalPriceDataResponseTrailer::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalPriceDataResponseTrailer::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalPriceDataResponseTrailer), *static_cast<uint16_t*>( p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_HistoricalPriceDataResponseTrailer::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalPriceDataResponseTrailer, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_HistoricalPriceDataResponseTrailer::GetFinalRecordLastDateTime() const
	{
		if (Size < offsetof(s_HistoricalPriceDataResponseTrailer, FinalRecordLastDateTime) + sizeof(FinalRecordLastDateTime))
			return 0;

		return FinalRecordLastDateTime;
	}

	/****************************************************************************/
	// s_HistoricalMarketDepthDataRequest

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataRequest::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalMarketDepthDataRequest::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalMarketDepthDataRequest), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_HistoricalMarketDepthDataRequest::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRequest, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	void s_HistoricalMarketDepthDataRequest::SetSymbol(const char* NewValue)
	{
		strncpy(Symbol, NewValue, sizeof(Symbol) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalMarketDepthDataRequest::GetSymbol()
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRequest, Symbol) + sizeof(Symbol))
			return "";

		Symbol[sizeof(Symbol) - 1] = '\0';

		return Symbol;
	}

	/*==========================================================================*/
	void s_HistoricalMarketDepthDataRequest::SetExchange(const char* NewValue)
	{
		strncpy(Exchange, NewValue, sizeof(Exchange) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalMarketDepthDataRequest::GetExchange()
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRequest, Exchange) + sizeof(Exchange))
			return "";

		Exchange[sizeof(Exchange) - 1] = '\0';

		return Exchange;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_HistoricalMarketDepthDataRequest::GetStartDateTime() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRequest, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_HistoricalMarketDepthDataRequest::GetEndDateTime() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRequest, EndDateTime) + sizeof(EndDateTime))
			return 0;

		return EndDateTime;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataRequest::GetUseZLibCompression() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRequest, UseZLibCompression) + sizeof(UseZLibCompression))
			return 0;

		return UseZLibCompression;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataRequest::GetInteger_1() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRequest, Integer_1) + sizeof(Integer_1))
			return 0;

		return Integer_1;
	}

	/****************************************************************************/
	// s_HistoricalMarketDepthDataResponseHeader

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataResponseHeader::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalMarketDepthDataResponseHeader::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalMarketDepthDataResponseHeader), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_HistoricalMarketDepthDataResponseHeader::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataResponseHeader, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataResponseHeader::GetUseZLibCompression() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataResponseHeader, UseZLibCompression) + sizeof(UseZLibCompression))
			return 0;

		return UseZLibCompression;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataResponseHeader::GetNoRecordsToReturn() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataResponseHeader, NoRecordsToReturn) + sizeof(NoRecordsToReturn))
			return 0;

		return NoRecordsToReturn;
	}

	/****************************************************************************/
	// s_HistoricalMarketDepthDataReject

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataReject::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalMarketDepthDataReject::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalMarketDepthDataReject), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_HistoricalMarketDepthDataReject::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataReject, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	void s_HistoricalMarketDepthDataReject::SetRejectText(const char* NewValue)
	{
		strncpy(RejectText, NewValue, sizeof(RejectText) - 1);
	}

	/*==========================================================================*/
	const char* s_HistoricalMarketDepthDataReject::GetRejectText()
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataReject, RejectText) + sizeof(RejectText))
			return "";

		RejectText[sizeof(RejectText) - 1] = '\0';

		return RejectText;
	}

	/*==========================================================================*/
	HistoricalPriceDataRejectReasonCodeEnum s_HistoricalMarketDepthDataReject::GetRejectReasonCode() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataReject, RejectReasonCode) + sizeof(RejectReasonCode))
			return DTC::HPDR_UNSET;

		return RejectReasonCode;
	}

	/****************************************************************************/
	// s_HistoricalMarketDepthDataRecordResponse

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataRecordResponse::GetMessageSize() const
	{
		return Size;
	}

	/*==========================================================================*/
	void s_HistoricalMarketDepthDataRecordResponse::CopyFrom(void* p_SourceData)
	{
		memcpy(this, p_SourceData, min(sizeof(s_HistoricalMarketDepthDataRecordResponse), *static_cast<uint16_t*>(p_SourceData)));
	}

	/*==========================================================================*/
	int32_t s_HistoricalMarketDepthDataRecordResponse::GetRequestID() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, RequestID) + sizeof(RequestID))
			return 0;

		return RequestID;
	}

	/*==========================================================================*/
	t_DateTimeWithMicrosecondsInt s_HistoricalMarketDepthDataRecordResponse::GetStartDateTime() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, StartDateTime) + sizeof(StartDateTime))
			return 0;

		return StartDateTime;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataRecordResponse::GetCommand() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, Command) + sizeof(Command))
			return 0;

		return Command;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataRecordResponse::GetFlags() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, Flags) + sizeof(Flags))
			return 0;

		return Flags;
	}

	/*==========================================================================*/
	uint16_t s_HistoricalMarketDepthDataRecordResponse::GetNumOrders() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, NumOrders) + sizeof(NumOrders))
			return 0;

		return NumOrders;
	}

	/*==========================================================================*/
	float s_HistoricalMarketDepthDataRecordResponse::GetPrice() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, Price) + sizeof(Price))
			return 0.0;

		return Price;
	}

	/*==========================================================================*/
	uint32_t s_HistoricalMarketDepthDataRecordResponse::GetQuantity() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, Quantity) + sizeof(Quantity))
			return 0;

		return Quantity;
	}

	/*==========================================================================*/
	uint8_t s_HistoricalMarketDepthDataRecordResponse::GetIsFinalRecord() const
	{
		if (Size < offsetof(s_HistoricalMarketDepthDataRecordResponse, IsFinalRecord) + sizeof(IsFinalRecord))
			return 0;

		return IsFinalRecord;
	}

	/*==========================================================================*/
}