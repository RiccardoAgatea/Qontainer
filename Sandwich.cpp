#include "Sandwich.h"

std::string Sandwich::getType() const
{
	return "sandwich";
}

Sandwich *Sandwich::clone() const
{
	return new Sandwich(*this);
}

