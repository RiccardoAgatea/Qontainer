#ifndef ALCOHOLIC_H
#define ALCOHOLIC_H
#include "Drink.h"

class Alcoholic: public Drink
{
private:
	static Order::Empty empty;
public:
	using Drink::Drink;
	Alcoholic *clone() const override = 0;
};

#endif // ALCOHOLIC_H