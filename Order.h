#ifndef ORDER_H
#define ORDER_H
#include <string>

class Order
{
private:
	unsigned int table;
	std::string item;
protected:
	virtual std::string getType() const = 0;

	static const char separator = '$';
	static const char *empty;
public:
	Order(unsigned int t, const std::string &i);
	virtual ~Order() = default;
	virtual Order *clone() const = 0;
	std::string recap() const;
	virtual std::string getDetails() const = 0;
	virtual void setDetails(const std::string &detail) = 0;
	virtual bool operator==(const Order &o) const;
	bool operator!=(const Order &o) const;
};

#endif // ORDER_H