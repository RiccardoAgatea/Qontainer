#include "Coffee.h"
#include <utility>

const std::string Coffee::type("Coffee");
Order::Empty Coffee::empty(type,
{{DetailType::LargeText, "Notes"}}, []
(unsigned int t,
 const std::string &i,
 unsigned int q,
 const std::vector<std::string> &d)
{
	return DeepPtr<Order>(Coffee(t, i, q, d[0]));
});

Coffee::Coffee(unsigned int t,
               const std::string &i,
               unsigned int q,
               const std::string &n):
	Drink(t, i, q),
	notes(n)
{

}

Coffee *Coffee::clone() const
{
	return new Coffee(*this);
}

std::string Coffee::getType() const
{
	return type;
}

std::string Coffee::getNotes() const
{
	return notes;
}

void Coffee::setNotes(const std::string &n)
{
	notes = n;
}

std::vector<std::string> Coffee::getDetails() const
{
	return {getNotes()};
}

void Coffee::setDetails(const std::vector<std::string> &det)
{
	setNotes(det[0]);
}

bool Coffee::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       notes == static_cast<const Coffee &>(o).notes;
}
