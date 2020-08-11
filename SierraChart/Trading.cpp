#include "Engine.h"

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.



// https://stackoverflow.com/questions/3247861/example-of-uuid-generation-using-boost-in-c
std::string generate_uuid()
{
	// note: we re-use the same generator object for better performance.
	static boost::uuids::random_generator generator;
	static std::mutex mutex;
	static bool initialized = false;

	std::ostringstream oss;
	{
		std::lock_guard<std::mutex> lock(mutex); // generator() is not thread safe.
		oss << generator();
	}

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[12];
	memset(buf, 0, 12);
	gmtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d-", &tstruct);

	return ((std::string)buf) + oss.str().substr(0, 8);

	// output format: "YYYY-MM-DD-XXXXXXXX", where the date is in UTC, 
	//				  and the XXXXXXXX is the first eight digits of a random UUID.
	// This is to make UUID's easy to identify.  We do not need the full complexity of the original UUID.
}




namespace asio = boost::asio;
namespace cro = std::chrono;
using boost::system::error_code;
using asio::ip::tcp;
#undef max

using namespace DTC;
using namespace DTCTools;

int client::zt_BrokerBuy2(char* ZorroAsset, int Amount, double StopDist, double Limit, double *pPrice, int *pFill)
{
	if (!Amount) return 0;
	s_SecurityDefinitionResponse* def = can_define(ZorroAsset);
	if (!def) return 0;
	per_trade_account& pta = m_pta.find(tradeaccount_selected)->second;

	double AmountDivisor = 1;
	if (can_calc_LotAmount(def, AmountDivisor))
	{
		if (AmountDivisor >= 1)
			AmountDivisor = 1;
	}

	bool to_open = true;
	if (StopDist == -1) to_open = false;
	
	// For close orders, we need to return 0 until the position matches the target position.
	if (!to_open)
	{
		// check if we have any unsatisfied close orders that match the intended order. (Asset and lot size)
		// if found, check if they are now satisfied.
		//			If satisfied, log satisfaction, output fill info and return 1.
		//			If unsatisfied, return 0.
		//			If the order has partially filled and expired, need to indicate this and return 1.
		//			If the order expired and did not fill at all, need to clear this and send another.
		// if not found, we need to place an order, and then we will log the unsatisfied condition.

		// we do all this from the backend - once.
		
		int return_value = 0;
		bool need_new_order = true; // true until proven otherwise
		int ignored = maybe_post_return([&]()->int {
			auto it = pta.unsatisfied_closures.begin();
			for (; it != pta.unsatisfied_closures.end(); it++)
			{
				// is this a mismatch? if so, skip.
				if (
					((std::string)def->GetSymbol() != it->DTCSymbol) ||
					(Amount != it->ZorroAmount)
					)
				{
					continue;
				}
				
				// is match
				need_new_order = false; 
				bool closure_satisfied = false;
				// scan open orders for matching client id, then get status
				s_OrderUpdate* update = NULL;
				for (auto& order : pta.orders_open)
				{
					if ((std::string)order.GetServerOrderID() != it->ServerID)
						continue; // mismatch

					// is match
					update = &order;
					break;
				}
				if (!update) std::runtime_error("Order update missing!!");
					
				switch (update->GetOrderStatus())
				{
				case ORDER_STATUS_UNSPECIFIED:
				case ORDER_STATUS_ORDER_SENT:
				case ORDER_STATUS_PENDING_OPEN:
				case ORDER_STATUS_PENDING_CHILD:
				case ORDER_STATUS_OPEN:
				case ORDER_STATUS_PENDING_CANCEL_REPLACE:
				case ORDER_STATUS_PENDING_CANCEL:
				case ORDER_STATUS_PARTIALLY_FILLED: // still working/active order
					closure_satisfied = false;
					return_value = 0;
					break;
				case ORDER_STATUS_FILLED: // filled, either full or partial, inactive
					if (pFill) *pFill = (int)(update->GetFilledQuantity() * AmountDivisor);
					if (pPrice) *pPrice = update->GetAverageFillPrice();
					closure_satisfied = true;
					if(*pFill) return_value = 1;
					else return_value = 0;
					break;
				case ORDER_STATUS_CANCELED:
				case ORDER_STATUS_REJECTED:
					closure_satisfied = true;
					return_value = 0;
					break;
				default:
					std::runtime_error("Unknown order status encountered!");
				}

				if (closure_satisfied)
				{
					pta.unsatisfied_closures.erase(it);
				}
				
				// we are done
				return 0; //ignored
			}
			return 0; //ignored
		});

		if (!need_new_order) 
			return return_value;
	}

	// if we reached this point, we need to place the order
	s_SubmitNewSingleOrder order;
	order.SetSymbol(def->GetSymbol());
	order.SetExchange(def->GetExchange());
	order.SetTradeAccount(tradeaccount_selected.c_str());
	order.SetClientOrderID(generate_uuid().c_str());
	switch (ordertype)
	{
	case ORDERTYPE_IMMEDIATEORCANCEL:
		order.TimeInForce = TIF_IMMEDIATE_OR_CANCEL;
		break;
	case ORDERTYPE_GOODTILLCANCELED:
		order.TimeInForce = TIF_GOOD_TILL_CANCELED;
		break;
	case ORDERTYPE_FILLORKILL:
	default:
		order.TimeInForce = TIF_FILL_OR_KILL;
		break;
	}
	if (!Limit) order.OrderType = ORDER_TYPE_MARKET;
	else
	{
		order.OrderType = ORDER_TYPE_LIMIT;
		order.Price1 = Limit; // TODO: confirm meaning of SET_LIMIT value
	}
	order.Quantity = std::abs(Amount)/AmountDivisor;
	if (Amount > 0)
		order.BuySell = BUY;
	else if (Amount < 0)
		order.BuySell = SELL;
	else
		order.BuySell = BUY_SELL_UNSET;
	order.IsAutomatedOrder = 1;
	if (to_open)
		order.OpenOrClose = TRADE_OPEN;
	else
		order.OpenOrClose = TRADE_CLOSE;

	b.expect(sol_OrderUpdate_ClientOrderID,(std::string)order.GetClientOrderID());
	// send the order
	write_async(order);

	// block for response to order
	if(!b.block_is_good())
	{
		err("Order failure.");
		return 0;
	}

	// Check the result.  If good, we want to output the ServerID ("UUID")
	return maybe_post_return([&]()->int {
		// locate order
		s_OrderUpdate* update = NULL;
		for (auto& oa : pta.orders_open)
		{
			if ((std::string)oa.GetClientOrderID() == (std::string)order.GetClientOrderID())
			{
				update = &oa;
				break;
			}
		}
		if(!update) return 0;
		if (update->GetNoOrders())
		{
			err("Server: No orders!");
		}
		switch (update->GetOrderStatus())
		{
		case ORDER_STATUS_UNSPECIFIED:
		case ORDER_STATUS_ORDER_SENT:
		case ORDER_STATUS_PENDING_OPEN:
		case ORDER_STATUS_PENDING_CHILD:
		case ORDER_STATUS_OPEN:
		case ORDER_STATUS_PENDING_CANCEL_REPLACE:
		case ORDER_STATUS_PENDING_CANCEL:
		case ORDER_STATUS_PARTIALLY_FILLED: // still working/active order
			//nothing to do
			break;
		case ORDER_STATUS_FILLED: // filled, either full or partial, inactive
			if (pFill) *pFill = (int)(update->GetFilledQuantity() * AmountDivisor);
			if (pPrice) *pPrice = update->GetAverageFillPrice();
			if (!(*pFill)) return 0;
			break;
		case ORDER_STATUS_CANCELED:
		case ORDER_STATUS_REJECTED:
			return 0;
		default:
			std::runtime_error("Unknown order status encountered!");
		}

		uuid = update->GetServerOrderID();
		if (uuid.size()) return -1;
		else {
			err("ServerID not supplied!");
			return 0;
		}

	});


}

