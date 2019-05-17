#ifndef DRINK_H
#define DRINK_H
#include "Order.h"

class Drink: public Order
{
public:
	using Order::Order;
};

#endif // DRINK_H