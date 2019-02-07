#include "Appetizer.h"
#include <utility>

std::string Appetizer::getType() const
{
	return "Appetizer";
}

Appetizer::Appetizer(unsigned int t, const std::string &i, const std::string &s):
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

std::string Appetizer::getDetails() const
{
	return Food::getDetails() + getSeparator() + sauces;
}

void Appetizer::setDetails(const std::string &detail)
{
	sauces = detail;
}

bool Appetizer::operator==(const Order &o) const
{
	return Food::operator==(o) &&
		   sauces == static_cast<const Appetizer &>(o).sauces;
}
