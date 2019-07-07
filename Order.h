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

	static const std::string class_name;
	static std::vector<std::string> &abstracts();
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
		Empty(const std::string &);
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
		Choice,
		SmallText,
		LargeText
	};

	Order(unsigned int,
		  const std::string &,
		  unsigned int);
	virtual ~Order() = default;
	virtual Order *clone() const = 0;
	unsigned int getTable() const;
	std::string getItem() const;
	unsigned int getQuantity() const;
	void setQuantity(unsigned int);
	virtual std::string getClassName() const;
	virtual bool isA(const std::string &) const;
	virtual std::vector<std::string> getDetails() const = 0;
	virtual void setDetails(const std::vector<std::string> &) = 0;
	virtual bool operator==(const Order &) const;
	bool operator!=(const Order &) const;

	static const std::vector<std::string> &getAbstracts();
	static const std::vector<std::string> &getTypes();
	static const
	std::multimap<std::string, std::pair<DetailType, std::string>> &
			getInfo();
	static const
	std::map<std::string, std::function<DeepPtr<Order>(unsigned int,
			const std::string &,
			unsigned int,
			const std::vector<std::string> &)>> &getMake();
};

#endif // ORDER_H