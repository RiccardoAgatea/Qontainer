#include "SearchView.h"
#include "SearchDialog.h"
#include "OrderWidget.h"
#include <QAction>
#include <QToolBar>
#include <QScrollArea>
#include <QLabel>

SearchView::SearchView(QWidget *parent):
	QDialog(parent),
	results_layout(new QVBoxLayout)
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
		results_layout->addWidget(new QLabel("POTATOES"));
		return true;
	}
	else
		return false;
}

int SearchView::exec()
{
	return filter() ? QDialog::exec() : 0;
}
