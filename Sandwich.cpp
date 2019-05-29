#include "Sandwich.h"
#include <utility>

StaticOrder::Empty Sandwich::empty("Sandwich");

Sandwich *Sandwich::clone() const
{
	return new Sandwich(*this);
}

Sandwich *Sandwich::move()
{
	return new Sandwich(std::move(*this));
}

std::string Sandwich::getType() const
{
	return "Sandwich";
}