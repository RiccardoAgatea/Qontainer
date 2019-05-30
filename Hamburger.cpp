#include "Hamburger.h"
#include <utility>

const std::string Hamburger::type("Hamburger");
Order::Empty Hamburger::empty(type,
{{DetailType::LargeText, "Not Including"}, {DetailType::SmallText, "Temperature"}}, []
(unsigned int t,
 const std::string &i,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Hamburger(t, i, d[0], d[1]));
});

Hamburger *Hamburger::clone() const
{
	return new Hamburger(*this);
}

Hamburger *Hamburger::move()
{
	return new Hamburger(std::move(*this));
}

std::string Hamburger::getType() const
{
	return type;
}