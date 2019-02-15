#include "Sandwich.h"
#include <utility>

/**
 * @brief      Reimplementation of Order::clone(). Standard polymorphic clone
 *             method, necessary to implement polymorphic copy construction.
 *
 * @return     a pointer to a copy of __*this__ on the heap.
 *
 * @details    The responsibility about the destruction of the constructed
 *             object is of the caller.
 */
Sandwich *Sandwich::clone() const
{
	return new Sandwich(*this);
}

/**
 * @brief      Reimplementation of Order::move(). Similar to the clone() method,
 *             necessary to implement polymorphic move construction.
 *
 * @return     A pointer to a copy of __*this__ on the heap.
 *
 * @details    The responsibility about the destruction of the constructed
 *             object is of the caller. After the call to move(), __*this__ is
 *             left in a valid but unspecified state.
 */
Sandwich *Sandwich::move()
{
	return new Sandwich(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Sandwich"*.
 */
std::string Sandwich::getType() const
{
	return "Sandwich";
}