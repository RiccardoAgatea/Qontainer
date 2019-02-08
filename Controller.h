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
	static const char separator = '$';

	explicit Controller(View *);
	bool isModelEmpty() const;
	void load(const QString &);
	void save(const QString &) const;
	void addOrder(const QString &, unsigned int, const QString &, const QString &);

	static const std::vector<std::string> getTypes();

	static char getSeparator();
	static void setSeparator(char value);

signals:

public slots:
};

#endif // CONTROLLER_H