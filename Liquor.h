#ifndef LIQUOR_H
#define LIQUOR_H
#include "Alcoholic.h"

/**
 * @brief      Represents an order of some liquor.
 */
class Liquor: public Alcoholic
{
private:
	bool ice;
public:
	Liquor(unsigned int,
	       const std::string &,
	       bool);
	Liquor *clone() const override;
	Liquor *move() override;
	std::string getType() const override;
	bool isIced() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // LIQUOR_H