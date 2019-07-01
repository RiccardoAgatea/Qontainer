#ifndef FOOD_H
#define FOOD_H
#include "Order.h"

class Food : public Order
{
private:
	std::string without;

	static Order::Empty empty;
public:
	Food(unsigned int,
	     const std::string &,
	     unsigned int,
	     const std::string &);
	Food *clone() const override = 0;
	std::string getRemovedParts() const;
	void setRemovedParts(const std::string &);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // FOOD_H