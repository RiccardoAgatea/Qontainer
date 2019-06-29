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
	std::string getType() const override;
	std::string getSauces() const;
	void setSauces(const std::string &);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // APPETIZER_H