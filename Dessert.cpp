#include "Dessert.h"
#include <utility>

std::string Dessert::getType() const
{
	return "dessert";
}

Dessert::Dessert(unsigned int t, const std::string &i, const std::string &w):
	Food(t, i, ""),
	with(w)
{

}

Dessert *Dessert::clone() const
{
	return new Dessert(*this);
}

Dessert *Dessert::move()
{
	return new Dessert(std::move(*this));
}

std::string Dessert::getDetails() const
{
	return with;
}

void Dessert::setDetails(const std::string &detail)
{
	with = detail;
}

bool Dessert::operator==(const Order &o) const
{
	return Food::operator==(o) &&
		   with == static_cast<const Dessert &>(o).with;
}
