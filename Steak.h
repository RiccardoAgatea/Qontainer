#ifndef STEAK_H
#define STEAK_H
#include "MeatBased.h"

/**
 * @brief      Represents an order of some meat-based food.
 */
class Steak: public MeatBased
{
public:
	Steak(unsigned int,
	      const std::string &,
	      const std::string &);
	Steak *clone() const override;
	Steak *move() override;
	std::string getType() const override;
	std::vector<std::string> getDetails() const override;
};

#endif // STEAK_H