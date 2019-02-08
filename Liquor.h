#ifndef LIQUOR_H
#define LIQUOR_H
#include "Alcoholic.h"

class Liquor: public Alcoholic
{
private:
	bool ice;
protected:
	std::string getType() const override;
public:
	Liquor(unsigned int,
		   const std::string &,
		   bool);
	Liquor *clone() const override;
	Liquor *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // LIQUOR_H