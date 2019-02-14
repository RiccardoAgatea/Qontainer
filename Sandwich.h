#ifndef SANDWICH_H
#define SANDWICH_H
#include "Food.h"

/**
 * @brief      Represents an order of some sandwich.
 */
class Sandwich: public Food
{
public:
	using Food::Food;
	Sandwich *clone() const override;
	Sandwich *move() override;
	std::string getType() const override;
};

#endif // SANDWICH_H