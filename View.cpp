#include "View.h"
#include "Controller.h"
#include "AddOrderDialog.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QToolBar>
#include <QFileDialog>
#include <QScrollArea>

View::View(QWidget *parent):
	QMainWindow(parent),
	controller(new Controller(this)),
	lineup_layout(new QVBoxLayout()),
	completed_layout(new QVBoxLayout())
{
	move(25, 25);

	//Menu
	QMenu *file_menu = new QMenu("File");
	QAction *save_action = new QAction("Save");
	QAction *load_action = new QAction("Load");
	QAction *exit_action = new QAction("Exit");

	menuBar()->addMenu(file_menu);
	file_menu->addAction(save_action);
	file_menu->addAction(load_action);
	file_menu->addAction(exit_action);

	connect(save_action, &QAction::triggered,
	        this, &View::save);

	connect(load_action, &QAction::triggered,
	        this, &View::load);

	connect(exit_action, &QAction::triggered,
	        this, &View::close);

	//ToolBar
	QToolBar *tool_bar = new QToolBar();
	QAction *add_order_action = new QAction("Add Order");
	tool_bar->addAction(add_order_action);
	tool_bar->addAction(save_action);
	tool_bar->addAction(load_action);

	addToolBar(tool_bar);

	connect(add_order_action, &QAction::triggered,
	        this, &View::newOrder);

	//Tabs
	QTabWidget *tab_widget = new QTabWidget();
	QScrollArea *lineup_scroll_area = new QScrollArea;
	QScrollArea *completed_scroll_area = new QScrollArea;
	lineup_scroll_area->setLayout(lineup_layout);
	completed_scroll_area->setLayout(completed_layout);
	tab_widget->addTab(lineup_scroll_area, "Lineup");
	tab_widget->addTab(completed_scroll_area, "Completed Orders");
	setCentralWidget(tab_widget);
}

QSize View::sizeHint() const
{
	return QSize(1000, 750);
}

void View::newOrder()
{
	AddOrderDialog *dial = new AddOrderDialog(this);

	if (dial->exec())
	{
		OrderWidget *aux = new OrderWidget(
			controller->addOrder(
				dial->getType(),
				dial->getTable(),
				dial->getItem(),
				dial->getDetails()
			)
		);
		lineup_layout->addWidget(aux);
		aux->show();
	}
}

void View::removeOrder(OrderWidget *o)
{
	lineup_layout->removeWidget(o);
	completed_layout->removeWidget(o);
	delete o;
}

void View::completeOrder(OrderWidget *o)
{
	lineup_layout->removeWidget(o);
	completed_layout->addWidget(o);
}

void View::load()
{
	bool act = true;

	if (!controller->isModelEmpty())
	{
		QMessageBox overwrite;
		overwrite.setText("The order lineup is not empty!");
		overwrite.setInformativeText("Do you want to overwrite the lineup, loading a new one from a file?");
		overwrite.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		overwrite.setDefaultButton(QMessageBox::Cancel);

		act = overwrite.exec();
	}

	if (act)
	{
		QMessageBox disclaimer;
		disclaimer.setText("Select the file from which to load the unfinished orders.");
		disclaimer.setInformativeText("If present, a corresponding file for completed orders will be selected.");
		disclaimer.exec();

		QFileDialog choose;
		choose.setFileMode(QFileDialog::ExistingFile);
		choose.setWindowTitle("Load Lineup");
		choose.setNameFilter("Lineup file (*.lnp)");

		if (choose.exec())
			controller->load(choose.selectedFiles()[0]);
	}
}

void View::save()
{
	QMessageBox disclaimer;
	disclaimer.setText("Indicate the name of the file for the unfinished orders.");
	disclaimer.setInformativeText("A corresponding file for completed orders will be generated.");
	disclaimer.exec();

	QFileDialog choose;
	choose.setFileMode(QFileDialog::AnyFile);
	choose.setWindowTitle("Save Lineup");
	choose.setNameFilter("Lineup file (*.lnp)");

	if (choose.exec())
		controller->save(choose.selectedFiles()[0]);
}
