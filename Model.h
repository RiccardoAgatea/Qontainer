#ifndef MODEL_H
#define MODEL_H
#include "Container.h"
#include "Order.h"
#include "PolyStatic.h"
#include <string>
#include <QString>
#include <vector>
#include <functional>

class Model
{
private:
	Container<Order> to_do;
	Container<Order> completed;
public:
	using Index = Container<Order>::iterator;

	Model() = default;
	void save(const QString &) const;
	void load(const QString &);
	Index addOrder(const std::string &,
				   unsigned int,
				   const std::string &,
				   unsigned int,
				   const std::vector<std::string> &);
	void removeOrder(const Index &);
	void completeOrder(const Index &);
	std::vector<Index> searchToDo(
		const std::function<bool(const Order &)> &);
	std::vector<Index> searchCompleted(
		const std::function<bool(const Order &)> &);
	bool empty() const;
};

#endif // MODEL_H