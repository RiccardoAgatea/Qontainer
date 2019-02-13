#ifndef FOOD_H
#define FOOD_H
#include "Order.h"

class Food : public Order
{
private:
	std::string without;
public:
	struct Details: public Order::Details
	{
		std::string without;

		Details(const Food &);
	};

	Food(unsigned int,
		 const std::string &,
		 const std::string &);
	DeepPtr<Order::Details> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // FOOD_H