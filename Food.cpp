#include "Food.h"

Food::Food(unsigned int t,
		   const std::string &i,
		   const std::string &w):
	Order(t, i),
	without(w)
{

}

DeepPtr<Order::Details> Food::getDetails() const
{
	return DeepPtr<Order::Details>(Details(*this));
}

bool Food::operator==(const Order &o) const
{
	return Order::operator==(o) &&
		   without == static_cast<const Food &>(o).without;
}

Food::Details::Details(const Food &f):
	without(f.without)
{

}
