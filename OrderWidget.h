#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H
#include <QWidget>
#include "Model.h"
#include "Order.h"

class OrderWidget: public QWidget
{
	Q_OBJECT
private:
	Model::Index order;
public:
	explicit OrderWidget(const Model::Index &, QWidget * = nullptr);
	QSize sizeHint() const override;

signals:
	void complete();
	void remove(const Model::Index &);

public slots:
};

#endif // ORDERWIDGET_H