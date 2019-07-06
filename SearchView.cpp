#include "SearchView.h"
#include "SearchDialog.h"
#include "OrderWidget.h"
#include "Model.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QToolBar>
#include <QScrollArea>
#include <QLabel>
#include <QDebug>

SearchView::SearchView(Model *m, QWidget *parent):
	QDialog(parent),
	results_layout(new QVBoxLayout),
	model(m)
{
	setMinimumWidth(500);
	setMaximumWidth(500);
	setWindowTitle("Search Results");
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowIcon(QIcon(":/icon/search"));

	QVBoxLayout *main_layout = new QVBoxLayout;

	QHBoxLayout *edit_all_layout = new QHBoxLayout;
	QPushButton *remove_all = new QPushButton(QIcon(":/icon/Remove"),
			"Remove All");
	QPushButton *complete_all = new QPushButton(QIcon(":/icon/Complete"),
			"Complete All");
	edit_all_layout->addWidget(complete_all);
	edit_all_layout->addWidget(remove_all);
	edit_all_layout->addStretch(1);

	QScrollArea *scroll_area = new QScrollArea;
	QWidget *widget = new QWidget;
	results_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	widget->setLayout(results_layout);
	scroll_area->setWidget(widget);
	widget->setFixedWidth(475);
	scroll_area->setWidgetResizable(false);
	scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	main_layout->addLayout(edit_all_layout);
	main_layout->addWidget(scroll_area);

	setLayout(main_layout);

	connect(remove_all, &QPushButton::clicked,
			this, [this]()
	{
		QMessageBox msg;

		msg.setWindowIcon(QIcon(":/icon/Warning"));
		msg.setText("Are you sure you want to remove all the selected orders?");
		msg.setIcon(QMessageBox::Warning);
		msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		msg.setDefaultButton(QMessageBox::Cancel);

		if (msg.exec() == QMessageBox::Ok)
			emit removeAll();
	});

	connect(complete_all, &QPushButton::clicked,
			this, [this]()
	{
		QMessageBox msg;

		msg.setWindowIcon(QIcon(":/icon/Warning"));
		msg.setText("Are you sure you want to complete all the selected orders?");
		msg.setIcon(QMessageBox::Warning);
		msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		msg.setDefaultButton(QMessageBox::Cancel);

		if (msg.exec() == QMessageBox::Ok)
			emit completeAll();
	});
}

QSize SearchView::sizeHint() const
{
	return QSize(500, 650);
}

bool SearchView::filter()
{
	SearchDialog opt;

	if (opt.exec())
	{
		if (opt.includeToDo())
		{
			auto results = model->searchToDo(opt.checker());

			for (auto &x : results)
			{
				OrderWidget *order = new OrderWidget(x);
				results_layout->addWidget(order);

				connect(this, &SearchView::removeAll,
						order, [order]()
				{
					emit order->remove(order);
				});

				connect(order, &OrderWidget::remove,
						this, [this](OrderWidget * o)
				{
					o->hide();
					results_layout->removeWidget(o);

					removed.push_back(o->getOrder());
					delete o;
				});

				connect(this, &SearchView::completeAll,
						order, [order]()
				{
					emit order->complete(order);
				});

				connect(order, &OrderWidget::complete,
						this, [this](OrderWidget * o)
				{
					o->hide();
					results_layout->removeWidget(o);

					completed.push_back(o->getOrder());
					delete o;
				});
			}
		}

		if (opt.includeCompleted())
		{
			auto results = model->searchCompleted(opt.checker());

			for (auto &x : results)
			{
				OrderWidget *order = new OrderWidget(x, true);
				results_layout->addWidget(order);
			}
		}

		results_layout->addStretch(1);

		show();

		return true;
	}
	else
		return false;
}

std::vector<Model::Index> SearchView::getRemovedOrders() const
{
	return removed;
}

std::vector<Model::Index> SearchView::getCOmpletedOrders() const
{
	return completed;
}

int SearchView::exec()
{
	return filter() ? QDialog::exec() : 0;
}
