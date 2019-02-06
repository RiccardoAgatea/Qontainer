#include "AddOrderDialog.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>

AddOrderDialog::AddOrderDialog(QWidget *parent):
	QDialog(parent)
{
	QVBoxLayout *add_layout = new QVBoxLayout();
	QHBoxLayout *table_layout = new QHBoxLayout();
	QGroupBox *choose_type = new QGroupBox("Type");
	QGroupBox *details = new QGroupBox("Details");

	QLineEdit *table_input = new QLineEdit();
	table_input->setValidator(new QIntValidator(0, 100));

	table_layout->addWidget(new QLabel("Table: "));
	table_layout->addWidget(table_input);

	add_layout->addLayout(table_layout);
	add_layout->addWidget(choose_type);
	add_layout->addWidget(details);

	setLayout(add_layout);
}
