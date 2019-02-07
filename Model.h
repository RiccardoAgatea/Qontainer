#ifndef MODEL_H
#define MODEL_H
#include "Container.h"
#include "Order.h"
#include <string>
#include <vector>

class Model
{
private:
	Container<Order> to_do;
	Container<Order> completed;

	static const std::vector<std::string> types;
public:
	Model() = default;
	explicit Model(const std::string &, const std::string &);
	void save(const std::string &, const std::string &) const;
	void load(const std::string &, const std::string &);
	bool empty() const;

	static const std::vector<std::string> &getTypes();
};

#endif // MODEL_H