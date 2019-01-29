#include "UnavailableFile.h"

UnavailableFile::UnavailableFile(const std::string &what_arg):
	std::invalid_argument(what_arg)
{

}
