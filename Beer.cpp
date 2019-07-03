#include "Beer.h"
#include <utility>

const std::string Beer::class_name("Beer");
Order::Empty Beer::empty(class_name,
{{DetailType::SmallText, "Size"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Beer(t, i, q, d[0]));
});

Beer::Beer(unsigned int t,
           const std::string &i,
           unsigned int q,
           const std::string &s):
	Alcoholic(t, i, q),
	size(s)
{

}

Beer *Beer::clone() const
{
	return new Beer(*this);
}

std::string Beer::getClassName() const
{
	return class_name;
}

bool Beer::isA(const std::string &type) const
{
	return type == Beer::getClassName() || Alcoholic::isA(type);
}

std::string Beer::getSize() const
{
	return size;
}

void Beer::setSize(const std::string &s)
{
	size = s;
}

std::vector<std::string> Beer::getDetails() const
{
	return {getSize()};
}

void Beer::setDetails(const std::vector<std::string> &det)
{
	setSize(det[0]);
}

bool Beer::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       size == static_cast<const Beer &>(o).size;
}
