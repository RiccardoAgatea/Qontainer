#ifndef ALCOHOLIC_H
#define ALCOHOLIC_H
#include "Drink.h"

/**
 * @brief      Represents an order of some alcoholic drink.
 */
class Alcoholic: public Drink
{
public:
	using Drink::Drink;
};

#endif // ALCOHOLIC_H