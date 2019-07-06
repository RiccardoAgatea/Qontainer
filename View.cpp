#include "View.h"
#include "Model.h"
#include "AddOrderDialog.h"
#include "SearchView.h"
#include "UnavailableFile.h"
#include "InvalidFile.h"
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QMenuBar>
#include <QFileDialog>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>
#include <QtDebug>

void View::update()
{
	while (lineup_layout->count() != 0)
	{
		auto item = lineup_layout->takeAt(0);
		delete item->widget();
		delete item;
	}

	for (auto &i : model->getUnfinishedOrders())
	{
		OrderWidget *order = new OrderWidget(i);

		lineup_layout->addWidget(order);

		connect(order, &OrderWidget::remove,
				this, &View::removeOrder);

		connect(order, &OrderWidget::complete,
				this, &View::completeOrder);
	}

	lineup_layout->addStretch(1);

	show();
}

View::View(QWidget *parent):
	QMainWindow(parent),
	model(new Model),
	lineup_layout(new QVBoxLayout)
{
	setMinimumWidth(500);
	setMaximumWidth(500);
	setWindowIcon(QIcon(":/icon/Main"));

	QAction *save_action = new QAction(QIcon(":/icon/Save"), "Save");
	QAction *load_action = new QAction(QIcon(":/icon/Load"), "Load");
	QAction *exit_action = new QAction("Exit");
	QAction *add_order_action = new QAction(QIcon(":/icon/AddOrder"),
											"Add Order");
	QAction *search_action = new QAction(QIcon(":/icon/Search"),
										 "Search");

	QMenu *file_menu = new QMenu("File");
	file_menu->addAction(save_action);
	file_menu->addAction(load_action);
	file_menu->addAction(exit_action);
	menuBar()->addMenu(file_menu);

	QToolBar *tool_bar = new QToolBar;
	tool_bar->addAction(save_action);
	tool_bar->addAction(load_action);
	tool_bar->addAction(add_order_action);
	tool_bar->addAction(search_action);
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
	connect(search_action, &QAction::triggered,
			this, &View::search);
}

QSize View::sizeHint() const
{
	return QSize(500, 750);
}

void View::search()
{
	SearchView search(model);

	search.exec();

	for (auto o : search.getRemovedOrders())
		for (int i = 0; i < lineup_layout->count() - 1; ++i)
		{
			auto order = static_cast<OrderWidget *>
						 (lineup_layout->itemAt(i)->widget());

			if (order->getOrder() == o)
			{
				removeOrder(order);
				break; //breaks most internal loop
			}
		}

	for (auto o : search.getCOmpletedOrders())
		for (int i = 0; i < lineup_layout->count() - 1; ++i)
		{
			auto order = static_cast<OrderWidget *>
						 (lineup_layout->itemAt(i)->widget());

			if (order->getOrder() == o)
			{
				completeOrder(order);
				break; //breaks most internal loop
			}
		}

	for (int i = 0; i < lineup_layout->count() - 1; ++i)
		emit static_cast<OrderWidget *>
		(lineup_layout->itemAt(i)->widget())->update();
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
	{
		try
		{
			QString path = choose.selectedFiles()[0];
			model->save(path + (path.endsWith(".xml") ? "" : ".xml"));
		}
		catch (UnavailableFile &)
		{
			QMessageBox msg;
			msg.setText("Couldn't open the requested file");
			msg.exec();
		}
	}
}

void View::load()
{
	QFileDialog choose;

	choose.setFileMode(QFileDialog::ExistingFile);
	choose.setOption(QFileDialog::DontConfirmOverwrite);
	choose.setOption(QFileDialog::ReadOnly);
	choose.setWindowTitle("Load Lineup");
	choose.setNameFilter("XML file (*.xml)");

	if (choose.exec())
	{
		try
		{
			model->load(choose.selectedFiles()[0]);
			update();
		}
		catch (UnavailableFile &)
		{
			QMessageBox msg;
			msg.setText("Couldn't open the requested file");
			msg.exec();
		}
		catch (InvalidFile &)
		{
			QMessageBox msg;
			msg.setText("The requested file isn't a suitable save file for this application");
			msg.exec();
		}
	}
}
