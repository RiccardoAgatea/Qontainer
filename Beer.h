#ifndef BEER_H
#define BEER_H
#include "Alcoholic.h"
#include <string>

class Beer: public Alcoholic
{
private:
	std::string size;
protected:
	std::string getType() const override;
public:
	Beer(unsigned int,
		 const std::string &,
		 const std::string &);
	Beer *clone() const override;
	Beer *move() override;
	std::string getDetails() const override;
	void setDetails(const std::string &) override;
	bool operator==(const Order &) const override;
};

#endif // BEER_H