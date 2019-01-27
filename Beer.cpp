#include "Beer.h"
#include <utility>

std::string Beer::getType() const
{
	return "beer";
}

Beer::Beer(unsigned int t, const std::string &i, const std::string &s):
	Alcoholic(t, i),
	size(s)
{

}

Beer *Beer::clone() const
{
	return new Beer(*this);
}

Beer *Beer::move()
{
	return new Beer(std::move(*this));
}

std::string Beer::getDetails() const
{
	return size;
}

void Beer::setDetails(const std::string &detail)
{
	size = detail;
}

bool Beer::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
		   size == static_cast<const Beer &>(o).size;
}
