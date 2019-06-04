#include "Cocktail.h"

const std::string Cocktail::type("Cocktail");
Order::Empty Cocktail::empty(type,
{{DetailType::LargeText, "Garnish"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Cocktail(t, i, q, d[0]));
});

Cocktail::Cocktail(unsigned int t,
                   const std::string &i,
				   unsigned int q,
                   const std::string &g):
	Alcoholic(t, i, q),
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
	return type;
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
