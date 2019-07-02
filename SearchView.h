#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QDialog>
#include <QVBoxLayout>
#include "OrderWidget.h"

class SearchView: public QDialog
{
	Q_OBJECT
private:
	QVBoxLayout *results_layout;
public:
	explicit SearchView(QWidget *parent = nullptr);
	QSize sizeHint() const override;
	bool filter();

signals:

public slots:
	int exec() override;
};

#endif // SEARCHVIEW_H