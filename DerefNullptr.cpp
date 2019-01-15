#include "DerefNullptr.h"

DerefNullptr::DerefNullptr(const std::string &what_arg):
    std::logic_error(what_arg)
{

}

DerefNullptr::DerefNullptr(const char *what_arg):
    std::logic_error(what_arg)
{

}
