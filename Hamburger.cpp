#include "Hamburger.h"
#include <utility>

const std::string Hamburger::type("Hamburger");
Order::Empty Hamburger::empty(type,
{{DetailType::LargeText, "Not Including"}, {DetailType::SmallText, "Temperature"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Hamburger(t, i, q, d[0], d[1]));
});

Hamburger *Hamburger::clone() const
{
	return new Hamburger(*this);
}

std::string Hamburger::getType() const
{
	return type;
}