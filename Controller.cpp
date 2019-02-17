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
	model->addOrder(
		type.toStdString() + separator +
		std::to_string(table) + separator +
		item.toStdString() + separator +
		details.toStdString()
	);
}

const std::vector<std::string> Controller::getTypes()
{
	return Model::getTypes();
}
