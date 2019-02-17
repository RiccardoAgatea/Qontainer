#ifndef NULLPTREXCEPT_H
#define NULLPTREXCEPT_H
#include <stdexcept>

class NullPtrExcept: public std::logic_error
{
public:
	NullPtrExcept(const std::string &);
};

#endif // NULLPTREXCEPT_H