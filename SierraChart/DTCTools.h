#pragma once

typedef double DATE;

// DTCProtocol.h prerequisites
#include <float.h>
#include <limits.h>
#include <string> // <string.h>
#include <memory.h> 
#include <stddef.h>
#include "DTCProtocol.h"
#define MT_STATUS_UNSUPPORTED 0
#define MT_STATUS_SUPPORTED 1

#include <vector>
typedef std::vector<char> v_char;
typedef std::vector<std::string> v_string;
typedef std::vector<uint16_t> v_uint16_t;


namespace DTCTools
{
	struct s_Header
	{
		uint16_t Size;
		uint16_t Type;

s_Header()
{
	Size = 0;
	Type = 0;
}

	};

	struct s_MsgTypeIndex
	{
		uint16_t Size;
		int Status; // 0: Not supported. 1 = supported
		std::string Name;
	};
	struct s_RequestIDEntry
	{
		uint16_t Type;
		int32_t LastRequestID;
		s_RequestIDEntry()
		{
			Type = 0;
			LastRequestID = 1;
		}
	};
	class RequestIDList
	{
	public:
		//int32_t get_request_id(uint16_t Type);

		template <typename T>
		int32_t get_request_id(T s_msg)
		{
			for (auto& entry : v_requestIDEntries_)
			{
				if (entry.Type == s_msg.Type)
				{
					return ++entry.LastRequestID;
				}
			}

			// no matches, add entry
			s_RequestIDEntry new_entry;
			new_entry.Type = s_msg.Type;
			v_requestIDEntries_.push_back(new_entry);
			return new_entry.LastRequestID;
		}

	private:
		std::vector<s_RequestIDEntry> v_requestIDEntries_;
	};

	struct s_SymbolIDEntry
	{
		uint32_t SymbolID;
		std::string Symbol;
		std::string Exchange;
		s_SymbolIDEntry()
		{
			SymbolID = 0;
			Symbol = "";
			Exchange = "";
		}
	};
	class SymbolIDList
	{
	public:
		//uint32_t get_symbolID(std::string Symbol);
		//uint32_t get_symbolID(std::string Symbol, std::string Exchange);
		uint32_t get_symbolID(DTC::s_SecurityDefinitionResponse* def);
	private:
		std::vector<s_SymbolIDEntry> v_symbolIDEntries_;
	};

	s_Header stringToHeader(std::string sbuffer);
	uint16_t stringToMsgType(std::string sbuffer);
	s_MsgTypeIndex GetTypeIndex(const uint16_t messageType);
	uint16_t GetMaxSize();
	uint16_t GetMinSize();
	std::string charVectorsToString(const std::vector<char>& cv1, const std::vector<char>& cv2);
	std::string GetTypeName(const uint16_t messageType);

	uint16_t getMsgSizeFromBuffer(std::vector<char> cbuffer);

	DATE convertTime(DTC::t_DateTime4Byte epoch_time);
	DATE convertTime(DTC::t_DateTime epoch_time);
	DATE convertTime(DTC::t_DateTimeWithMilliseconds epoch_time);
	DTC::t_DateTime4Byte convertDate_1day(DATE date_input);
	DTC::t_DateTime4Byte convertDate_1sec32bit(DATE date_input);
	DTC::t_DateTime convertDate_1sec64bit(DATE date_input);
	DTC::t_DateTimeWithMilliseconds convertDate_1ms(DATE date_input);


	template<typename T> std::string structToString(T s_input)
	{
		return(std::string((char*)&s_input, sizeof(s_input)));
	}

	template<typename T> uint16_t structToMsgType(T s_input)
	{
		s_Header *h = (s_Header*)&s_input;
		return(h->Type);
	}

	template<typename T> bool stringToStruct(T& struct_output, std::string str_input)
	{
		try {
			// check for wrong type, and if so return false
			T s_sample;
			s_Header *h_sample = (s_Header*)&s_sample;
			s_Header *h_actual = (s_Header*)str_input.data();
			if (h_sample->Type != h_actual->Type) return false;

			memcpy_s((char*)&struct_output, sizeof(struct_output), str_input.data(), str_input.size());
			return true;

			//if (sizeof(T) == str_input.size())
			//{
			//	memcpy_s((char*)&struct_output, sizeof(struct_output), str_input.data(), str_input.size());
			//	return true;
			//}
			//else // wrong size
			//{
			//	std::vector<char> v_input;
			//	v_input.resize(str_input.size());
			//	memcpy_s(v_input.data(), v_input.size(), str_input.data(), str_input.size());
			//	v_input.resize(sizeof(T), 0);
			//	memcpy_s((char*)&struct_output, sizeof(struct_output), v_input.data(), v_input.size());
			//	return true;
			//}
		}
		catch (...)
		{
			return false;
		}
	}
	void resize_msg_string(std::string& msg);

}

namespace DTCTypes
{
	extern const v_uint16_t t_logon;
	extern const v_uint16_t t_market_data;
	extern const v_uint16_t t_open_orders;
	extern const v_uint16_t t_historical_orders;
	extern const v_uint16_t t_positions;
	extern const v_uint16_t t_trade_accounts;
	extern const v_uint16_t t_exchange_list;
	extern const v_uint16_t t_security_definition;
	extern const v_uint16_t t_account_balance;
	extern const v_uint16_t t_info;
	extern const v_uint16_t t_historical_price_data_header;
	extern const v_uint16_t t_historical_price_data;
}