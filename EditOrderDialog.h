#ifndef EDITORDERDIALOG_H
#define EDITORDERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>

class EditOrderDialog: public QDialog
{
	Q_OBJECT
private:
	QLineEdit *quantity_line_edit;
	QVBoxLayout *details_layout;
public:
	explicit EditOrderDialog(const std::string &,
							 unsigned int,
							 const std::vector<std::string> &,
							 QWidget * = nullptr);
	unsigned int getQuantity() const;
	std::vector<std::string> getDetails() const;

signals:

public slots:
};

#endif // EDITORDERDIALOG_H