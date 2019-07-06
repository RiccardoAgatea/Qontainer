#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include "OrderWidget.h"

class SearchView: public QDialog
{
	Q_OBJECT
private:
	QVBoxLayout *results_layout;
	Model *model;
	std::vector<Model::Index> removed;
	std::vector<Model::Index> completed;
public:
	explicit SearchView(Model *, QWidget * = nullptr);
	QSize sizeHint() const override;
	bool filter();
	std::vector<Model::Index> getRemovedOrders() const;
	std::vector<Model::Index> getCOmpletedOrders() const;

signals:
	void removeAll();
	void completeAll();

public slots:
	int exec() override;
};

#endif // SEARCHVIEW_H