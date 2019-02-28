#ifndef INVALIDITERATOR_H
#define INVALIDITERATOR_H
#include <stdexcept>

/**
 * @brief      Exception class for methods that require a valid or deferenceable
 *             iterator
 */
class InvalidIterator: public std::logic_error
{
public:
	InvalidIterator(const std::string &);
};

#endif // INVALIDITERATOR_H