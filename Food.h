#ifndef FOOD_H
#define FOOD_H
#include "Order.h"

class Food : public Order
{
private:
	std::string without;

	static const std::string class_name;
	static Order::Empty empty;
public:
	Food(unsigned int,
	     const std::string &,
	     unsigned int,
	     const std::string &);
	Food *clone() const override = 0;
	std::string getWithout() const;
	void setWithout(const std::string &);
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // FOOD_H