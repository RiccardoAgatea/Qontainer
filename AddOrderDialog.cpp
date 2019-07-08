#include "AddOrderDialog.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QRadioButton>
#include <QCheckBox>

void AddOrderDialog::setup()
{
	while (!details_layout->isEmpty())
	{
		QLayoutItem *item = details_layout->takeAt(0);

		delete item->widget();
		delete item;
	}

	auto fields =
	    Order::getInfo().equal_range(
	        types_group->checkedButton()->text().toStdString());

	for (auto it = fields.first; it != fields.second; ++it)
	{
		auto detail = it->second;

		if (detail.first == Order::DetailType::SmallText)
		{
			QLineEdit *text = new QLineEdit();
			text->setPlaceholderText(QString::fromStdString(
			                             detail.second));
			text->setMinimumWidth(100);
			details_layout->addWidget(text);
			text->show();
		}
		else if (detail.first == Order::DetailType::LargeText)
		{
			QTextEdit *text = new QTextEdit();
			text->setPlaceholderText(QString::fromStdString(
			                             detail.second));
			text->setMinimumSize(100, 75);
			text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
			details_layout->addWidget(text);
			text->show();
		}
		else if (detail.first == Order::DetailType::Choice)
		{
			QCheckBox *check = new QCheckBox(QString::fromStdString(
			                                     detail.second));
			details_layout->addWidget(check);
			check->show();
		}
	}
}

AddOrderDialog::AddOrderDialog(QWidget *parent):
	QDialog(parent),
	table_line_edit(new QLineEdit),
	item_line_edit(new QLineEdit),
	quantity_line_edit(new QLineEdit),
	types_group(new QButtonGroup),
	details_layout(new QVBoxLayout)
{
	setMinimumWidth(250);
	setMaximumWidth(250);
	setWindowTitle("Add Order");
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowIcon(QIcon(":/icon/AddOrder"));

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

	QGridLayout *types_layout = new QGridLayout;

	int pos = 0;

	for (auto &t : Order::getTypes())
	{
		QRadioButton *button = new QRadioButton(QString::fromStdString(t));
		types_layout->addWidget(button, pos / 2, pos % 2);
		types_group->addButton(button);
		++pos;
	}

	types_box->setLayout(types_layout);

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

	connect(types_group, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
	        this, &AddOrderDialog::setup);

	connect(ok_button, &QPushButton::clicked,
	        this, &AddOrderDialog::accept);

	connect(cancel_button, &QPushButton::clicked,
	        this, &AddOrderDialog::reject);

	types_group->buttons()[0]->click();
}

QSize AddOrderDialog::sizeHint() const
{
	return QSize(250, 415);
}

QString AddOrderDialog::getType() const
{
	return types_group->checkedButton()->text();
}

unsigned int AddOrderDialog::getTable() const
{
	return table_line_edit->text().toUInt();
}

QString AddOrderDialog::getItem() const
{
	return item_line_edit->text();
}

unsigned int AddOrderDialog::getQuantity() const
{
	return quantity_line_edit->text().toUInt();
}

std::vector<std::string> AddOrderDialog::getDetails() const
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
