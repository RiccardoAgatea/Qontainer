#ifndef WINE_H
#define WINE_H
#include "Alcoholic.h"

class Wine: public Alcoholic
{
private:
	bool vintage;

	static StaticOrder::Empty empty;
public:
	Wine(unsigned int,
	     const std::string &, bool);
	Wine *clone() const override;
	Wine *move() override;
	std::string getType() const override;
	bool isVintage() const;
	std::vector<std::string> getDetails() const override;
	bool operator==(const Order &) const override;
};

#endif // WINE_H