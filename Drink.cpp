#include "Drink.h"

Drink::Drink(unsigned int t, const std::string &i, const std::string &n):
	Order(t, i),
	notes(n)
{

}

std::string Drink::getDetails() const
{
	return notes;
}

void Drink::setDetails(const std::string &detail)
{
	notes = detail;
}

bool Drink::operator==(const Order &o) const
{
	return Order::operator==(o) &&
		   notes == static_cast<const Drink &>(o).notes;
}