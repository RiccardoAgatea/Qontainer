#include "Drink.h"

const std::string Drink::class_name("Drink");
Order::Empty Drink::empty(class_name);

std::string Drink::getClassName() const
{
	return class_name;
}

bool Drink::isA(const std::string &type) const
{
	return type == Drink::getClassName() || Order::isA(type);
}
