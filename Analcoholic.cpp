#include "Analcoholic.h"
#include <utility>
#include <stdexcept>

const std::string Analcoholic::type("Analcoholic");
Order::Empty Analcoholic::empty(type,
{{DetailType::CheckBox, "Ice"}}, []
(unsigned int t,
 const std::string &i,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Analcoholic(t, i, std::stoi(d[0])));
});

Analcoholic::Analcoholic(unsigned int t,
						 const std::string &i,
						 bool ic):
	Drink(t, i),
	ice(ic)
{

}

Analcoholic *Analcoholic::clone() const
{
	return new Analcoholic(*this);
}

Analcoholic *Analcoholic::move()
{
	return new Analcoholic(std::move(*this));
}

std::string Analcoholic::getType() const
{
	return type;
}

bool Analcoholic::isIced() const
{
	return ice;
}

std::vector<std::string> Analcoholic::getDetails() const
{
	return {isIced() ? "1" : "0"};
}

bool Analcoholic::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       ice == static_cast<const Analcoholic &>(o).ice;
}
