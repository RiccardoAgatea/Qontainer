#include "Cocktail.h"

std::string Cocktail::getType() const
{
	return "Cocktail";
}

Cocktail::Cocktail(unsigned int t,
				   const std::string &i,
				   const std::string &g):
	Alcoholic(t, i),
	garnish(g)
{

}

Cocktail *Cocktail::clone() const
{
	return new Cocktail(*this);
}

Cocktail *Cocktail::move()
{
	return new Cocktail(std::move(*this));
}

std::string Cocktail::getDetails() const
{
	return garnish;
}

void Cocktail::setDetails(const std::string &detail)
{
	garnish = detail;
}

bool Cocktail::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
		   garnish == static_cast<const Cocktail &>(o).garnish;
}
