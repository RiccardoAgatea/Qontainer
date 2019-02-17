#include "Hamburger.h"
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
Hamburger *Hamburger::clone() const
{
	return new Hamburger(*this);
}

/**
 * @brief      Reimplementation of Order::move(). Similar to the clone() method,
 *             necessary to implement polymorphic move construction.
 *
 * @return     A pointer to a copy of __*this__ on the heap.
 *
 * @details    The responsibility about the destruction of the constructed
 *             object is of the caller.
 *
 * @post       After the call to move(), __*this__ is left in a valid but
 *             unspecified state.
 */
Hamburger *Hamburger::move()
{
	return new Hamburger(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Hamburger"*.
 */
std::string Hamburger::getType() const
{
	return "Hamburger";
}