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
public:
	explicit OrderWidget(const Model::Index &, QWidget * = nullptr);
	Model::Index getOrder() const;

signals:
	void complete(OrderWidget *);
	void remove(OrderWidget *);

public slots:
};

#endif // ORDERWIDGET_H