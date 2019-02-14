#ifndef FOOD_H
#define FOOD_H
#include "Order.h"

/**
 * @brief      Represents an order of some food (as opposed to drinks).
 */
class Food : public Order
{
private:
	std::string without;
public:
	Food(unsigned int,
	     const std::string &,
	     const std::string &);
	std::string getRemovedParts() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // FOOD_H