#include "Alcoholic.h"

const std::string Alcoholic::class_name("Alcoholic");
Order::Empty Alcoholic::empty(class_name);

std::string Alcoholic::getClassName() const
{
	return class_name;
}

bool Alcoholic::isA(const std::string &type) const
{
	return type == Alcoholic::getClassName() || Drink::isA(type);
}
