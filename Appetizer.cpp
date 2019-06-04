#include "Appetizer.h"
#include <utility>

const std::string Appetizer::type("Appetizer");
Order::Empty Appetizer::empty(type,
{{DetailType::SmallText, "Sauces"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Appetizer(t, i, q, d[0]));
});

Appetizer::Appetizer(unsigned int t,
					 const std::string &i,
					 unsigned int q,
					 const std::string &s):
	Food(t, i, q, ""),
	sauces(s)
{

}

Appetizer *Appetizer::clone() const
{
	return new Appetizer(*this);
}

Appetizer *Appetizer::move()
{
	return new Appetizer(std::move(*this));
}

std::string Appetizer::getType() const
{
	return type;
}

std::string Appetizer::getSauces() const
{
	return sauces;
}

std::vector<std::string> Appetizer::getDetails() const
{
	return {getSauces()};
}

bool Appetizer::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       sauces == static_cast<const Appetizer &>(o).sauces;
}
