#include "Order.h"
#include <typeinfo>

char Order::separator = '$';
std::string Order::empty = "!";

Order::Order(unsigned int t, const std::string &i):
	table(t),
	item(i)
{

}

std::string Order::recap() const
{
	std::string det = getDetails();
	return getType() + separator + (det != "" ? det : empty) + separator + item + separator +
		   std::to_string(table);
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

char Order::getSeparator()
{
	return separator;
}

void Order::setSeparator(char value)
{
	separator = value;
}

std::string Order::getEmpty()
{
	return empty;
}

void Order::setEmpty(const std::string &value)
{
	empty = value;
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