#include "InvalidIterator.h"


InvalidIterator::InvalidIterator(const std::string &what_arg):
	std::logic_error (what_arg)
{

}
