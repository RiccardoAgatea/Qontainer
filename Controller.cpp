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

/**
 * @brief      Provides an interface for the Model method addOrder()
 */
void Controller::addOrder(const QString &type,
                          unsigned int table,
                          const QString &item,
						  const QVector<QVector<QString>> &details)
{
	std::vector<std::string> aux;

	for (const auto &x : details)
		aux.push_back(x.toStdString());

	model->addOrder(type.toStdString(),
	                table,
	                item.toStdString(),
	                aux);
}

/**
 * @brief      Provides an interface between the View and the Model method
 *             getTypes()
 */
QVector<QString> Controller::getTypes()
{
	QVector<QString> aux;

	for (const auto &x : Model::getTypes())
		aux.push_back(QString::fromStdString(x));

	return aux;
}

/**
 * @brief      Provides an interface between the View and the Model method getInfo()
 */
QVector<QVector<QString> > Controller::getInfo(const QString &type)
{
	std::vector<std::vector<std::string>> temp = Model::getInfo(
										   type.toStdString());
	QVector<QVector<QString>> aux;

	for (const auto &v : temp)
	{
		QVector<QString> t;

		for (const auto &x : v)
			t.push_back(QString::fromStdString(x));

		aux.push_back(t);
	}

	return aux;
}
