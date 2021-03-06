#ifndef ANALCOHOLIC_H
#define ANALCOHOLIC_H
#include "Drink.h"

class Analcoholic: public Drink
{
private:
	bool ice;

	static const std::string class_name;
	static Order::Empty empty;
public:
	Analcoholic(unsigned int,
	            const std::string &,
	            unsigned int,
	            bool);
	Analcoholic *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	bool isIced() const;
	void setIced(bool);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // ANALCOHOLIC_H