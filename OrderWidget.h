#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H
#include <QWidget>
#include "Controller.h"
#include "Order.h"

class OrderWidget: public QWidget
{
	Q_OBJECT
private:
	const Order &order;
public:
	explicit OrderWidget(const Order &, QWidget * = nullptr);

signals:
	void complete();
	void remove();

public slots:
};

#endif // ORDERWIDGET_H