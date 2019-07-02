#include "SearchDialog.h"
#include "Order.h"
#include <QGroupBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QLineEdit>

void SearchDialog::showRecursively(QLayout *layout)
{
	if (layout != nullptr)
		for (int i = 0; i < layout->count(); ++i)
		{
			auto item = layout->itemAt(i);

			if (item->layout() != nullptr)
				showRecursively(item->layout());
			else if (item->widget() != nullptr)
				item->widget()->show();
		}
}

void SearchDialog::hideRecursively(QLayout *layout)
{
	if (layout != nullptr)
		for (int i = 0; i < layout->count(); ++i)
		{
			auto item = layout->itemAt(i);

			if (item->layout() != nullptr)
				hideRecursively(item->layout());
			else if (item->widget() != nullptr)
				item->widget()->hide();
		}
}

SearchDialog::SearchDialog(QWidget *parent):
	QDialog(parent),
	table_line_edit(new QLineEdit),
	item_line_edit(new QLineEdit),
	quantity_line_edit(new QLineEdit),
	abstracts_group(new QButtonGroup),
	concretes_group(new QButtonGroup),
	details_layout(new QVBoxLayout)
{
	setMinimumWidth(250);
	setMaximumWidth(250);
	setWindowTitle("Search Options");
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	QVBoxLayout *main_layout = new QVBoxLayout;
	QHBoxLayout *table_quantity_layout = new QHBoxLayout;
	QHBoxLayout *item_layout = new QHBoxLayout;
	QGroupBox *types_box = new QGroupBox("Type");
	QHBoxLayout *buttons_layout = new QHBoxLayout;

	table_line_edit->setMaximumWidth(30);
	quantity_line_edit->setMaximumWidth(30);
	table_line_edit->setValidator(new QIntValidator(0, 100));
	quantity_line_edit->setValidator(new QIntValidator(0, 20));
	table_quantity_layout->addWidget(new QLabel("Table: "));
	table_quantity_layout->addWidget(table_line_edit);
	table_quantity_layout->addStretch(1);
	table_quantity_layout->addWidget(new QLabel("Quantity: "));
	table_quantity_layout->addWidget(quantity_line_edit);

	QRegExp item_regex("^.{0,50}$");
	item_line_edit->setValidator(new QRegExpValidator(item_regex));
	item_layout->addWidget(new QLabel("Item: "));
	item_layout->addWidget(item_line_edit);

	QVBoxLayout *types_layout = new QVBoxLayout;
	QGridLayout *abstracts_layout = new QGridLayout;
	QGroupBox *concretes_box = new QGroupBox;
	QGridLayout *concretes_layout = new QGridLayout;

	int pos = 0;

	for (auto &t : Order::getAbstracts())
	{
		QCheckBox *button = new QCheckBox(QString::fromStdString(t));
		abstracts_layout->addWidget(button, pos / 2, pos % 2);
		abstracts_group->addButton(button);
		++pos;
	}

	pos = 0;

	for (auto &t : Order::getTypes())
	{
		QCheckBox *button = new QCheckBox(QString::fromStdString(t));
		concretes_layout->addWidget(button, pos / 2, pos % 2);
		concretes_group->addButton(button, pos);
		++pos;
	}

	concretes_box->setLayout(concretes_layout);
	types_layout->addLayout(abstracts_layout);
	types_layout->addWidget(concretes_box);
	types_box->setLayout(types_layout);

	abstracts_group->setExclusive(false);
	concretes_group->setExclusive(false);

	for (int i = 0; i < pos; ++i)
	{
		QVBoxLayout *current_type_layout = new QVBoxLayout;

		auto fields =
			Order::getInfo().equal_range(
				concretes_group->buttons()[i]->text().toStdString());

		for (auto it = fields.first; it != fields.second; ++it)
		{
			auto detail = it->second;

			if (detail.first == Order::DetailType::SmallText)
			{
				QLineEdit *text = new QLineEdit();
				text->setPlaceholderText(QString::fromStdString(
											 detail.second));
				text->setMinimumWidth(100);
				current_type_layout->addWidget(text);
			}
			else if (detail.first == Order::DetailType::LargeText)
			{
				QTextEdit *text = new QTextEdit();
				text->setPlaceholderText(QString::fromStdString(
											 detail.second));
				text->setMinimumSize(100, 75);
				text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
				current_type_layout->addWidget(text);
			}
			else if (detail.first == Order::DetailType::CheckBox)
			{
				QCheckBox *check = new QCheckBox(QString::fromStdString(
													 detail.second));
				current_type_layout->addWidget(check);
			}
		}

		details_layout->addLayout(current_type_layout);
	}

	QPushButton *ok_button = new QPushButton("Ok");
	QPushButton *cancel_button = new QPushButton("Cancel");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(ok_button);
	buttons_layout->addWidget(cancel_button);

	main_layout->addLayout(table_quantity_layout);
	main_layout->addLayout(item_layout);
	main_layout->addWidget(types_box);
	main_layout->addLayout(details_layout);
	main_layout->addStretch(1);
	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);

	connect(ok_button, &QPushButton::clicked,
			this, &SearchDialog::accept);

	connect(cancel_button, &QPushButton::clicked,
			this, &SearchDialog::reject);

	connect(concretes_group,
			QOverload<int>::of(&QButtonGroup::buttonClicked),
			this, [this](int i)
	{
		hideRecursively(details_layout);
		showRecursively(details_layout->itemAt(i)->layout());
	});

	concretes_group->buttons()[0]->click();
}