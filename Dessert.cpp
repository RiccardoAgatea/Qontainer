#include "Dessert.h"
#include <utility>

/**
 * @brief      Constructor for a Dessert subobject.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  w     Eventual additions to the dish.
 *
 * @details    To be noted that Steak objects can't be ordered removing some
 *             parts.
 */
Dessert::Dessert(unsigned int t,
                 const std::string &i,
                 const std::string &w):
	Food(t, i, ""),
	with(w)
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
Dessert *Dessert::clone() const
{
	return new Dessert(*this);
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
Dessert *Dessert::move()
{
	return new Dessert(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Dessert"*.
 */
std::string Dessert::getType() const
{
	return "Dessert";
}

/**
 * @brief      Getter for the *with* field.
 *
 * @return     The list of additions to the original ordered dish, in the
 *             form of a string.
 */
std::string Dessert::getAddedParts() const
{
	return with;
}

/**
 * @brief      Reimplementation of Dessert::getDetails(). Since Dessert doesn't
 *             allow parts to be removed from the dish, the reimplementation
 *             stops the returned vector from holding the empty string.
 *
 * @return     A vector containing the returned string from getAddedParts().
 */
std::vector<std::string> Dessert::getDetails() const
{
	return {getAddedParts()};
}

/**
 * @brief      Reimplementation of Food::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are both of type Dessert.
 *
 * @details    Expands the functionality of Order::operator==() by checking for
 *             the equality in the *with* field.
 */
bool Dessert::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       with == static_cast<const Dessert &>(o).with;
}
