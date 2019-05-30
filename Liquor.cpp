#include "Liquor.h"
#include <utility>
#include <stdexcept>

const std::string Liquor::type("Liquor");
Order::Empty Liquor::empty(type,
{{DetailType::CheckBox, "Ice"}}, []
(unsigned int t,
 const std::string &i,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Liquor(t, i, std::stoi(d[0])));
});

Liquor::Liquor(unsigned int t,
               const std::string &i,
               bool ic):
	Alcoholic(t, i),
	ice(ic)
{

}

Liquor *Liquor::clone() const
{
	return new Liquor(*this);
}

Liquor *Liquor::move()
{
	return new Liquor(std::move(*this));
}

std::string Liquor::getType() const
{
	return type;
}

bool Liquor::isIced() const
{
	return ice;
}

std::vector<std::string> Liquor::getDetails() const
{
	return {isIced() ? "1" : "0"};
}

bool Liquor::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       ice == static_cast<const Liquor &>(o).ice;
}
