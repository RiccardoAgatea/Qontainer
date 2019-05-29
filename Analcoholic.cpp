#include "Analcoholic.h"
#include <utility>
#include <stdexcept>

StaticOrder::Empty Analcoholic::empty("Analcoholic");

Analcoholic::Analcoholic(unsigned int t,
                         const std::string &i,
                         bool ic):
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

std::string Analcoholic::getType() const
{
	return "Analcoholic";
}

bool Analcoholic::isIced() const
{
	return ice;
}

std::vector<std::string> Analcoholic::getDetails() const
{
	return {isIced() ? "1" : "0"};
}

bool Analcoholic::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       ice == static_cast<const Analcoholic &>(o).ice;
}
