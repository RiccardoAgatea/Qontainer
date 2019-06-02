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
	class Index
	{
		friend class Model;
	private:
		Container<Order>::iterator it;

		Index(const Container<Order>::iterator &);
	public:
		const Order &getOrder() const;
	};

	Model() = default;
	void save(const std::string &path) const;
	void load(const std::string &);
	Index addOrder(const std::string &,
				   unsigned int,
				   const std::string &,
				   const std::vector<std::string> &);
	void removeOrder(const Index &);
	bool empty() const;
};

#endif // MODEL_H