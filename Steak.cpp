#include "Steak.h"
#include <utility>

/**
 * @brief      Constructor for a Steak object.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  temp  The temperature that the meat should be cooked at.
 *
 * @details    To be noted that Steak objects can't be ordered removing some
 *             parts.
 */
Steak::Steak(unsigned int t,
             const std::string &i,
             const std::string &temp):
	MeatBased(t, i, "", temp)
{

}

/**
 * @brief      Reimplementation of Order::clone(). Standard polymorphic clone
 *             method, necessary to implement polymorphic copy construction.
 *
 * @return     a pointer to a copy of __*this__ on the heap.
 *
 * @details    The responsibility about the destruction of the constructed
 *             object is of the caller.
 */
Steak *Steak::clone() const
{
	return new Steak(*this);
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
Steak *Steak::move()
{
	return new Steak(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Steak"*.
 */
std::string Steak::getType() const
{
	return "Steak";
}

/**
 * @brief      Reimplementation of MeatBased::getDetails(). Since Steak doesn't
 *             allow parts to be removed from the dish, the reimplementation
 *             stops the returned vector from holding the empty string.
 *
 * @return     A vector containing the returned string from getTemperature().
 */
std::vector<std::string> Steak::getDetails() const
{
	return {getTemperature()};
}