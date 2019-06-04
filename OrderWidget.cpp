#include "OrderWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
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
	//Capisci come aggiungere i dettagli. Maybe metti su una classe che abbia
	//	un label e un LineEdit, un TextEdit, o un Checkbox, e che si gestisca
	//	da sola il posizionamento. Bho. Veid un po'.
	/*
		auto fields = Order::getInfo().equal_range(order->getType());
		auto details = order->getDetails();

		unsigned int i = 0;

		for (auto it = fields.first; it != fields.second; ++i, ++it)
		{
			auto detail = it->second;

			if (detail.first == Order::DetailType::SmallText)
			{
				QLineEdit *text = new QLineEdit();
				text->setReadOnly(true);
				text->setText(QString::fromStdString(details[i]));
				text->setMinimumWidth(100);
				details_layout->addWidget(text);
				text->show();
			}
			else if (detail.first == Order::DetailType::LargeText)
			{
				QTextEdit *text = new QTextEdit();
				text->setReadOnly(true);
				text->setText(QString::fromStdString(details[i]));
				text->setMinimumSize(100, 75);
				text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
				details_layout->addWidget(text);
				text->show();
			}
			else if (detail.first == Order::DetailType::CheckBox)
			{
				QCheckBox *check = new QCheckBox(QString::fromStdString(
													 detail.second));
				details_layout->addWidget(check);
				check->show();
			}
		}*/

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