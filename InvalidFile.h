#ifndef INVALIDFILE_H
#define INVALIDFILE_H

#include <stdexcept>

class InvalidFile: public std::invalid_argument
{
public:
	InvalidFile(const std::string &);
};

#endif // INVALIDFILE_H