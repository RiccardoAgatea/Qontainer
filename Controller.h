#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "Model.h"
#include <QString>
#include <QVector>
#include <string>
#include <vector>

class View;

class Controller: public QWidget
{
	Q_OBJECT
private:
	Model *model;
	View *view;
public:
	explicit Controller(View *);
	bool isModelEmpty() const;
	void load(const QString &);
	void save(const QString &) const;
	const Order &addOrder(const QString &,
						  unsigned int,
						  const QString &,
						  const std::vector<std::string> &);
signals:

public slots:
};

#endif // CONTROLLER_H