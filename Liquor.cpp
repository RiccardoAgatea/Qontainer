#include "Liquor.h"
#include <utility>
#include <stdexcept>

std::string Liquor::getType() const
{
	return "Liquor";
}

Liquor::Liquor(unsigned int t,
			   const std::string &i,
			   bool ic):
	Alcoholic(t, i),
	ice(ic)
{

}

Liquor *Liquor::clone() const
{
	return new Liquor(*this);
}

Liquor *Liquor::move()
{
	return new Liquor(std::move(*this));
}

std::string Liquor::getDetails() const
{
	return ice ? "1" : "0";
}

void Liquor::setDetails(const std::string &detail)
{
	if (detail != "0" && detail != "1")
		throw std::invalid_argument("Liquor::setDetails() called with argument not in {0,1}");

	ice = detail == "1";
}

bool Liquor::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
		   ice == static_cast<const Liquor &>(o).ice;
}
