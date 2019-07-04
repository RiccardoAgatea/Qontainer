#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H
#include <QFrame>
#include <QVBoxLayout>
#include "Model.h"

class OrderWidget: public QFrame
{
	Q_OBJECT
private:
	Model::Index order;

private slots:
	void edit();
public:
	explicit OrderWidget(const Model::Index &,
						 bool = false,
						 QWidget * = nullptr);
	Model::Index getOrder() const;

signals:
	void update();
	void complete(OrderWidget *);
	void remove(OrderWidget *);

public slots:
};

#endif // ORDERWIDGET_H