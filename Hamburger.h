#ifndef HAMBURGER_H
#define HAMBURGER_H
#include "MeatBased.h"

class Hamburger: public MeatBased
{
private:
	static const std::string class_name;
	static Order::Empty empty;
public:
	using MeatBased::MeatBased;
	Hamburger *clone() const override;
	std::string getClassName() const override;
	bool isA(const std::string &) const override;
};

#endif // HAMBURGER_H