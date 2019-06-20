#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "Alcoholic.h"

class Cocktail: public Alcoholic
{
private:
	std::string garnish;

	static const std::string type;
	static Order::Empty empty;
public:
	Cocktail(unsigned int,
	         const std::string &,
	         unsigned int,
	         const std::string &);
	Cocktail *clone() const override;
	std::string getType() const override;
	std::string getGarnish() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // COCKTAIL_H