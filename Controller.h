#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "Model.h"
#include <QString>
#include <QVector>
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
	struct Info
	{
		QVector<QString> long_texts;
		QVector<QString> short_texts;
		QVector<QString> checks;
	};
	explicit Controller(View *);
	bool isModelEmpty() const;
	void load(const QString &);
	void save(const QString &) const;
	void addOrder(const QString &,
	              unsigned int,
	              const QString &,
				  const QVector<QString> &);

	static QVector<QString> getTypes();
	static Controller::Info getInfo(const QString &);
signals:

public slots:
};

#endif // CONTROLLER_H