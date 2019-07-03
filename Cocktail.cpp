#include "Cocktail.h"

const std::string Cocktail::class_name("Cocktail");
Order::Empty Cocktail::empty(class_name,
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

std::string Cocktail::getClassName() const
{
	return class_name;
}

bool Cocktail::isA(const std::string &type) const
{
	return type == Cocktail::getClassName() || Alcoholic::isA(type);
}

std::string Cocktail::getGarnish() const
{
	return garnish;
}

void Cocktail::setGarnish(const std::string &g)
{
	garnish = g;
}

std::vector<std::string> Cocktail::getDetails() const
{
	return {getGarnish()};
}

void Cocktail::setDetails(const std::vector<std::string> &det)
{
	setGarnish(det[0]);
}

bool Cocktail::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       garnish == static_cast<const Cocktail &>(o).garnish;
}
