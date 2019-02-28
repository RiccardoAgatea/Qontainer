#ifndef UNKNOWNTYPE_H
#define UNKNOWNTYPE_H
#include <stdexcept>

/**
 * @brief      Exception class for a translation from an invalid string to the
 *             relative type
 */
class UnknownType: public std::invalid_argument
{
public:
	UnknownType(const std::string &what_arg);
};

#endif // UNKNOWNTYPE_H