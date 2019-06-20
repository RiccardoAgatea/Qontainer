#ifndef COFFEE_H
#define COFFEE_H
#include "Drink.h"

class Coffee: public Drink
{
private:
	std::string notes;

	static const std::string type;
	static Order::Empty empty;
public:
	Coffee(unsigned int,
	       const std::string &,
	       unsigned int,
	       const std::string &);
	Coffee *clone() const override;
	std::string getType() const override;
	std::string getNotes() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // COFFEE_H