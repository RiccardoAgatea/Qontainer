#include <QApplication>
#include "View.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	View v;

	v.show();
	return a.exec();
}
