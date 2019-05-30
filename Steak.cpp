#include "Steak.h"
#include <utility>

const std::string Steak::type("Steak");
Order::Empty Steak::empty(type,
{{Order::DetailType::SmallText, "Temperature"}}, []
(unsigned int t,
 const std::string &i,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Steak(t, i, d[0]));
});

Steak::Steak(unsigned int t,
             const std::string &i,
             const std::string &temp):
	MeatBased(t, i, "", temp)
{

}

Steak *Steak::clone() const
{
	return new Steak(*this);
}

Steak *Steak::move()
{
	return new Steak(std::move(*this));
}

std::string Steak::getType() const
{
	return type;
}

std::vector<std::string> Steak::getDetails() const
{
	return {getTemperature()};
}