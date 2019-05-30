#include "OrderWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

OrderWidget::OrderWidget(const Order &o, QWidget *parent):
	QWidget(parent),
	order(o)
{
	QHBoxLayout *main_layout = new QHBoxLayout;
	QVBoxLayout *specifics_layout = new QVBoxLayout;
	QVBoxLayout *buttons_layout = new QVBoxLayout;

	QHBoxLayout *table_type_layout = new QHBoxLayout;
	QHBoxLayout *item_layout = new QHBoxLayout;
	QVBoxLayout *details_layout = new QVBoxLayout;


	specifics_layout->addLayout(table_type_layout);
	specifics_layout->addLayout(item_layout);
	specifics_layout->addLayout(details_layout);

	QPushButton *remove_button = new QPushButton("Remove");
	QPushButton *complete_button = new QPushButton("Complete");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(remove_button);
	buttons_layout->addWidget(complete_button);

	main_layout->addLayout(specifics_layout);
	main_layout->addStretch(1);
	main_layout->addLayout(buttons_layout);
}
