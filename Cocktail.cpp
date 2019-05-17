#include "Cocktail.h"

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

std::string Cocktail::getType() const
{
	return "Cocktail";
}

std::string Cocktail::getGarnish() const
{
	return garnish;
}

std::vector<std::string> Cocktail::getDetails() const
{
	return {getGarnish()};
}

bool Cocktail::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       garnish == static_cast<const Cocktail &>(o).garnish;
}
