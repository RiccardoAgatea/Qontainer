#ifndef MODEL_H
#define MODEL_H
#include "Container.h"
#include "Order.h"
#include <QString>

class Model
{
private:
	Container<Order> to_do;
	Container<Order> completed;
public:
	Model() = default;
	explicit Model(const QString &);
	void save(const QString &) const;
	void load(const QString &);
};

#endif // MODEL_H