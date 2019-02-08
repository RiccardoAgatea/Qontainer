#include "Coffee.h"
#include <utility>


std::string Coffee::getType() const
{
	return "Coffee";
}

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

std::string Coffee::getDetails() const
{
	return notes;
}

void Coffee::setDetails(const std::string &detail)
{
	notes = detail;
}

bool Coffee::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
		   notes == static_cast<const Coffee &>(o).notes;
}
