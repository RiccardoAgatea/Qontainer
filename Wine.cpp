#include "Wine.h"
#include <utility>
#include <stdexcept>

Wine::Wine(unsigned int t,
		   const std::string &i,
		   bool v):
	Alcoholic(t, i),
	vintage(v)
{

}

Wine *Wine::clone() const
{
	return new Wine(*this);
}

Wine *Wine::move()
{
	return new Wine(std::move(*this));
}

std::string Wine::getType() const
{
	return "Wine";
}

bool Wine::isVintage() const
{
	return vintage;
}

std::vector<std::string> Wine::getDetails() const
{
	return {isVintage() ? "1" : "0"};
}

bool Wine::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
		   vintage == static_cast<const Wine &>(o).vintage;
}
