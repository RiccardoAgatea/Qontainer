#ifndef WINE_H
#define WINE_H
#include "Alcoholic.h"

class Wine: public Alcoholic
{
private:
	bool vintage;
protected:
	std::string getType() const override;
public:
	Wine(unsigned int, const std::string &, bool);
	Wine *clone() const override;
	Wine *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // WINE_H