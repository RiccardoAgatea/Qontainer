#include "Controller.h"
#include "View.h"

Controller::Controller(View *v):
	QWidget(v),
	model(nullptr),
	view(v)
{

}
