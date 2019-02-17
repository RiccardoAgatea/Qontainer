#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "Model.h"
#include <QString>
#include <string>
#include <vector>

class View;

/**
 * @brief      Acts as interface and filter between the Model and the View
 */
class Controller: public QWidget
{
	Q_OBJECT
private:
	Model *model;
	View *view;
public:
	explicit Controller(View *);
	bool isModelEmpty() const;
	void load(const QString &);
	void save(const QString &) const;
	void addOrder(const QString &,
	              unsigned int,
	              const QString &,
	              const QString &);

	static const std::vector<std::string> getTypes();

signals:

public slots:
};

#endif // CONTROLLER_H