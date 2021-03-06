#include "Appetizer.h"
#include <utility>

const std::string Appetizer::class_name("Appetizer");
Order::Empty Appetizer::empty(class_name,
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

std::string Appetizer::getClassName() const
{
	return class_name;
}

bool Appetizer::isA(const std::string &type) const
{
	return type == Appetizer::getClassName() || Food::isA(type);
}

std::string Appetizer::getSauces() const
{
	return sauces;
}

void Appetizer::setSauces(const std::string &s)
{
	sauces = s;
}

std::vector<std::string> Appetizer::getDetails() const
{
	return {getSauces()};
}

void Appetizer::setDetails(const std::vector<std::string> &det)
{
	setSauces(det[0]);
}

bool Appetizer::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       sauces == static_cast<const Appetizer &>(o).sauces;
}
