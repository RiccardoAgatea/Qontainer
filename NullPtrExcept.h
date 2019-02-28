#ifndef NULLPTREXCEPT_H
#define NULLPTREXCEPT_H
#include <stdexcept>

/**
 * @brief      Exception class for dereferenciation of a null pointer
 */
class NullPtrExcept: public std::logic_error
{
public:
	NullPtrExcept(const std::string &);
};

#endif // NULLPTREXCEPT_H