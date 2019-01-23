#include "Order.h"
#include <typeinfo>

Order::Order(unsigned int t, const std::string &f):
	table(t),
	food(f)
{

}

std::string Order::recap() const
{
	return std::to_string(table) + food;
}

bool Order::operator==(const Order &o) const
{
	return typeid(*this) == typeid(o) &&
		   table == o.table &&
		   food == o.food;
}

bool Order::operator!=(const Order &o) const
{
	return !(*this == o);
}
