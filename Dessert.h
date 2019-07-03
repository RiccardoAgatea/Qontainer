#ifndef DESSERT_H
#define DESSERT_H
#include "Food.h"

class Dessert: public Food
{
private:
	std::string with;

	static const std::string class_name;
	static Order::Empty empty;
public:
	Dessert(unsigned int,
	        const std::string &,
	        unsigned int,
	        const std::string &);
	Dessert *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	std::string getAddedParts() const;
	void setAddedParts(const std::string &);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // DESSERT_H