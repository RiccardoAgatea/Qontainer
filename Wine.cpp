#include "Wine.h"
#include <utility>
#include <stdexcept>

std::string Wine::getType() const
{
	return "Wine";
}

Wine::Wine(unsigned int t, const std::string &i, bool v):
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

std::string Wine::getDetails() const
{
	return vintage ? "1" : "0";
}

void Wine::setDetails(const std::string &detail)
{
	if (detail != "0" && detail != "1")
		throw std::invalid_argument("Wine::setDetails() called with argument not in {0,1}");

	vintage = detail == "1";
}

bool Wine::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
		   vintage == static_cast<const Wine &>(o).vintage;
}
