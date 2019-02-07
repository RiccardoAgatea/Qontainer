#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLineEdit>
#include <QDialog>
#include <QLinkedList>
#include <string>
#include <vector>

class AddOrderDialog: public QDialog
{
	Q_OBJECT
private:
	QButtonGroup *choose_type;
	QVBoxLayout *details_layout;
	QLinkedList<QLayout *> details;
private slots:
	void setDetails();
public:
	explicit AddOrderDialog(const std::vector<std::string> &, QWidget * = nullptr);

signals:

public slots:
};

#endif // ADDORDERDIALOG_H