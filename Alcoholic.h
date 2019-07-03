#ifndef ALCOHOLIC_H
#define ALCOHOLIC_H
#include "Drink.h"

class Alcoholic: public Drink
{
private:
	static const std::string class_name;
	static Order::Empty empty;
public:
	using Drink::Drink;
	Alcoholic *clone() const override = 0;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
};

#endif // ALCOHOLIC_H