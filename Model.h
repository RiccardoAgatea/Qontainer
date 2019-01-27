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
	explicit Model(const std::string &);
	void save(const std::string &) const;
	void load(const std::string &);
};

#endif // MODEL_H