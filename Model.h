#ifndef MODEL_H
#define MODEL_H
#include "Container.h"
#include "Order.h"
#include "PolyStatic.h"
#include <string>
#include <vector>

class Model
{
private:
	Container<Order> to_do;
	Container<Order> completed;
public:
	using Index = Container<Order>::iterator;

	Model() = default;
	void save(const std::string &) const;
	void load(const std::string &);
	Index addOrder(const std::string &,
				   unsigned int,
				   const std::string &,
				   unsigned int,
				   const std::vector<std::string> &);
	void removeOrder(const Index &);
	void completeOrder(const Index &);
	bool empty() const;
};

#endif // MODEL_H