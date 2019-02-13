#include "Appetizer.h"
#include <utility>

Appetizer::Appetizer(unsigned int t,
					 const std::string &i,
					 const std::string &s):
	Food(t, i, ""),
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
	return "Appetizer";
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
