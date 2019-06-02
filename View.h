#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>
#include <QVBoxLayout>

class Model;

class View : public QMainWindow
{
	Q_OBJECT
private:
	Model *model;
	QVBoxLayout *lineup_layout;
public:
	explicit View(QWidget *parent = nullptr);
	QSize sizeHint() const override;

signals:

public slots:
	void addOrder();
	void save();
	void load();
};

#endif // VIEW_H