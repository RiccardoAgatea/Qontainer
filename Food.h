#ifndef FOOD_H
#define FOOD_H
#include "Order.h"

class Food : public Order
{
private:
	std::string without;
public:
	Food(unsigned int,
	     const std::string &,
	     unsigned int,
	     const std::string &);
	Food *clone() const override = 0;
	std::string getRemovedParts() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // FOOD_H