#ifndef DRINK_H
#define DRINK_H
#include "Order.h"
#include <string>

class Drink: public Order
{
private:
	std::string notes;
public:
	Drink(unsigned int t, const std::string &i, const std::string &n);
	virtual std::string getDetails() const override;
	virtual void setDetails(const std::string &detail) override;
	virtual bool operator==(const Order &o) const override;
};

#endif // DRINK_H