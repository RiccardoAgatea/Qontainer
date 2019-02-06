#include "View.h"
#include "Controller.h"
#include "AddOrderDialog.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QScrollArea>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QToolBar>

void View::createTabs()
{
	//Tabs: general
	QScrollArea *general = new QScrollArea();

	//Tabs: bar
	QScrollArea *bar = new QScrollArea();

	//Tabs: desserts
	QScrollArea *desserts = new QScrollArea();

	//Tabs
	QTabWidget *tabs = new QTabWidget();
	tabs->addTab(general, "General");
	tabs->addTab(bar, "Bar");
	tabs->addTab(desserts, "Desserts");
	setCentralWidget(tabs);
}

View::View(QWidget *parent):
	QMainWindow(parent),
	controller(new Controller(this))
{
	resize(750, 500);

	//Menu
	QMenu *file = new QMenu("File");
	QAction *save = new QAction("Save");
	QAction *load = new QAction("Load");
	QAction *exit = new QAction("Exit");

	menuBar()->addMenu(file);
	file->addAction(save);
	file->addAction(load);
	file->addAction(exit);

	connect(exit, &QAction::triggered,
			this, &View::close);

	//ToolBar
	QToolBar *tools = new QToolBar();
	QAction *add_order = new QAction("Add Order");
	tools->addAction(add_order);

	addToolBar(tools);

	connect(add_order, &QAction::triggered,
			[]()
	{
		AddOrderDialog dial;
		dial.exec();
	});

	//Tabs
	createTabs();
}
