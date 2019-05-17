#include "Food.h"

Food::Food(unsigned int t,
           const std::string &i,
           const std::string &w):
	Order(t, i),
	without(w)
{

}

std::string Food::getRemovedParts() const
{
	return without;
}

std::vector<std::string> Food::getDetails() const
{
	return {getRemovedParts()};
}

bool Food::operator==(const Order &o) const
{
	return Order::operator==(o) &&
	       without == static_cast<const Food &>(o).without;
}
