#include "EmptyContainer.h"


EmptyContainer::EmptyContainer(const std::string &what_arg):
	std::logic_error(what_arg)
{

}

EmptyContainer::EmptyContainer(const char *what_arg):
	std::logic_error(what_arg)
{

}
