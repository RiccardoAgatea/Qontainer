#ifndef SANDWICH_H
#define SANDWICH_H
#include "Food.h"

class Sandwich: public Food
{
private:
	static const std::string class_name;
	static Order::Empty empty;
public:
	using Food::Food;
	Sandwich *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
};

#endif // SANDWICH_H