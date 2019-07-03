#include "Sandwich.h"
#include <utility>

const std::string Sandwich::class_name("Sandwich");
Order::Empty Sandwich::empty(class_name,
{{DetailType::LargeText, "Not Including"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Sandwich(t, i, q, d[0]));
});

Sandwich *Sandwich::clone() const
{
	return new Sandwich(*this);
}

std::string Sandwich::getClassName() const
{
	return class_name;
}

bool Sandwich::isA(const std::string &type) const
{
	return type == Sandwich::getClassName() || Food::isA(type);
}