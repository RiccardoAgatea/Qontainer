#include "Steak.h"
#include <utility>

Steak::Steak(unsigned int t,
             const std::string &i,
             const std::string &temp):
	MeatBased(t, i, "", temp)
{

}

Steak *Steak::clone() const
{
	return new Steak(*this);
}

Steak *Steak::move()
{
	return new Steak(std::move(*this));
}

std::string Steak::getType() const
{
	return "Steak";
}

std::vector<std::string> Steak::getDetails() const
{
	return {getTemperature()};
}