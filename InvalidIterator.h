#ifndef INVALIDITERATOR_H
#define INVALIDITERATOR_H
#include <stdexcept>

class InvalidIterator: public std::logic_error
{
public:
	InvalidIterator(const std::string &);
	InvalidIterator(const char *);
};

#endif // INVALIDITERATOR_H