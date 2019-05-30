#ifndef DESSERT_H
#define DESSERT_H
#include "Food.h"

class Dessert: public Food
{
private:
	std::string with;

	static const std::string type;
	static Order::Empty empty;
public:
	Dessert(unsigned int,
	        const std::string &,
	        const std::string &);
	Dessert *clone() const override;
	Dessert *move() override;
	std::string getType() const override;
	std::string getAddedParts() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // DESSERT_H