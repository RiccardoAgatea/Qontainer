#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "Model.h"

class View;

class Controller: public QWidget
{
	Q_OBJECT
private:
	Model *model;
	View *view;
public:
	explicit Controller(View *);

signals:

public slots:
};

#endif // CONTROLLER_H