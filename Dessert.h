#ifndef DESSERT_H
#define DESSERT_H
#include "Food.h"
#include <string>

class Dessert: public Food
{
private:
	std::string with;
protected:
	std::string getType() const override;
public:
	Dessert(unsigned int, const std::string &, const std::string &);
	Dessert *clone() const override;
	Dessert *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // DESSERT_H