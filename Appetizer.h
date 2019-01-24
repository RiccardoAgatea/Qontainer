#ifndef APPETIZER_H
#define APPETIZER_H
#include "Food.h"
#include <string>

class Appetizer: public Food
{
private:
	std::string sauces;
protected:
	virtual std::string getType() const override;
public:
	Appetizer(unsigned int t, const std::string &i, const std::string &s);
	virtual Appetizer *clone() const override;
	virtual std::string getDetails() const override;
	virtual void setDetails(const std::string &detail) override;
	virtual bool operator==(const Order &o) const override;
};

#endif // APPETIZER_H