int client::zt_BrokerTrade(int nTradeID, double *pOpen, double *pClose, double *pRoll, double *pProfit)
{
	if (nTradeID != -1) return 0; //UUID only
	per_trade_account& pta = m_pta.find(tradeaccount_selected)->second;

	// Check the result.  If good, we want to output the ServerID ("UUID")
	return maybe_post_return([&]()->int {
		
		// locate order
		s_OrderUpdate* update = NULL;
		for (auto& oa : pta.orders_open)
		{
			if ((std::string)oa.GetServerOrderID() == uuid)
			{
				update = &oa;
				break;
			}
		}
		if (!update) return 0;

		// locate definition
		s_SecurityDefinitionResponse* def = NULL;
		for (auto& d : security_definitions)
		{
			if ((std::string)d.GetSymbol() == (std::string)update->GetSymbol()) 
			{
				def = &d;
				break;
			}
		}
		if (!def) return 0;

		double AmountDivisor = 1;
		if (can_calc_LotAmount(def, AmountDivisor))
		{
			if (AmountDivisor >= 1)
				AmountDivisor = 1;
		}
		switch (update->GetOrderStatus())
		{
		case ORDER_STATUS_UNSPECIFIED:
		case ORDER_STATUS_ORDER_SENT:
		case ORDER_STATUS_PENDING_OPEN:
		case ORDER_STATUS_PENDING_CHILD:
		case ORDER_STATUS_OPEN:
		case ORDER_STATUS_PENDING_CANCEL_REPLACE:
		case ORDER_STATUS_PENDING_CANCEL:
		case ORDER_STATUS_PARTIALLY_FILLED: // still working/active order
			//nothing to do
			return 0;
		case ORDER_STATUS_FILLED: // filled, either full or partial, inactive
			if (pOpen) *pOpen = update->GetAverageFillPrice();
			return (int)(update->GetFilledQuantity() * AmountDivisor);
		case ORDER_STATUS_CANCELED:
		case ORDER_STATUS_REJECTED:
			return 0;
		default:
			std::runtime_error("Unknown order status encountered!");
			return 0;
		}


	});

}
