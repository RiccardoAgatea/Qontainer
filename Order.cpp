#include "Order.h"
#include <typeinfo>

Order::Order(unsigned int t, const std::string &i):
	table(t),
	item(i)
{

}

std::string Order::recap() const
{
	std::string det = getDetails();
	return getType() + ' ' + (det != "" ? det : "!") + ' ' + item + ' ' + std::to_string(table);
}

bool Order::operator==(const Order &o) const
{
	return typeid(*this) == typeid(o) &&
		   table == o.table &&
		   item == o.item;
}

bool Order::operator!=(const Order &o) const
{
	return !(*this == o);
}
