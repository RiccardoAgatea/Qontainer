#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>

class Controller;

class View: public QMainWindow
{
	Q_OBJECT

private:
	Controller *controller;

	void createTabs();
public:
	explicit View(QWidget * = nullptr);

signals:

public slots:
};

#endif // VIEW_H