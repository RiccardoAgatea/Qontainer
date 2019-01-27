#include "Sandwich.h"
#include <utility>

std::string Sandwich::getType() const
{
	return "sandwich";
}

Sandwich *Sandwich::clone() const
{
	return new Sandwich(*this);
}

Sandwich *Sandwich::move()
{
	return new Sandwich(std::move(*this));
}

