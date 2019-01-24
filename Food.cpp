#include "Food.h"

Food::Food(unsigned int t, const std::string &i, const std::string &w):
	Order(t, i),
	without(w)
{

}

std::string Food::getDetails() const
{
	return without;
}

void Food::setDetails(const std::string &detail)
{
	without = detail;
}

bool Food::operator==(const Order &o) const
{
	return Order::operator==(o) &&
		   without == static_cast<const Food &>(o).without;
}
