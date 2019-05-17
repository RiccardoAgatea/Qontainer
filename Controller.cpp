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

void Controller::addOrder(const QString &type,
                          unsigned int table,
                          const QString &item,
                          const QVector<QVector<QString>> &details)
{
	if (type == "" || table || item == "" || details.empty()) return;
}

QVector<QString> Controller::getTypes()
{
	QVector<QString> aux;

	for (const auto &x : Model::getTypes())
		aux.push_back(QString::fromStdString(x));

	return aux;
}

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
