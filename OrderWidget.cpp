#include "OrderWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

OrderWidget::OrderWidget(const Model::Index &in, QWidget *parent):
	QWidget(parent),
	order(in)
{
	QHBoxLayout *main_layout = new QHBoxLayout;
	QVBoxLayout *specifics_layout = new QVBoxLayout;
	QVBoxLayout *buttons_layout = new QVBoxLayout;

	main_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	specifics_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	QHBoxLayout *table_type_layout = new QHBoxLayout;
	table_type_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	QHBoxLayout *item_layout = new QHBoxLayout;
	QVBoxLayout *details_layout = new QVBoxLayout;

	QLabel *table = new QLabel;
	table->setText("Table " + QString::number(order->getTable()));
	QLabel *type = new QLabel;
	type->setText(QString::fromStdString(order->getType()));
	table_type_layout->addWidget(table);
	table_type_layout->addStretch(1);
	table_type_layout->addWidget(type);

	QLabel *item = new QLabel(QString::fromStdString(order->getItem()));
	item_layout->addWidget(item);

	specifics_layout->addLayout(table_type_layout);
	specifics_layout->addLayout(item_layout);
	specifics_layout->addLayout(details_layout);

	QPushButton *remove_button = new QPushButton("Remove");
	QPushButton *complete_button = new QPushButton("Complete");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(remove_button);
	buttons_layout->addWidget(complete_button);

	main_layout->addLayout(specifics_layout);
	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);
}

QSize OrderWidget::sizeHint() const
{
	return QSize(400, 100);
}