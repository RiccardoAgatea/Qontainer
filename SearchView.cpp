#include "SearchView.h"
#include "SearchDialog.h"
#include "OrderWidget.h"
#include "Model.h"
#include <QAction>
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

	QVBoxLayout *main_layout = new QVBoxLayout;
	QScrollArea *scroll_area = new QScrollArea;
	QWidget *widget = new QWidget;
	results_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	results_layout->addStretch(1);
	widget->setLayout(results_layout);
	scroll_area->setWidget(widget);
	widget->setFixedWidth(475);
	scroll_area->setWidgetResizable(false);
	scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	main_layout->addWidget(scroll_area);

	setLayout(main_layout);
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

				connect(order, &OrderWidget::remove,
						this, [this](OrderWidget * o)
				{
					o->hide();
					results_layout->removeWidget(o);

					removed.push_back(o->getOrder());
					delete o;
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
