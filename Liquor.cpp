#include "Liquor.h"
#include <utility>
#include <stdexcept>

const std::string Liquor::type("Liquor");
Order::Empty Liquor::empty(type,
{{DetailType::CheckBox, "Ice"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Liquor(t, i, q, std::stoi(d[0])));
});

Liquor::Liquor(unsigned int t,
               const std::string &i,
               unsigned int q,
               bool ic):
	Alcoholic(t, i, q),
	ice(ic)
{

}

Liquor *Liquor::clone() const
{
	return new Liquor(*this);
}

std::string Liquor::getType() const
{
	return type;
}

bool Liquor::isIced() const
{
	return ice;
}

void Liquor::setIced(bool ic)
{
	ice = ic;
}

std::vector<std::string> Liquor::getDetails() const
{
	return {isIced() ? "1" : "0"};
}

void Liquor::setDetails(const std::vector<std::string> &det)
{
	setIced(det[0] == "1");
}

bool Liquor::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       ice == static_cast<const Liquor &>(o).ice;
}
