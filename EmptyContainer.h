#ifndef EMPTYCONTAINER_H
#define EMPTYCONTAINER_H
#include <stdexcept>

/**
 * @brief      Exception class for calls from an empty Container object of
 *             methods that require a non-empty Container
 */
class EmptyContainer: public std::logic_error
{
public:
	EmptyContainer(const std::string &);
};

#endif // EMPTYCONTAINER_H