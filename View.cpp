#include "View.h"
#include "Model.h"
#include "AddOrderDialog.h"
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QMenuBar>
#include <QFileDialog>
#include <QScrollArea>
#include <QScrollBar>

View::View(QWidget *parent):
	QMainWindow(parent),
	model(new Model),
	lineup_layout(new QVBoxLayout)
{
	setMinimumWidth(500);
	setMaximumWidth(500);

	QAction *save_action = new QAction("Save");
	QAction *load_action = new QAction("Load");
	QAction *exit_action = new QAction("Exit");
	QAction *add_order_action = new QAction("Add Order");
	QAction *completed_action = new QAction("Completed Orders");

	QMenu *file_menu = new QMenu("File");
	file_menu->addAction(save_action);
	file_menu->addAction(load_action);
	file_menu->addAction(exit_action);
	menuBar()->addMenu(file_menu);

	QToolBar *tool_bar = new QToolBar;
	tool_bar->addAction(save_action);
	tool_bar->addAction(load_action);
	tool_bar->addAction(add_order_action);
	tool_bar->addAction(completed_action);
	addToolBar(tool_bar);

	QScrollArea *scroll_area = new QScrollArea;
	QWidget *widget = new QWidget;
	lineup_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	lineup_layout->addStretch(1);
	widget->setLayout(lineup_layout);
	scroll_area->setWidget(widget);
	widget->setFixedWidth(475);
	scroll_area->setWidgetResizable(false);
	scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setCentralWidget(scroll_area);

	connect(exit_action, &QAction::triggered,
			this, &View::close);
	connect(save_action, &QAction::triggered,
			this, &View::save);
	connect(load_action, &QAction::triggered,
			this, &View::load);
	connect(add_order_action, &QAction::triggered,
			this, &View::addOrder);
	//connect(completed_action, &QAction::triggered,
	//		this, &View::addOrder);
}

QSize View::sizeHint() const
{
	return QSize(500, 750);
}

void View::addOrder()
{
	AddOrderDialog add;

	if (add.exec())
	{
		OrderWidget *order = new OrderWidget(
			model->addOrder(
				add.getType().toStdString(),
				add.getTable(),
				add.getItem().toStdString(),
				add.getQuantity(),
				add.getDetails()
			)
		);

		delete lineup_layout->takeAt(lineup_layout->count() - 1);
		lineup_layout->addWidget(order);
		lineup_layout->addStretch(1);

		connect(order, &OrderWidget::remove,
				this, &View::removeOrder);

		connect(order, &OrderWidget::complete,
				this, &View::completeOrder);
	}
}

void View::removeOrder(OrderWidget *o)
{
	lineup_layout->removeWidget(o);
	model->removeOrder(o->getOrder());
	delete o;
}

void View::completeOrder(OrderWidget *o)
{
	lineup_layout->removeWidget(o);
	model->completeOrder(o->getOrder());
	delete o;
}

void View::save()
{
	QFileDialog choose;

	choose.setFileMode(QFileDialog::AnyFile);
	choose.setWindowTitle("Save Lineup");
	choose.setNameFilter("XML file (*.xml)");

	if (choose.exec())
		model->save(choose.selectedFiles()[0].toStdString());
}

void View::load()
{
	QFileDialog choose;

	choose.setFileMode(QFileDialog::ExistingFile);
	choose.setWindowTitle("Load Lineup");
	choose.setNameFilter("XML file (*.xml)");

	if (choose.exec())
		model->load(choose.selectedFiles()[0].toStdString());
}
