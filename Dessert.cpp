#include "Dessert.h"
#include <utility>

const std::string Dessert::type("Dessert");
Order::Empty Dessert::empty(type,
{{DetailType::LargeText, "Adding"}}, []
(unsigned int t,
 const std::string &i,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Dessert(t, i, d[0]));
});

Dessert::Dessert(unsigned int t,
                 const std::string &i,
                 const std::string &w):
	Food(t, i, ""),
	with(w)
{

}

Dessert *Dessert::clone() const
{
	return new Dessert(*this);
}

Dessert *Dessert::move()
{
	return new Dessert(std::move(*this));
}

std::string Dessert::getType() const
{
	return type;
}

std::string Dessert::getAddedParts() const
{
	return with;
}

std::vector<std::string> Dessert::getDetails() const
{
	return {getAddedParts()};
}

bool Dessert::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       with == static_cast<const Dessert &>(o).with;
}
