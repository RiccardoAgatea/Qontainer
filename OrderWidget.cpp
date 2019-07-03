#include "OrderWidget.h"
#include "EditOrderDialog.h"
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>

void OrderWidget::edit()
{
	EditOrderDialog edit_dialog(order->getClassName(),
								order->getQuantity(),
								order->getDetails());

	if (edit_dialog.exec())
	{
		order->setQuantity(edit_dialog.getQuantity());
		order->setDetails(edit_dialog.getDetails());

		emit update();
	}
}

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
	QFormLayout *details_layout = new QFormLayout;

	QLabel *table = new QLabel;
	table->setText("Table " + QString::number(order->getTable()));
	table_layout->addWidget(table);
	table_layout->addStretch(1);

	QLabel *type = new QLabel;
	type->setText(QString::fromStdString(order->getClassName()));
	type_layout->addWidget(type);
	type_layout->addStretch(1);

	QLabel *item = new QLabel(QString::fromStdString(order->getItem()));
	item_layout->addWidget(item);
	item_layout->addStretch(1);

	QLabel *quantity = new QLabel;
	quantity->setText(QString::number(order->getQuantity()) + " pieces");
	quantity_layout->addWidget(quantity);
	quantity_layout->addStretch(1);

	auto det = Order::getInfo().equal_range(order->getClassName()).first;

	auto details = order->getDetails();

	for (unsigned int i = 0; i < details.size(); ++i)
	{
		if (det->second.first == Order::DetailType::LargeText)
		{
			QTextEdit *detail_content = new QTextEdit(QString::fromStdString(
						details[i]));
			detail_content->setReadOnly(true);
			detail_content->viewport()->setAutoFillBackground(false);
			detail_content->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			detail_content->setMinimumHeight(65);
			detail_content->setMaximumHeight(65);

			details_layout->addRow(QString::fromStdString(det->second.second) +
								   ": ", detail_content);

			connect(this, &OrderWidget::update,
					detail_content, [this, i, detail_content]()
			{
				detail_content->setText(
					QString::fromStdString(order->getDetails()[i]));
			});
		}
		else if (det->second.first == Order::DetailType::SmallText)
		{
			QLineEdit *detail_content = new QLineEdit(QString::fromStdString(
						details[i]));
			detail_content->setReadOnly(true);
			detail_content->setAutoFillBackground(false);

			details_layout->addRow(QString::fromStdString(det->second.second) +
								   ": ", detail_content);

			connect(this, &OrderWidget::update,
					detail_content, [this, i, detail_content]()
			{
				detail_content->setText(
					QString::fromStdString(order->getDetails()[i]));
			});
		}
		else if (det->second.first == Order::DetailType::CheckBox)
		{
			QCheckBox *detail_content = new QCheckBox;
			detail_content->setEnabled(false);
			detail_content->setChecked(details[i] == "1");

			details_layout->addRow(QString::fromStdString(det->second.second) +
								   ": ", detail_content);

			connect(this, &OrderWidget::update,
					detail_content, [this, i, detail_content]()
			{
				detail_content->setChecked(order->getDetails()[i] == "1");
			});
		}

		++det;
	}

	details_layout->setLabelAlignment(Qt::AlignLeft);

	specifics_layout->addLayout(table_layout);
	specifics_layout->addLayout(type_layout);
	specifics_layout->addLayout(item_layout);
	specifics_layout->addLayout(quantity_layout);
	specifics_layout->addLayout(details_layout);

	QPushButton *edit_button = new QPushButton("Edit");
	QPushButton *complete_button = new QPushButton("Complete");
	QPushButton *remove_button = new QPushButton("Remove");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(edit_button);
	buttons_layout->addWidget(complete_button);
	buttons_layout->addWidget(remove_button);

	main_layout->addLayout(specifics_layout);
	main_layout->addStretch(1);
	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);

	connect(edit_button, &QPushButton::clicked,
			this, &OrderWidget::edit);

	connect(complete_button, &QPushButton::clicked,
			this, [this]()
	{
		emit complete(this);
	});

	connect(remove_button, &QPushButton::clicked,
			this, [this]()
	{
		emit remove(this);
	});

	connect(this, &OrderWidget::update,
			quantity, [this, quantity]()
	{
		quantity->setText(QString::number(order->getQuantity()) + " pieces");
	});
}

Model::Index OrderWidget::getOrder() const
{
	return order;
}