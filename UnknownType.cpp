#include "UnknownType.h"

UnknownType::UnknownType(const std::string &what_arg):
	std::invalid_argument(what_arg)
{

}
