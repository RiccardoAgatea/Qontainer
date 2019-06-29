#ifndef STEAK_H
#define STEAK_H
#include "MeatBased.h"

class Steak: public MeatBased
{
private:
	static const std::string type;
	static Order::Empty empty;
public:
	Steak(unsigned int,
	      const std::string &,
	      unsigned int,
	      const std::string &);
	Steak *clone() const override;
	std::string getType() const override;
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
};

#endif // STEAK_H