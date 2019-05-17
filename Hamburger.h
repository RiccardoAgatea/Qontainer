#ifndef HAMBURGER_H
#define HAMBURGER_H
#include "MeatBased.h"

class Hamburger: public MeatBased
{
public:
	using MeatBased::MeatBased;
	Hamburger *clone() const override;
	Hamburger *move() override;
	std::string getType() const override;
};

#endif // HAMBURGER_H