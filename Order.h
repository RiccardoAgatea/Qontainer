#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <vector>
#include "StaticOrder.h"

class Order
{
private:
	unsigned int table;
	std::string item;
public:
	Order(unsigned int,
	      const std::string &);
	virtual ~Order() = default;
	virtual Order *clone() const = 0;
	virtual Order *move() = 0;
	unsigned int getTable();
	std::string getItem();
	virtual std::string getType() const = 0;
	virtual std::vector<std::string> getDetails() const = 0;
	virtual bool operator==(const Order &) const;
	bool operator!=(const Order &) const;
};

#endif // ORDER_H