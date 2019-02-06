#ifndef ORDER_H
#define ORDER_H
#include <string>
#include "PolyConstruct.h"

class Order
{
private:
	unsigned int table;
	std::string item;

	static char separator;
protected:
	virtual std::string getType() const = 0;
public:
	Order(unsigned int, const std::string &);
	virtual ~Order() = default;
	virtual Order *clone() const = 0;
	virtual Order *move() = 0;
	std::string recap() const;
	virtual std::string getDetails() const = 0;
	virtual void setDetails(const std::string &) = 0;
	virtual bool operator==(const Order &) const;
	bool operator!=(const Order &) const;

	static char getSeparator();
	static void setSeparator(char value);
};

namespace PolyConstruct
{
template<>
Order *clone(const Order &);

template<>
Order *clone(Order &&);
}

#endif // ORDER_H