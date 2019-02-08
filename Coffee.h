#ifndef COFFEE_H
#define COFFEE_H
#include "Drink.h"
#include <string>

class Coffee: public Drink
{
private:
	std::string notes;
protected:
	std::string getType() const override;
public:
	Coffee(unsigned int,
		   const std::string &,
		   const std::string &);
	Coffee *clone() const override;
	Coffee *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // COFFEE_H