#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLineEdit>
#include <QDialog>
#include <functional>

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
	QVBoxLayout *details_layout_long; //a layout for long texts
	QVBoxLayout *details_layout_short; //a layout for short texts
	QVBoxLayout *details_layout_check; //a layout for checkboxes

	std::function<QVector<QVector<QString>>(const QString &)> getInfo;
private slots:
	void setDetails();
public:
	explicit AddOrderDialog(const QVector<QString> &,
							const std::function<QVector<QVector<QString>>(const QString &)> &,
							QWidget * = nullptr);
	QSize sizeHint() const override;
	QString getType() const;
	unsigned int getTable() const;
	QString getItem() const;
	QVector<QVector<QString>> getDetails() const;

signals:

public slots:
};

#endif // ADDORDERDIALOG_H