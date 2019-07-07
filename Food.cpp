#include "Food.h"

const std::string Food::class_name("Food");
Order::Empty Food::empty(class_name);

Food::Food(unsigned int t,
           const std::string &i,
           unsigned int q,
           const std::string &w):
	Order(t, i, q),
	without(w)
{

}

std::string Food::getWithout() const
{
	return without;
}

void Food::setWithout(const std::string &w)
{
	without = w;
}

std::string Food::getClassName() const
{
	return class_name;
}

bool Food::isA(const std::string &type) const
{
	return type == Food::getClassName() || Order::isA(type);
}

std::vector<std::string> Food::getDetails() const
{
	return {getWithout()};
}

void Food::setDetails(const std::vector<std::string> &det)
{
	setWithout(det[0]);
}

bool Food::operator==(const Order &o) const
{
	return Order::operator==(o) &&
	       without == static_cast<const Food &>(o).without;
}
