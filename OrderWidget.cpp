#include "OrderWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

OrderWidget::OrderWidget(const DeepPtr<Order> &o, QWidget *parent):
	QWidget(parent),
	order(o)
{
	QVBoxLayout *main_layout = new QVBoxLayout;
	QHBoxLayout *buttons_layout = new QHBoxLayout;

	QPushButton *remove_button = new QPushButton("Remove");
	QPushButton *complete_button = new QPushButton("Complete");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(remove_button);
	buttons_layout->addWidget(complete_button);

	main_layout->addStretch(1);
	main_layout->addLayout(buttons_layout);
}
