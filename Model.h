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
	Model() = default;
	explicit Model(const std::string &,
	               const std::string &);
	void save(const std::string &,
	          const std::string &) const;
	void load(const std::string &,
	          const std::string &);
	const Order &addOrder(const std::string &,
						  unsigned int,
						  const std::string &,
						  const std::vector<std::string> &);
	bool empty() const;
};

#endif // MODEL_H