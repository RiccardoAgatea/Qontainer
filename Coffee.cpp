#include "Coffee.h"
#include <utility>

/**
 * @brief      Constructor for a Steak object.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  n     Eventual notes.
 */
Coffee::Coffee(unsigned int t,
               const std::string &i,
               const std::string &n):
	Drink(t, i),
	notes(n)
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
Coffee *Coffee::clone() const
{
	return new Coffee(*this);
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
Coffee *Coffee::move()
{
	return new Coffee(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Coffee"*.
 */
std::string Coffee::getType() const
{
	return "Coffee";
}

/**
 * @brief      Getter for the *coffee* field.
 *
 * @return     The notes about the ordered coffee.
 */
std::string Coffee::getNotes() const
{
	return notes;
}

/**
 * @brief      Implementation of Order::getDetails().
 *
 * @return     A vector containing the string returned by getNotes().
 */
std::vector<std::string> Coffee::getDetails() const
{
	return {getNotes()};
}

/**
 * @brief      Reimplementation of Order::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are both of type Coffee.
 *
 * @details    Expands the functionality of Order::operator==() by checking for
 *             the equality in the *notes* field.
 */
bool Coffee::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       notes == static_cast<const Coffee &>(o).notes;
}
