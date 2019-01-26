#include "Appetizer.h"

std::string Appetizer::getType() const
{
	return "appetizer";
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

std::string Appetizer::getDetails() const
{
	return (sauces != "" ? sauces : empty) + separator + Food::getDetails();
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
