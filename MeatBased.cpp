#include "MeatBased.h"

const std::string MeatBased::class_name("MeatBased");
Order::Empty MeatBased::empty(class_name);

MeatBased::MeatBased(unsigned int t,
					 const std::string &i,
					 unsigned int q,
					 const std::string &w,
					 const std::string &temp):
	Food(t, i, q, w),
	temperature(temp)
{

}

std::string MeatBased::getTemperature() const
{
	return temperature;
}

void MeatBased::setTemperature(const std::string &temp)
{
	temperature = temp;
}

std::string MeatBased::getClassName() const
{
	return class_name;
}

bool MeatBased::isA(const std::string &type) const
{
	return type == MeatBased::getClassName() || Food::isA(type);
}

std::vector<std::string> MeatBased::getDetails() const
{
	std::vector<std::string> aux = Food::getDetails();
	aux.push_back(getTemperature());

	return aux;
}

void MeatBased::setDetails(const std::vector<std::string> &det)
{
	Food::setDetails(det);
	unsigned int skip = Food::getDetails().size();

	setTemperature(det[skip]);
}

bool MeatBased::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       temperature == static_cast<const MeatBased &>(o).temperature;
}
