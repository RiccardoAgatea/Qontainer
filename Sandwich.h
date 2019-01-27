#ifndef SANDWICH_H
#define SANDWICH_H
#include "Food.h"

class Sandwich: public Food
{
protected:
	std::string getType() const override;
public:
	using Food::Food;
	Sandwich *clone() const override;
	Sandwich *move() override;
};

#endif // SANDWICH_H