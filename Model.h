#ifndef MODEL_H
#define MODEL_H
#include "Container.h"
#include "Order.h"
#include <string>

class Model
{
private:
	Container<Order> in_coda;
	Container<Order> completati;
public:
	Model() = default;
	explicit Model(const std::string &path);
	void save(const std::string &path) const;
	void load(const std::string &path);
};

#endif // MODEL_H