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
	void setVintage(bool);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // WINE_H