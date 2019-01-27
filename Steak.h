#ifndef STEAK_H
#define STEAK_H
#include "MeatBased.h"
#include <string>

class Steak: public MeatBased
{
protected:
	std::string getType() const override;
public:
	Steak(unsigned int, const std::string &, const std::string &);
	Steak *clone() const override;
	Steak *move() override;
};

#endif // STEAK_H