#include "Hamburger.h"

std::string Hamburger::getType() const
{
	return "hamburger";
}

Hamburger *Hamburger::clone() const
{
	return new Hamburger(*this);
}

