#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H
#include <QDialog>
#include "Order.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QButtonGroup>

class AddOrderDialog: public QDialog
{
	Q_OBJECT
private:
	QLineEdit *table_line_edit;
	QLineEdit *item_line_edit;
	QLineEdit *quantity_line_edit;
	QButtonGroup *types_group;
	QVBoxLayout *details_layout;
private slots:
	void setup();
public:
	explicit AddOrderDialog(QWidget * = nullptr);
	QSize sizeHint() const;
	QString getType() const;
	unsigned int getTable() const;
	QString getItem() const;
	unsigned int getQuantity() const;
	std::vector<std::string> getDetails() const;

signals:

public slots:
};

#endif // ADDORDERDIALOG_H