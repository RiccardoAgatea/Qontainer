#include "Wine.h"


std::string Wine::getType() const
{
	return "wine";
}

Wine::Wine(unsigned int t, const std::string &i, unsigned int y):
	Alcoholic(t, i),
	year(y)
{

}
