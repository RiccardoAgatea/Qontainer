#ifndef ANALCOHOLIC_H
#define ANALCOHOLIC_H
#include "Drink.h"

class Analcoholic: public Drink
{
private:
	bool ice;
protected:
	std::string getType() const override;
public:
	Analcoholic(unsigned int, const std::string &, bool);
	Analcoholic *clone() const override;
	Analcoholic *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // ANALCOHOLIC_H