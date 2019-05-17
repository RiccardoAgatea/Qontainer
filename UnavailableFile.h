#ifndef UNAVAILABLEFILE_H
#define UNAVAILABLEFILE_H
#include <stdexcept>

class UnavailableFile: public std::invalid_argument
{
public:
	UnavailableFile(const std::string &);
};

#endif // UNAVAILABLEFILE_H