#include "Order.h"
#include <typeinfo>

Order::Order(unsigned int t,
			 const std::string &i):
	table(t),
	item(i)
{

}

std::string Order::recap() const
{
	return getType() + separator + std::to_string(table) + separator +
		   item
		   + separator + getDetails();
}

bool Order::operator==(const Order &o) const
{
	return getType() == o.getType() &&
		   table == o.table &&
		   item == o.item;
}

bool Order::operator!=(const Order &o) const
{
	return !(*this == o);
}

namespace PolyConstruct
{
template<>
Order *clone(const Order &t)
{
	return t.clone();
}

template<>
Order *clone(Order &&t)
{
	return t.move();
}
}