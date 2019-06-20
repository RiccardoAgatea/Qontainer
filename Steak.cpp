#include "Steak.h"
#include <utility>

const std::string Steak::type("Steak");
Order::Empty Steak::empty(type,
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

std::string Steak::getType() const
{
	return type;
}

std::vector<std::string> Steak::getDetails() const
{
	return {getTemperature()};
}