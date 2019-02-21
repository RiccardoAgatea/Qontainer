#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLineEdit>
#include <QDialog>

/**
 * @brief      Provides a dialogue window for the insertion of a new Order in the queue
 */
class AddOrderDialog: public QDialog
{
	Q_OBJECT
private:
	QLineEdit *table_input;
	QLineEdit *item_input;
	QButtonGroup *choose_type;
	QGroupBox *details_box;
	QVBoxLayout *details_layout;
private slots:
	void setDetails();
public:
	explicit AddOrderDialog(const QVector<QString> &,
	                        QWidget * = nullptr);
	QSize sizeHint() const override;
	QString getType() const;
	unsigned int getTable() const;
	QString getItem() const;
	QVector<QString> getDetails() const;

signals:

public slots:
};

#endif // ADDORDERDIALOG_H