#ifndef DRINK_H
#define DRINK_H
#include "Order.h"

class Drink: public Order
{
private:
	static const std::string class_name;
	static Order::Empty empty;
public:
	using Order::Order;
	Drink *clone() const override = 0;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
};

#endif // DRINK_H