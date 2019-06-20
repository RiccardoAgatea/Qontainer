#ifndef DRINK_H
#define DRINK_H
#include "Order.h"

class Drink: public Order
{
public:
	using Order::Order;
	Drink *clone() const override = 0;
};

#endif // DRINK_H