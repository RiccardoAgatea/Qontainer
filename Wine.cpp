#include "Wine.h"
#include <utility>
#include <stdexcept>

/**
 * @brief      Constructor for a Steak object.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  v     Wether the wine needs to be vintage or not.
 */
Wine::Wine(unsigned int t,
           const std::string &i,
           bool v):
	Alcoholic(t, i),
	vintage(v)
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
Wine *Wine::clone() const
{
	return new Wine(*this);
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
Wine *Wine::move()
{
	return new Wine(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Wine"*.
 */
std::string Wine::getType() const
{
	return "Wine";
}

/**
 * @brief      Getter for the *vintage* field.
 *
 * @return     Wether the wine needs to be vintage or not.
 */
bool Wine::isVintage() const
{
	return vintage;
}

/**
 * @brief      Implementation of Order::getDetails().
 *
 * @return     A vector containing the string "1" if isVintage() returns true,
 *             "0" otherwise.
 */
std::vector<std::string> Wine::getDetails() const
{
	return {isVintage() ? "1" : "0"};
}

/**
 * @brief      Reimplementation of Order::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are both of type Wine.
 *
 * @details    Expands the functionality of Order::operator==() by checking for
 *             the equality in the *vintage* field.
 */
bool Wine::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       vintage == static_cast<const Wine &>(o).vintage;
}
