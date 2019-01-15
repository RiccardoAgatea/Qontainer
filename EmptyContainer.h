#ifndef EMPTYCONTAINER_H
#define EMPTYCONTAINER_H
#include <stdexcept>

class EmptyContainer: public std::logic_error
{
public:
    EmptyContainer(const std::string &what_arg);
    EmptyContainer(const char *what_arg);
};

#endif // EMPTYCONTAINER_H