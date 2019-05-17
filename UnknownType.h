#ifndef UNKNOWNTYPE_H
#define UNKNOWNTYPE_H
#include <stdexcept>

class UnknownType: public std::invalid_argument
{
public:
	UnknownType(const std::string &what_arg);
};

#endif // UNKNOWNTYPE_H