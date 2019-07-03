#include "Dessert.h"
#include <utility>

const std::string Dessert::class_name("Dessert");
Order::Empty Dessert::empty(class_name,
{{DetailType::LargeText, "Adding"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Dessert(t, i, q, d[0]));
});

Dessert::Dessert(unsigned int t,
                 const std::string &i,
                 unsigned int q,
                 const std::string &w):
	Food(t, i, q, ""),
	with(w)
{

}

Dessert *Dessert::clone() const
{
	return new Dessert(*this);
}

std::string Dessert::getClassName() const
{
	return class_name;
}

bool Dessert::isA(const std::string &type) const
{
	return type == Dessert::getClassName() || Food::isA(type);
}

std::string Dessert::getAddedParts() const
{
	return with;
}

void Dessert::setAddedParts(const std::string &w)
{
	with = w;
}

std::vector<std::string> Dessert::getDetails() const
{
	return {getAddedParts()};
}

void Dessert::setDetails(const std::vector<std::string> &det)
{
	setAddedParts(det[0]);
}

bool Dessert::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       with == static_cast<const Dessert &>(o).with;
}
