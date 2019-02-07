#include "Analcoholic.h"
#include <utility>
#include <stdexcept>

std::string Analcoholic::getType() const
{
	return "Analcoholic";
}

Analcoholic::Analcoholic(unsigned int t, const std::string &i, bool ic):
	Drink(t, i),
	ice(ic)
{

}

Analcoholic *Analcoholic::clone() const
{
	return new Analcoholic(*this);
}

Analcoholic *Analcoholic::move()
{
	return new Analcoholic(std::move(*this));
}

std::string Analcoholic::getDetails() const
{
	return ice ? "1" : "0";
}

void Analcoholic::setDetails(const std::string &detail)
{
	if (detail != "0" && detail != "1")
		throw std::invalid_argument("Analcoholic::setDetails() called with argument not in {0,1}");

	ice = detail == "1";
}

bool Analcoholic::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
		   ice == static_cast<const Analcoholic &>(o).ice;
}
