#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <vector>
#include "PolyConstruct.h"
#include "DeepPtr.h"

class Order
{
private:
	unsigned int table;
	std::string item;
protected:

public:
	struct Details {};
	Order(unsigned int,
		  const std::string &);
	virtual ~Order() = default;
	virtual Order *clone() const = 0;
	virtual Order *move() = 0;
	unsigned int getTable();
	std::string getItem();
	virtual std::string getType() const = 0;
	virtual DeepPtr<Details> getDetails() const = 0;
	virtual bool operator==(const Order &) const;
	bool operator!=(const Order &) const;
};

namespace PolyConstruct
{
template<>
Order *clone(const Order &);

template<>
Order *clone(Order &&);
}

#endif // ORDER_H