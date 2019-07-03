#ifndef MEATBASED_H
#define MEATBASED_H
#include "Food.h"
#include <string>


class MeatBased : public Food
{
private:
	std::string temperature;

	static const std::string class_name;
	static Order::Empty empty;
public:
	MeatBased(unsigned int,
	          const std::string &,
	          unsigned int,
	          const std::string &,
	          const std::string &);
	MeatBased *clone() const override = 0;
	std::string getTemperature() const;
	void setTemperature(const std::string &);
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // MEATBASED_H