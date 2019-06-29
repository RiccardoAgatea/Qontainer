#ifndef BEER_H
#define BEER_H
#include "Alcoholic.h"

class Beer: public Alcoholic
{
private:
	std::string size;

	static const std::string type;
	static Order::Empty empty;
public:
	Beer(unsigned int,
	     const std::string &,
	     unsigned int,
	     const std::string &);
	Beer *clone() const override;
	std::string getType() const override;
	std::string getSize() const;
	void setSize(const std::string &);
	std::vector<std::string> getDetails() const override;
	void setDetails(const std::vector<std::string> &) override;
	bool operator==(const Order &) const override;
};

#endif // BEER_H