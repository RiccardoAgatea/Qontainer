#include "Order.h"
#include <typeinfo>
#include <QDebug>

std::vector<std::string> &Order::types()
{
	static std::vector<std::string> *aux = new std::vector<std::string>;
	return *aux;
}

std::multimap<std::string, std::pair<Order::DetailType, std::string>>
		&Order::info()
{
	static std::multimap<std::string,
		   std::pair<Order::DetailType,
		   std::string>>
		   *aux =
			   new std::multimap<std::string,
	std::pair<Order::DetailType,
	std::string>>;
	return *aux;
}

std::map<std::string, std::function<DeepPtr<Order>(unsigned int,
		const std::string &,
		const std::vector<std::string> &)>>
				&Order::make()
{
	static std::map<std::string,
		   std::function<DeepPtr<Order>(unsigned int,
										const std::string &,
										const std::vector<std::string> &)>>
		   *aux =
			   new std::map<std::string,
	std::function<DeepPtr<Order>(unsigned int,
								 const std::string &,
								 const std::vector<std::string> &)>>;
	return *aux;
}

Order::Order(unsigned int t,
             const std::string &i):
	table(t),
	item(i)
{

}


unsigned int Order::getTable()
{
	return table;
}


std::string Order::getItem()
{
	return item;
}


bool Order::operator==(const Order &o) const
{
	return getType() == o.getType() &&
	       table == o.table &&
	       item == o.item;
}


bool Order::operator!=(const Order &o) const
{
	return !(*this == o);
}

const std::vector<std::string> &Order::getTypes()
{
	return types();
}

const std::multimap<std::string, std::pair<Order::DetailType, std::string> >
&Order::getInfo()
{
	return info();
}

std::map<std::string, std::function<DeepPtr<Order> (unsigned int, const std::string &, const std::vector<std::string> &)> >
&Order::getMake()
{
	return make();
}

Order::Empty::Empty(const std::string &type,
					const std::vector<std::pair<Order::DetailType,
					std::string>> &details,
					const std::function<DeepPtr<Order>(unsigned int,
							const std::string &,
							const std::vector<std::string> &)> &constructor)
{
	types().push_back(type);

	for (auto &x : details)
		info().insert({type, x});

	make()[type] = constructor;
}
