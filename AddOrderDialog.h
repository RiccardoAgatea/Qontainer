#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H
#include <QDialog>
#include "StaticOrder.h"
#include <QVBoxLayout>
#include <QButtonGroup>

class AddOrderDialog: public QDialog
{
	Q_OBJECT
private:
	QVBoxLayout *details_layout;
	QButtonGroup *types_group;
private slots:
	void setup();
public:
	explicit AddOrderDialog(QWidget * = nullptr);
	QSize sizeHint() const;

signals:

public slots:
};

#endif // ADDORDERDIALOG_H