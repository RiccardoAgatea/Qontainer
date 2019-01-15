#ifndef INVALIDITERATOR_H
#define INVALIDITERATOR_H
#include <stdexcept>

class InvalidIterator: public std::logic_error
{
public:
	InvalidIterator(const std::string &what_arg);
	InvalidIterator(const char *what_arg);
};

#endif // INVALIDITERATOR_H