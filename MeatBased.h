#ifndef MEATBASED_H
#define MEATBASED_H
#include "Food.h"
#include <string>

class MeatBased : public Food
{
private:
	std::string temperature;
public:
	MeatBased(unsigned int,
			  const std::string &,
			  const std::string &,
			  const std::string &);
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // MEATBASED_H