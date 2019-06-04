#ifndef APPETIZER_H
#define APPETIZER_H
#include "Food.h"

class Appetizer: public Food
{
private:
	std::string sauces;

	static const std::string type;
	static Order::Empty empty;
public:
	Appetizer(unsigned int,
	          const std::string &,
			  unsigned int,
	          const std::string &);
	Appetizer *clone() const override;
	Appetizer *move() override;
	std::string getType() const override;
	std::string getSauces() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // APPETIZER_H