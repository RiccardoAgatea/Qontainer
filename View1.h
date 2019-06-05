#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>
#include <QVBoxLayout>
#include "OrderWidget.h"

class Model;

class View: public QMainWindow
{
	Q_OBJECT

private:
	Model *model;
	QVBoxLayout *lineup_layout;
	QVBoxLayout *completed_layout;
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