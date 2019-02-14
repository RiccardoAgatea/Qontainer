#ifndef HAMBURGER_H
#define HAMBURGER_H
#include "MeatBased.h"

/**
 * @brief      Represents an order of some hamburger dish.
 */
class Hamburger: public MeatBased
{
public:
	using MeatBased::MeatBased;
	Hamburger *clone() const override;
	Hamburger *move() override;
	std::string getType() const override;
};

#endif // HAMBURGER_H