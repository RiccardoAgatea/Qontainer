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
	Model *model;
public:
	explicit SearchView(Model *, QWidget * = nullptr);
	QSize sizeHint() const override;
	bool filter();

signals:

public slots:
	int exec() override;
};

#endif // SEARCHVIEW_H