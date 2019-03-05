#include "View.h"
#include "Controller.h"
#include "AddOrderDialog.h"
#include <QMessageBox>
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
#include <QFileDialog>

/**
 * @brief      Creates the tabs that compose the main widget of the window
 */
void View::createTabs()
{
	//Tabs: general
	QScrollArea *general = new QScrollArea();

	//Tabs: bar
	QScrollArea *bar = new QScrollArea();

	//Tabs: desserts
	QScrollArea *desserts = new QScrollArea();

	//Tabs: completed
	QScrollArea *completed = new QScrollArea();

	//Tabs
	QTabWidget *tabs = new QTabWidget();
	tabs->addTab(general, "General");
	tabs->addTab(bar, "Bar");
	tabs->addTab(desserts, "Desserts");
	tabs->addTab(completed, "Completed Orders");
	setCentralWidget(tabs);
}

/**
 * @brief      Constructor for the main window of the View.
 *
 * @param      parent  The parent widget.
 *
 * @details    The main window is composed of a menu bar, a tool bar and a tab
 *             system that manages (from a visual point of view) the orders in
 *             the queue.
 */
View::View(QWidget *parent):
	QMainWindow(parent),
	controller(new Controller(this))
{
	move(25, 25);

	//Menu
	QMenu *file = new QMenu("File");
	QAction *save = new QAction("Save");
	QAction *load = new QAction("Load");
	QAction *exit = new QAction("Exit");

	menuBar()->addMenu(file);
	file->addAction(save);
	file->addAction(load);
	file->addAction(exit);

	connect(save, &QAction::triggered,
	        this, &View::save);

	connect(load, &QAction::triggered,
	        this, &View::load);

	connect(exit, &QAction::triggered,
	        this, &View::close);

	//ToolBar
	QToolBar *tools = new QToolBar();
	QAction *add_order = new QAction("Add Order");
	tools->addAction(add_order);
	tools->addAction(save);
	tools->addAction(load);

	addToolBar(tools);

	connect(add_order, &QAction::triggered,
	        this, &View::newOrder);

	//Tabs
	createTabs();
}

/**
 * @brief      Override of QMainWindow::sizeHint()
 *
 * @return     A QSize representing the preferred size of the window.
 */
QSize View::sizeHint() const
{
	return QSize(1000, 750);
}

/**
 * @brief      Adds an order to the respective tab(s)
 */
void View::newOrder()
{
	AddOrderDialog dial(Controller::getTypes(),
						&Controller::getInfo,
						this);
	dial.exec();

	controller->addOrder(dial.getType(),
						 dial.getTable(),
						 dial.getItem(),
						 dial.getDetails());
}

/**
 * @brief      Manages selection of a file from which to load an order lineup.
 */
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

/**
 * @brief      Manages selection of a file in which to save the current order lineup.
 */
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
