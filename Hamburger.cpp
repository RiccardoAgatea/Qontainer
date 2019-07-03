#include "Hamburger.h"
#include <utility>

const std::string Hamburger::class_name("Hamburger");
Order::Empty Hamburger::empty(class_name,
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

std::string Hamburger::getClassName() const
{
	return class_name;
}

bool Hamburger::isA(const std::string &type) const
{
	return type == Hamburger::getClassName() || MeatBased::isA(type);
}