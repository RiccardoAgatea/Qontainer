#ifndef COFFEE_H
#define COFFEE_H
#include "Drink.h"

class Coffee: public Drink
{
private:
	std::string notes;

	static StaticOrder::Empty empty;
public:
	Coffee(unsigned int,
	       const std::string &,
	       const std::string &);
	Coffee *clone() const override;
	Coffee *move() override;
	std::string getType() const override;
	std::string getNotes() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // COFFEE_H