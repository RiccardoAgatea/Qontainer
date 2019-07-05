#include "InvalidFile.h"

InvalidFile::InvalidFile(const std::string &what_arg):
	std::invalid_argument(what_arg)
{

}
