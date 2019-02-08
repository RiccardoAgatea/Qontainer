#ifndef APPETIZER_H
#define APPETIZER_H
#include "Food.h"
#include <string>

class Appetizer: public Food
{
private:
	std::string sauces;
protected:
	std::string getType() const override;
public:
	Appetizer(unsigned int,
			  const std::string &,
			  const std::string &);
	Appetizer *clone() const override;
	Appetizer *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // APPETIZER_H