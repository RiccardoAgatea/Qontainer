#ifndef ANALCOHOLIC_H
#define ANALCOHOLIC_H
#include "Drink.h"

/**
 * @brief      Represents an order of some analcoholic drink.
 */
class Analcoholic: public Drink
{
private:
	bool ice;
public:
	Analcoholic(unsigned int,
	            const std::string &, bool);
	Analcoholic *clone() const override;
	Analcoholic *move() override;
	std::string getType() const override;
	bool isIced() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // ANALCOHOLIC_H