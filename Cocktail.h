#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "Alcoholic.h"
#include <string>

class Cocktail: public Alcoholic
{
private:
	std::string garnish;
protected:
	std::string getType() const override;
public:
	Cocktail(unsigned int, const std::string &, const std::string &);
	Cocktail *clone() const override;
	Cocktail *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // COCKTAIL_H