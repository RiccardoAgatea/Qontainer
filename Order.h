#ifndef ORDER_H
#define ORDER_H
#include <string>

class Order
{
private:
	unsigned int table;
	std::string food;
public:
	Order(unsigned int t, const std::string &f);
	virtual ~Order() = default;
	virtual Order *clone() const = 0;
	virtual std::string recap() const;
	virtual bool operator==(const Order &o) const;
	bool operator!=(const Order &o) const;
};

#endif // ORDER_H