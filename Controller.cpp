#include "Controller.h"
#include "View.h"

Controller::Controller(View *v):
	QWidget(v),
	model(nullptr),
	view(v)
{

}

bool Controller::isModelEmpty() const
{
	return model == nullptr || model->empty();
}

void Controller::load(const QString &)
{

}

void Controller::save(const QString &) const
{

}

void Controller::addOrder(const QString &type,
						  unsigned int table,
						  const QString &item,
						  const QString &details)
{

}

const std::vector<std::string> Controller::getTypes()
{
	return Model::getTypes();
}
