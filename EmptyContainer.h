#ifndef EMPTYCONTAINER_H
#define EMPTYCONTAINER_H
#include <stdexcept>

class EmptyContainer: public std::logic_error
{
public:
	EmptyContainer(const std::string &);
};

#endif // EMPTYCONTAINER_H