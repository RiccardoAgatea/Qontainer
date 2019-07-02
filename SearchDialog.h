#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QButtonGroup>
#include <QVBoxLayout>

class SearchDialog: public QDialog
{
	Q_OBJECT
private:
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

signals:

public slots:
};

#endif // SEARCHDIALOG_H