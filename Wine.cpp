#include "Wine.h"
#include <utility>
#include <stdexcept>

const std::string Wine::type("Wine");
Order::Empty Wine::empty(type,
{{DetailType::CheckBox, "Vintage"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Wine(t, i, q, std::stoi(d[0])));
});

Wine::Wine(unsigned int t,
           const std::string &i,
           unsigned int q,
           bool v):
	Alcoholic(t, i, q),
	vintage(v)
{

}

Wine *Wine::clone() const
{
	return new Wine(*this);
}

std::string Wine::getType() const
{
	return type;
}

bool Wine::isVintage() const
{
	return vintage;
}

void Wine::setVintage(bool v)
{
	vintage = v;
}

std::vector<std::string> Wine::getDetails() const
{
	return {isVintage() ? "1" : "0"};
}

void Wine::setDetails(const std::vector<std::string> &det)
{
	setVintage(det[0] == "1");
}

bool Wine::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       vintage == static_cast<const Wine &>(o).vintage;
}
