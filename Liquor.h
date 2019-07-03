#ifndef LIQUOR_H
#define LIQUOR_H
#include "Alcoholic.h"

class Liquor: public Alcoholic
{
private:
	bool ice;

	static const std::string class_name;
	static Order::Empty empty;
public:
	Liquor(unsigned int,
	       const std::string &,
	       unsigned int,
	       bool);
	Liquor *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	bool isIced() const;
	void setIced(bool);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // LIQUOR_H