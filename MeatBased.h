#ifndef MEATBASED_H
#define MEATBASED_H
#include "Food.h"
#include <string>

class MeatBased : public Food
{
private:
	std::string temperature;
public:
	struct Details: public Food::Details
	{
		std::string temperature;

		Details(const MeatBased &);
	};
	MeatBased(unsigned int,
			  const std::string &,
			  const std::string &,
			  const std::string &);
	DeepPtr<Order::Details> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // MEATBASED_H