#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "Alcoholic.h"

class Cocktail: public Alcoholic
{
private:
	std::string garnish;

	static const std::string class_name;
	static Order::Empty empty;
public:
	Cocktail(unsigned int,
	         const std::string &,
	         unsigned int,
	         const std::string &);
	Cocktail *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	std::string getGarnish() const;
	void setGarnish(const std::string &);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // COCKTAIL_H