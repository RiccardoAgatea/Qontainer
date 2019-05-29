#ifndef APPETIZER_H
#define APPETIZER_H
#include "Food.h"

class Appetizer: public Food
{
private:
	std::string sauces;

	static StaticOrder::Empty empty;
public:
	Appetizer(unsigned int,
	          const std::string &,
	          const std::string &);
	Appetizer *clone() const override;
	Appetizer *move() override;
	std::string getType() const override;
	std::string getSauces() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // APPETIZER_H