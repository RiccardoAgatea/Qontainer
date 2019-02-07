#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "Model.h"
#include <QString>
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

	static const std::vector<std::string> getTypes();

signals:

public slots:
};

#endif // CONTROLLER_H