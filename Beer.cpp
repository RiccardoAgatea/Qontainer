#include "Beer.h"
#include <utility>

/**
 * @brief      Constructor for a Steak object.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  s     Size of the ordered beer.
 */
Beer::Beer(unsigned int t,
           const std::string &i,
           const std::string &s):
	Alcoholic(t, i),
	size(s)
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
Beer *Beer::clone() const
{
	return new Beer(*this);
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
Beer *Beer::move()
{
	return new Beer(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Beer"*.
 */
std::string Beer::getType() const
{
	return "Bbeer";
}

/**
 * @brief      Getter for the *size* field.
 *
 * @return     The size of the ordered beer.
 */
std::string Beer::getSize() const
{
	return size;
}

/**
 * @brief      Implementation of Order::getDetails().
 *
 * @return     A vector containing the string returned by getSize().
 */
std::vector<std::string> Beer::getDetails() const
{
	return {getSize()};
}

/**
 * @brief      Reimplementation of Order::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are both of type Beer.
 *
 * @details    Expands the functionality of Order::operator==() by checking for
 *             the equality in the *size* field.
 */
bool Beer::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       size == static_cast<const Beer &>(o).size;
}
