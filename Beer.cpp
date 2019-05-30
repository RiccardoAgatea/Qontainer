#include "Beer.h"
#include <utility>

const std::string Beer::type("Beer");
Order::Empty Beer::empty(type,
{{DetailType::SmallText, "Size"}}, []
(unsigned int t,
 const std::string &i,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Beer(t, i, d[0]));
});

Beer::Beer(unsigned int t,
           const std::string &i,
           const std::string &s):
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

std::string Beer::getType() const
{
	return type;
}

std::string Beer::getSize() const
{
	return size;
}

std::vector<std::string> Beer::getDetails() const
{
	return {getSize()};
}

bool Beer::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       size == static_cast<const Beer &>(o).size;
}
