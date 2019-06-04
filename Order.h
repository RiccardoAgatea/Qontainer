#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "DeepPtr.h"

class Order
{
public:
	enum class DetailType;
private:
	unsigned int table;
	std::string item;
	unsigned int quantity;

	static std::vector<std::string> &types();
	static
	std::multimap<std::string, std::pair<DetailType, std::string>> &
			info();
	static
	std::map<std::string, std::function<DeepPtr<Order>(unsigned int,
			const std::string &,
			unsigned int,
			const std::vector<std::string> &)>> &make();

protected:
	class Empty
	{
	public:
		Empty(const std::string &,
			  const std::vector<std::pair<DetailType, std::string>> &,
			  const std::function<DeepPtr<Order>(unsigned int,
					  const std::string &,
					  unsigned int,
					  const std::vector<std::string> &)> &);
	};
public:
	enum class DetailType
	{
		CheckBox,
		SmallText,
		LargeText
	};

	Order(unsigned int,
		  const std::string &,
		  unsigned int);
	virtual ~Order() = default;
	virtual Order *clone() const = 0;
	virtual Order *move() = 0;
	unsigned int getTable();
	std::string getItem();
	unsigned int getQuantity() const;
	virtual std::string getType() const = 0;
	virtual std::vector<std::string> getDetails() const = 0;
	virtual bool operator==(const Order &) const;
	bool operator!=(const Order &) const;

	static const std::vector<std::string> &getTypes();
	static const
	std::multimap<std::string, std::pair<DetailType, std::string>> &
			getInfo();
	static
	std::map<std::string, std::function<DeepPtr<Order>(unsigned int,
			const std::string &,
			unsigned int,
			const std::vector<std::string> &)>> &getMake();
};

#endif // ORDER_H