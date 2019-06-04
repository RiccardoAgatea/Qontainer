#ifndef LIQUOR_H
#define LIQUOR_H
#include "Alcoholic.h"

class Liquor: public Alcoholic
{
private:
	bool ice;

	static const std::string type;
	static Order::Empty empty;
public:
	Liquor(unsigned int,
	       const std::string &,
		   unsigned int,
	       bool);
	Liquor *clone() const override;
	Liquor *move() override;
	std::string getType() const override;
	bool isIced() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // LIQUOR_H