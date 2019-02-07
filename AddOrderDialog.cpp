#include "AddOrderDialog.h"
#include "MakeOrder.h"
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QString>

void AddOrderDialog::setDetails()
{
	//essenzialmente, non va
	QString type = choose_type->checkedButton()->text();
	MakeOrder::Info info = MakeOrder::getInfo(type.toStdString());

	for (auto it = details.begin(); it != details.end();)
	{
		details_layout->removeItem(*it);
		it = details.erase(it);
	}

	for (auto &x : info.long_texts)
	{
		QLabel *label = new QLabel(QString::fromStdString(x + ": "));
		QLineEdit *line_edit = new QLineEdit();
		line_edit->setMinimumSize(100, 75);

		QHBoxLayout *layout = new QHBoxLayout();
		layout->addWidget(label);
		layout->addWidget(line_edit);
		layout->addStretch(1);

		details_layout->addLayout(layout);
		details.push_back(layout);
	}

	for (auto &x : info.short_texts)
	{
		QLabel *label = new QLabel(QString::fromStdString(x + ": "));
		QLineEdit *line_edit = new QLineEdit();
		line_edit->setMinimumWidth(100);

		QHBoxLayout *layout = new QHBoxLayout();
		layout->addWidget(label);
		layout->addWidget(line_edit);
		layout->addStretch(1);

		details_layout->addLayout(layout);
		details.push_back(layout);
	}

	for (auto &x : info.checks)
	{
		QCheckBox *checkbox = new QCheckBox(QString::fromStdString(x + ": "));

		QHBoxLayout *layout = new QHBoxLayout();
		layout->addWidget(checkbox);
		layout->addStretch(1);

		details_layout->addLayout(layout);
		details.push_back(layout);
	}

	show();
}

AddOrderDialog::AddOrderDialog(const std::vector<std::string> &types, QWidget *parent):
	QDialog(parent),
	choose_type(new QButtonGroup()),
	details_layout(new QVBoxLayout())
{
	QVBoxLayout *main_layout = new QVBoxLayout();
	QHBoxLayout *table_layout = new QHBoxLayout();
	QGroupBox *type_box = new QGroupBox("Type");
	QGroupBox *details_box = new QGroupBox("Details");
	QGridLayout *type_layout = new QGridLayout();
	QHBoxLayout *details_layout = new QHBoxLayout();
	QHBoxLayout *buttons_layout = new QHBoxLayout();

	QLineEdit *table_input = new QLineEdit();
	table_input->setMaximumWidth(30);
	table_input->setValidator(new QIntValidator(0, 100));

	table_layout->addWidget(new QLabel("Table: "));
	table_layout->addWidget(table_input);
	table_layout->addStretch(1);

	int pos = 0;

	for (const auto &t : types)
	{
		QRadioButton *button = new QRadioButton(QString::fromStdString(t));
		type_layout->addWidget(button, pos / 2, pos % 2);
		choose_type->addButton(button);
		++pos;
	}

	connect(choose_type, QOverload<int>::of(&QButtonGroup::buttonClicked),
			this, &AddOrderDialog::setDetails);

	choose_type->buttons()[0]->toggle();

	QPushButton *ok = new QPushButton("Ok");
	QPushButton *cancel = new QPushButton("Cancel");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(ok);
	buttons_layout->addWidget(cancel);

	type_box->setLayout(type_layout);
	details_box->setLayout(details_layout);

	main_layout->addLayout(table_layout);
	main_layout->addWidget(type_box);
	main_layout->addWidget(details_box);
	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);
	show();

	connect(ok, &QPushButton::clicked,
			this, &AddOrderDialog::accept);

	connect(cancel, &QPushButton::clicked,
			this, &AddOrderDialog::reject);
}
