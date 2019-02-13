#include "Hamburger.h"
#include <utility>

Hamburger *Hamburger::clone() const
{
	return new Hamburger(*this);
}

Hamburger *Hamburger::move()
{
	return new Hamburger(std::move(*this));
}

std::string Hamburger::getType() const
{
	return "Hamburger";
}