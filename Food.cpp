#include "Food.h"

/**
 * @brief      Constructor for a Food subobject.
 *
 * @param      t     The table that issued the order.
 * @param      i     The ordered item.
 * @param      w     Eventual parts of the item that must not be included in the
 *                   final dish.
 */
Food::Food(unsigned int t,
           const std::string &i,
           const std::string &w):
	Order(t, i),
	without(w)
{

}

/**
 * @brief      Getter for the *without* field.
 *
 * @return     The list of exclusions from the original ordered item, in the
 *             form of a string.
 */
std::string Food::getRemovedParts() const
{
	return without;
}

/**
 * @brief      Implementation of Order::getDetails().
 *
 * @return     A vector containing the string returned by getRemovedParts().
 */
std::vector<std::string> Food::getDetails() const
{
	return {getRemovedParts()};
}

/**
 * @brief      Reimplementation of Order::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are of the same subtype of
 *             Food.
 *
 * @details    Expands the functionality of Order::operator==() by checking for
 *             the equality in the *without* field.
 */
bool Food::operator==(const Order &o) const
{
	return Order::operator==(o) &&
	       without == static_cast<const Food &>(o).without;
}
