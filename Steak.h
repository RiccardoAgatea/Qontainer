#ifndef STEAK_H
#define STEAK_H
#include "MeatBased.h"
#include <string>

class Steak: public MeatBased
{
protected:
	virtual std::string getType() const override;
public:
	Steak(unsigned int t, const std::string &i, const std::string &temp);
	virtual Steak *clone() const override;
};

#endif // STEAK_H