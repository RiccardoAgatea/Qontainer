#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>

class Controller;

class View: public QMainWindow
{
	Q_OBJECT

private:
	Controller *controller;

	void createTabs();
public:
	explicit View(QWidget * = nullptr);
	QSize sizeHint() const override;

signals:

public slots:
	void newOrder();
	void load();
	void save();
};

#endif // VIEW_H