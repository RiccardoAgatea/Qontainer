#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "Order.h"
#include <QDialog>
#include <QLineEdit>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QCheckBox>
#include <functional>

class SearchDialog: public QDialog
{
	Q_OBJECT
private:
	QCheckBox *incompleted_check;
	QCheckBox *completed_check;
	QLineEdit *table_line_edit;
	QLineEdit *item_line_edit;
	QLineEdit *quantity_line_edit;
	QButtonGroup *abstracts_group;
	QButtonGroup *concretes_group;
	QVBoxLayout *details_layout;

	static void showRecursively(QLayout *);
	static void hideRecursively(QLayout *);
public:
	explicit SearchDialog(QWidget *parent = nullptr);
	bool includeToDo() const;
	bool includeCompleted() const;
	std::function<bool(const Order &)> checker() const;

signals:

public slots:
};

#endif // SEARCHDIALOG_H