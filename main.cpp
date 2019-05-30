#include <QApplication>
#include "View.h"

#include "Order.h"
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	View v;

	qDebug() << "start\n";
	std::vector<std::string> vec = Order::getTypes();

	qDebug() << "size: " << vec.size() << "\n";

	for (auto &x : vec)
		qDebug() << x.c_str() << "\n";

	qDebug() << "end\n";

	v.show();
	return a.exec();
}
