#ifndef SANDWICH_H
#define SANDWICH_H
#include "Food.h"

class Sandwich: public Food
{
private:
	static StaticOrder::Empty empty;
public:
	using Food::Food;
	Sandwich *clone() const override;
	Sandwich *move() override;
	std::string getType() const override;
};

#endif // SANDWICH_H