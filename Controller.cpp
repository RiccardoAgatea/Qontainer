#include "Controller.h"
#include "View.h"

const char &Controller::separator = Order::separator;

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

void Controller::addOrder(const QString &s)
{
	model->addOrder(s.toStdString());
}

const std::vector<std::string> Controller::getTypes()
{
	return Model::getTypes();
}
