#include "Hamburger.h"
#include <utility>

std::string Hamburger::getType() const
{
	return "hamburger";
}

Hamburger *Hamburger::clone() const
{
	return new Hamburger(*this);
}

Hamburger *Hamburger::move()
{
	return new Hamburger(std::move(*this));
}

