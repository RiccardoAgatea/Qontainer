#include "MeatBased.h"

MeatBased::MeatBased(unsigned int t,
					 const std::string &i,
					 const std::string &w,
					 const std::string &temp):
	Food(t, i, w),
	temperature(temp)
{

}

DeepPtr<Order::Details> MeatBased::getDetails() const
{
	return DeepPtr<Order::Details>(Details(*this));
}

bool MeatBased::operator==(const Order &o) const
{
	return Food::operator==(o) &&
		   temperature == static_cast<const MeatBased &>(o).temperature;
}

MeatBased::Details::Details(const MeatBased &mb):
	Food::Details(mb),
	temperature(mb.temperature)
{

}
