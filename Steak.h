#ifndef STEAK_H
#define STEAK_H
#include "MeatBased.h"

class Steak: public MeatBased
{
private:
	static const std::string class_name;
	static Order::Empty empty;
public:
	Steak(unsigned int,
	      const std::string &,
	      unsigned int,
	      const std::string &);
	Steak *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
};

#endif // STEAK_H