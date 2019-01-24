#ifndef HAMBURGER_H
#define HAMBURGER_H
#include "MeatBased.h"
#include <string>

class Hamburger: public MeatBased
{
protected:
	virtual std::string getType() const override;
public:
	using MeatBased::MeatBased;
	virtual Hamburger *clone() const override;
};

#endif // HAMBURGER_H