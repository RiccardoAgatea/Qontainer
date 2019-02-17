#include "NullPtrExcept.h"

NullPtrExcept::NullPtrExcept(const std::string &what_arg):
	std::logic_error(what_arg)
{

}
