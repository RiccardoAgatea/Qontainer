#include "OrderWidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>

OrderWidget::OrderWidget(const Model::Index &in, QWidget *parent):
	QFrame(parent),
	order(in)
{
	setFixedWidth(400);
	setFrameStyle(QFrame::Panel | QFrame::Raised);

	QHBoxLayout *main_layout = new QHBoxLayout;
	QVBoxLayout *specifics_layout = new QVBoxLayout;
	QVBoxLayout *buttons_layout = new QVBoxLayout;

	main_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	specifics_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	QHBoxLayout *table_layout = new QHBoxLayout;
	QHBoxLayout *type_layout = new QHBoxLayout;
	QHBoxLayout *item_layout = new QHBoxLayout;
	QHBoxLayout *quantity_layout = new QHBoxLayout;
	QVBoxLayout *details_layout = new QVBoxLayout;

	QLabel *table = new QLabel;
	table->setText("Table " + QString::number(order->getTable()));
	table_layout->addWidget(table);
	table_layout->addStretch(1);

	QLabel *type = new QLabel;
	type->setText(QString::fromStdString(order->getType()));
	type_layout->addWidget(type);
	type_layout->addStretch(1);

	QLabel *item = new QLabel(QString::fromStdString(order->getItem()));
	item_layout->addWidget(item);
	item_layout->addStretch(1);

	QLabel *quantity = new QLabel;
	quantity->setText(QString::number(order->getQuantity()) + " pieces");
	quantity_layout->addWidget(quantity);
	quantity_layout->addStretch(1);

	auto det = Order::getInfo().equal_range(order->getType()).first;

	for (auto &x : order->getDetails())
	{
		QHBoxLayout *label_layout = new QHBoxLayout;

		QLabel *detail_name = new QLabel(QString::fromStdString(
											 det->second.second) + ": ");

		QTextEdit *detail_text = new QTextEdit(QString::fromStdString(x));
		detail_text->setReadOnly(true);
		detail_text->viewport()->setAutoFillBackground(false);

		label_layout->addWidget(detail_name);
		label_layout->addWidget(detail_text);
		label_layout->addStretch(1);

		details_layout->addLayout(label_layout);

		++det;
	}

	details_layout->addStretch(1);

	specifics_layout->addLayout(table_layout);
	specifics_layout->addLayout(type_layout);
	specifics_layout->addLayout(item_layout);
	specifics_layout->addLayout(quantity_layout);
	specifics_layout->addLayout(details_layout);

	QPushButton *remove_button = new QPushButton("Remove");
	QPushButton *complete_button = new QPushButton("Complete");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(remove_button);
	buttons_layout->addWidget(complete_button);

	main_layout->addLayout(specifics_layout);
	main_layout->addStretch(1);
	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);

	connect(remove_button, &QPushButton::clicked,
			this, [this]()
	{
		emit remove(this);
	});

	connect(complete_button, &QPushButton::clicked,
			this, [this]()
	{
		emit complete(this);
	});
}

Model::Index OrderWidget::getOrder() const
{
	return order;
}