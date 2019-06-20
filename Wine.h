#ifndef WINE_H
#define WINE_H
#include "Alcoholic.h"

class Wine: public Alcoholic
{
private:
	bool vintage;

	static const std::string type;
	static Order::Empty empty;
public:
	Wine(unsigned int,
	     const std::string &,
	     unsigned int,
	     bool);
	Wine *clone() const override;
	std::string getType() const override;
	bool isVintage() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // WINE_H