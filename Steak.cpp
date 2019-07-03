#include "Steak.h"
#include <utility>

const std::string Steak::class_name("Steak");
Order::Empty Steak::empty(class_name,
{{Order::DetailType::SmallText, "Temperature"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Steak(t, i, q, d[0]));
});

Steak::Steak(unsigned int t,
             const std::string &i,
             unsigned int q,
             const std::string &temp):
	MeatBased(t, i, q, "", temp)
{

}

Steak *Steak::clone() const
{
	return new Steak(*this);
}

std::string Steak::getClassName() const
{
	return class_name;
}

bool Steak::isA(const std::string &type) const
{
	return type == Steak::getClassName() || MeatBased::isA(type);
}

std::vector<std::string> Steak::getDetails() const
{
	return {getTemperature()};
}

void Steak::setDetails(const std::vector<std::string> &det)
{
	setTemperature(det[0]);
}