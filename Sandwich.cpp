#include "Sandwich.h"
#include <utility>

const std::string Sandwich::type("Sandwich");
Order::Empty Sandwich::empty(type,
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

Sandwich *Sandwich::move()
{
	return new Sandwich(std::move(*this));
}

std::string Sandwich::getType() const
{
	return type;
}