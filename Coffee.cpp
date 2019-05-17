#include "Coffee.h"
#include <utility>

Coffee::Coffee(unsigned int t,
               const std::string &i,
               const std::string &n):
	Drink(t, i),
	notes(n)
{

}

Coffee *Coffee::clone() const
{
	return new Coffee(*this);
}

Coffee *Coffee::move()
{
	return new Coffee(std::move(*this));
}

std::string Coffee::getType() const
{
	return "Coffee";
}

std::string Coffee::getNotes() const
{
	return notes;
}

std::vector<std::string> Coffee::getDetails() const
{
	return {getNotes()};
}

bool Coffee::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       notes == static_cast<const Coffee &>(o).notes;
}
