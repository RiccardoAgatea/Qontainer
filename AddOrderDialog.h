#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLineEdit>
#include <QDialog>
#include <QString>
#include <string>
#include <vector>

class AddOrderDialog: public QDialog
{
	Q_OBJECT
private:
	QLineEdit *table_input;
	QLineEdit *item_input;
	QButtonGroup *choose_type;
	QGroupBox *details_box;
	QVBoxLayout *details_layout;
	QString recap;
private slots:
	void setDetails();
public:
	explicit AddOrderDialog(const std::vector<std::string> &,
							QWidget * = nullptr);
	void accept() override;
	QSize sizeHint() const override;
	QString getRecap() const;

signals:

public slots:
};

#endif // ADDORDERDIALOG_H