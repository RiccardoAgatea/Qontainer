#include <QApplication>
#include "Container.h"
#include "Ordinazione.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Container<Ordinazione> con_def;

	return a.exec();
}
