#include "MeatBased.h"

MeatBased::MeatBased(unsigned int t, const std::string &i, const std::string &w,
					 const std::string &temp):
	Food(t, i, w),
	temperature(temp)
{

}

std::string MeatBased::getDetails() const
{
	return Food::getDetails() + separator + temperature;
}

void MeatBased::setDetails(const std::string &detail)
{
	if (detail[0] == '-')
		temperature = detail.substr(1);
	else
		Food::setDetails(detail.substr(1));
}

bool MeatBased::operator==(const Order &o) const
{
	return Food::operator==(o) &&
		   temperature == static_cast<const MeatBased &>(o).temperature;
}
