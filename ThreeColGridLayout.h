#ifndef THREECOLGRIDLAYOUT_H
#define THREECOLGRIDLAYOUT_H

#include <QGridLayout>
//see what to to do with this...

class ThreeColGridLayout: public QGridLayout
{
	Q_OBJECT
private:
	int position;
public:
	explicit ThreeColGridLayout(QWidget * = nullptr);


signals:

public slots:
};

#endif // THREECOLGRIDLAYOUT_H