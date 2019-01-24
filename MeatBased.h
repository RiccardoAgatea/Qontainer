#ifndef MEATBASED_H
#define MEATBASED_H
#include "Food.h"
#include <string>

class MeatBased : public Food
{
private:
	std::string temperature;
public:
	MeatBased(unsigned int t, const std::string &i, const std::string &w, const std::string &temp);
	virtual std::string getDetails() const override;
	virtual void setDetails(const std::string &detail) override;
	virtual bool operator==(const Order &o) const override;
};

#endif // MEATBASED_H