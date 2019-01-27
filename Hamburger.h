#ifndef HAMBURGER_H
#define HAMBURGER_H
#include "MeatBased.h"
#include <string>

class Hamburger: public MeatBased
{
protected:
	std::string getType() const override;
public:
	using MeatBased::MeatBased;
	Hamburger *clone() const override;
	Hamburger *move() override;
};

#endif // HAMBURGER_H