#ifndef ALCOHOLIC_H
#define ALCOHOLIC_H
#include "Drink.h"

class Alcoholic: public Drink
{
public:
	using Drink::Drink;
	Alcoholic *clone() const override = 0;
	Alcoholic *move() override = 0;
};

#endif // ALCOHOLIC_H