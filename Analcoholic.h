#ifndef ANALCOHOLIC_H
#define ANALCOHOLIC_H
#include "Drink.h"

class Analcoholic: public Drink
{
private:
	bool ice;

	static const std::string type;
	static Order::Empty empty;
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