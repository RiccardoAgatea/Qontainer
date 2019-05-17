#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>
#include <QGridLayout>
#include "OrderWidget.h"

class Controller;

class View: public QMainWindow
{
	Q_OBJECT

private:
	Controller *controller;
	QGridLayout *general_layout;
	QGridLayout *bar_layout;
	QGridLayout *desserts_layout;
	QGridLayout *completed_layout;
public:
	explicit View(QWidget * = nullptr);
	QSize sizeHint() const override;

signals:

public slots:
	void newOrder();
	void removeOrder(OrderWidget *);
	void completeOrder(OrderWidget *);
	void load();
	void save();
};

#endif // VIEW_H