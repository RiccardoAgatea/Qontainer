#ifndef SANDWICH_H
#define SANDWICH_H
#include "Food.h"

class Sandwich: public Food
{
protected:
	virtual std::string getType() const override;
public:
	using Food::Food;
	virtual Sandwich *clone() const override;
};

#endif // SANDWICH_H