#include "EditOrderDialog.h"
#include "Order.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QLabel>
#include <QIntValidator>

EditOrderDialog::EditOrderDialog(const std::string &type,
								 unsigned int q,
								 const std::vector<std::string> &det,
								 QWidget *parent):
	QDialog(parent),
	quantity_line_edit(new QLineEdit(QString::number(q))),
	details_layout(new QVBoxLayout)
{
	setMinimumWidth(250);
	setMaximumWidth(250);
	setWindowIcon(QIcon(":/icon/Edit"));

	QVBoxLayout *main_layout = new QVBoxLayout;
	QHBoxLayout *quantity_layout = new QHBoxLayout;
	QHBoxLayout *buttons_layout = new QHBoxLayout;

	quantity_line_edit->setMaximumWidth(30);
	quantity_line_edit->setValidator(new QIntValidator(0, 20));
	quantity_layout->addWidget(new QLabel("Quantity: "));
	quantity_layout->addWidget(quantity_line_edit);
	quantity_layout->addStretch(1);

	auto fields = Order::getInfo().equal_range(type);

	auto det_it = det.begin();

	for (auto it = fields.first; it != fields.second; ++it)
	{
		auto detail = it->second;

		if (detail.first == Order::DetailType::SmallText)
		{
			QLineEdit *text = new QLineEdit(QString::fromStdString(*det_it));
			text->setPlaceholderText(QString::fromStdString(
										 detail.second));
			text->setMinimumWidth(100);
			details_layout->addWidget(text);
		}
		else if (detail.first == Order::DetailType::LargeText)
		{
			QTextEdit *text = new QTextEdit(QString::fromStdString(*det_it));
			text->setPlaceholderText(QString::fromStdString(
										 detail.second));
			text->setMinimumSize(100, 75);
			text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
			details_layout->addWidget(text);
		}
		else if (detail.first == Order::DetailType::Choice)
		{
			QCheckBox *check = new QCheckBox(QString::fromStdString(
												 detail.second));
			check->setChecked((*det_it) == "1");
			details_layout->addWidget(check);
		}

		++det_it;
	}

	QPushButton *ok_button = new QPushButton("Ok");
	QPushButton *cancel_button = new QPushButton("Cancel");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(ok_button);
	buttons_layout->addWidget(cancel_button);

	main_layout->addLayout(quantity_layout);
	main_layout->addLayout(details_layout);
	main_layout->addStretch(1);
	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);

	connect(ok_button, &QPushButton::clicked,
			this, &EditOrderDialog::accept);

	connect(cancel_button, &QPushButton::clicked,
			this, &EditOrderDialog::reject);
}

unsigned int EditOrderDialog::getQuantity() const
{
	return quantity_line_edit->text().toUInt();
}

std::vector<std::string> EditOrderDialog::getDetails() const
{
	std::vector<std::string> aux;

	for (int i = 0; i < details_layout->count(); ++i)
	{
		QString text;

		if (qobject_cast<QCheckBox *>(details_layout->
									  itemAt(i)->
									  widget()) != nullptr)
			text = static_cast<QCheckBox *>(details_layout->
											itemAt(i)->
											widget())->isChecked() ?
				   "1" :
				   "0";
		else if (qobject_cast<QLineEdit *>(details_layout->
										   itemAt(i)->
										   widget()) != nullptr)
			text = static_cast<QLineEdit *>(details_layout->
											itemAt(i)->
											widget())->text();
		else if (qobject_cast<QTextEdit *>(details_layout->
										   itemAt(i)->
										   widget()) != nullptr)
			text = static_cast<QTextEdit *>(details_layout->
											itemAt(i)->
											widget())->toPlainText();

		aux.push_back(text.toStdString());
	}

	return aux;
}
