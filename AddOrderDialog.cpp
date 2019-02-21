#include "AddOrderDialog.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QString>

/**
 * @brief      Builds the details part of the window depending on the type
 *             that's selected
 */
void AddOrderDialog::setDetails()
{
	QString type = choose_type->checkedButton()->text();
	PolyStatic::Info info = PolyStatic::getInfo(type.toStdString());

	while (!details_layout->isEmpty())
	{
		QLayoutItem *item = details_layout->takeAt(0);

		if (item->widget() != nullptr)
			delete item->widget();
		else if (item->layout() != nullptr)
		{
			while (!item->layout()->isEmpty())
			{
				QLayoutItem *it = item->layout()->takeAt(0);

				delete it->widget();
				delete it;
			}

			delete item;
		}
	}

	for (auto &x : info.long_texts)
	{
		QLabel *label = new QLabel(QString::fromStdString(x + ": "),
		                           details_box);
		QLineEdit *line_edit = new QLineEdit(details_box);
		line_edit->setMinimumSize(100, 75);

		QHBoxLayout *layout = new QHBoxLayout();
		layout->addWidget(label);
		layout->addWidget(line_edit);
		layout->addStretch(1);

		details_layout->addLayout(layout);

		label->show();
		line_edit->show();
	}

	for (auto &x : info.short_texts)
	{
		QLabel *label = new QLabel(QString::fromStdString(x + ": "),
		                           details_box);
		QLineEdit *line_edit = new QLineEdit(details_box);
		line_edit->setMinimumWidth(100);

		QHBoxLayout *layout = new QHBoxLayout();
		layout->addWidget(label);
		layout->addWidget(line_edit);
		layout->addStretch(1);

		details_layout->addLayout(layout);

		label->show();
		line_edit->show();
	}

	for (auto &x : info.checks)
	{
		QCheckBox *checkbox = new QCheckBox(QString::fromStdString(x),
		                                    details_box);

		QHBoxLayout *layout = new QHBoxLayout();
		layout->addWidget(checkbox);
		layout->addStretch(1);

		details_layout->addLayout(layout);

		checkbox->show();
	}
}

/**
 * @brief      Constructor
 *
 * @param[in]  types   Vector containing all the types of order that can be
 *                     created.
 * @param      parent  The parent widget.
 */
AddOrderDialog::AddOrderDialog(const QVector<QString> &types,
							   QWidget *parent):
	QDialog(parent),
	table_input(new QLineEdit()),
	item_input(new QLineEdit()),
	choose_type(new QButtonGroup()),
	details_box(new QGroupBox("Details")),
	details_layout(new QVBoxLayout())
{
	setWindowModality(Qt::ApplicationModal);
	setMinimumSize(sizeHint());

	QVBoxLayout *main_layout = new QVBoxLayout();
	QHBoxLayout *table_layout = new QHBoxLayout();
	QHBoxLayout *item_layout = new QHBoxLayout();
	QGroupBox *type_box = new QGroupBox("Type");
	QGridLayout *type_layout = new QGridLayout();
	QHBoxLayout *buttons_layout = new QHBoxLayout();

	table_input->setMaximumWidth(30);
	table_input->setValidator(new QIntValidator(0, 100));

	table_layout->addWidget(new QLabel("Table: "));
	table_layout->addWidget(table_input);
	table_layout->addStretch(1);

	item_layout->addWidget(new QLabel("Item: "));
	item_layout->addWidget(item_input);
	item_layout->addStretch(1);

	int pos = 0;

	for (const auto &t : types)
	{
		QRadioButton *button = new QRadioButton(t);
		type_layout->addWidget(button, pos / 2, pos % 2);
		choose_type->addButton(button);
		++pos;
	}

	connect(choose_type, QOverload<int>::of(&QButtonGroup::buttonClicked),
	        this, &AddOrderDialog::setDetails);

	choose_type->buttons()[0]->click();

	QPushButton *ok = new QPushButton("Ok");
	QPushButton *cancel = new QPushButton("Cancel");
	buttons_layout->addStretch(1);
	buttons_layout->addWidget(ok);
	buttons_layout->addWidget(cancel);

	type_box->setLayout(type_layout);
	details_box->setLayout(details_layout);

	main_layout->addLayout(table_layout);
	main_layout->addLayout(item_layout);
	main_layout->addWidget(type_box);
	main_layout->addWidget(details_box);
	main_layout->addStretch(1);
	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);
	show();

	connect(ok, &QPushButton::clicked,
	        this, &AddOrderDialog::accept);

	connect(cancel, &QPushButton::clicked,
	        this, &AddOrderDialog::reject);
}

/**
 * @brief      Override of QDialog::sizeHint()
 *
 * @return     A QSize representing the preferred size of the window.
 */
QSize AddOrderDialog::sizeHint() const
{
	return QSize(250, 415);
}

QString AddOrderDialog::getType() const
{
	return choose_type->checkedButton()->text();
}

unsigned int AddOrderDialog::getTable() const
{
	return table_input->text().toUInt();
}

QString AddOrderDialog::getItem() const
{
	return item_input->text();
}

QVector<QString> AddOrderDialog::getDetails() const
{
	QVector<QString> aux;

}
