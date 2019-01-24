#ifndef FOOD_H
#define FOOD_H
#include "Order.h"

class Food : public Order
{
private:
	std::string without;
public:
	Food(unsigned int t, const std::string &i, const std::string &w);
	virtual std::string getDetails() const override;
	virtual void setDetails(const std::string &detail) override;
	virtual bool operator==(const Order &o) const override;
};

#endif // FOOD_H