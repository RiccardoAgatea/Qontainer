#include "Analcoholic.h"
#include <utility>
#include <stdexcept>

const std::string Analcoholic::class_name("Analcoholic");
Order::Empty Analcoholic::empty(class_name,
{{DetailType::Choice, "Ice"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Analcoholic(t, i, q, std::stoi(d[0])));
});

Analcoholic::Analcoholic(unsigned int t,
                         const std::string &i,
                         unsigned int q,
                         bool ic):
	Drink(t, i, q),
	ice(ic)
{

}

Analcoholic *Analcoholic::clone() const
{
	return new Analcoholic(*this);
}

std::string Analcoholic::getClassName() const
{
	return class_name;
}

bool Analcoholic::isA(const std::string &type) const
{
	return type == Analcoholic::getClassName() || Drink::isA(type);
}

bool Analcoholic::isIced() const
{
	return ice;
}

void Analcoholic::setIced(bool ic)
{
	ice = ic;
}

std::vector<std::string> Analcoholic::getDetails() const
{
	return {isIced() ? "1" : "0"};
}

void Analcoholic::setDetails(const std::vector<std::string> &det)
{
	setIced(det[0] == "1");
}

bool Analcoholic::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       ice == static_cast<const Analcoholic &>(o).ice;
}
