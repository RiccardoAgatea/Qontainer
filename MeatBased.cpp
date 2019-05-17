#include "MeatBased.h"

MeatBased::MeatBased(unsigned int t,
                     const std::string &i,
                     const std::string &w,
                     const std::string &temp):
	Food(t, i, w),
	temperature(temp)
{

}

std::string MeatBased::getTemperature() const
{
	return temperature;
}

std::vector<std::string> MeatBased::getDetails() const
{
	std::vector<std::string> aux = Food::getDetails();
	aux.push_back(getTemperature());

	return aux;
}

bool MeatBased::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       temperature == static_cast<const MeatBased &>(o).temperature;
}
