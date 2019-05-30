#include "Controller.h"
#include "View.h"

Controller::Controller(View *v):
	QWidget(v),
	model(new Model),
	view(v)
{

}

bool Controller::isModelEmpty() const
{
	return model->empty();
}

void Controller::load(const QString &)
{

}

void Controller::save(const QString &) const
{

}

const Order &Controller::addOrder(const QString &type,
								  unsigned int table,
								  const QString &item,
								  const std::vector<std::string> &details)
{
	return model->addOrder(type.toStdString(),
						   table,
						   item.toStdString(),
						   details);
}
