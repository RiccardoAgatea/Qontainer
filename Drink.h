#ifndef DRINK_H
#define DRINK_H
#include "Order.h"

/**
 * @brief      Represents an order of some drink (as opposed to foods).
 */
class Drink: public Order
{
public:
	using Order::Order;
};

#endif // DRINK_H