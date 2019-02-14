#include "Appetizer.h"
#include <utility>

/**
 * @brief      Constructor for an Appetizer object.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  s     Sauces ordered.
 *
 *             To be noted that Appetizer objects can't be ordered removing some
 *             parts.
 */
Appetizer::Appetizer(unsigned int t,
                     const std::string &i,
                     const std::string &s):
	Food(t, i, ""),
	sauces(s)
{

}

/**
 * @brief      Reimplementation of Order::clone(). Standard polymorphic clone
 *             method, necessary to implement polymorphic copy construction.
 *
 * @return     a pointer to a copy of __*this__ on the heap.
 *
 *             The responsibility about the destruction of the constructed
 *             object is of the caller.
 */
Appetizer *Appetizer::clone() const
{
	return new Appetizer(*this);
}

/**
 * @brief      Reimplementation of Order::move(). Similar to the clone() method,
 *             necessary to implement polymorphic move construction.
 *
 * @return     A pointer to a copy of __*this__ on the heap.
 *
 *             The responsibility about the destruction of the constructed
 *             object is of the caller. After the call to move(), __*this__ is left
 *             in a valid but unspecified state.
 */
Appetizer *Appetizer::move()
{
	return new Appetizer(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Appetizer"*.
 */
std::string Appetizer::getType() const
{
	return "Appetizer";
}

/**
 * @brief      Getter for the *sauces* field.
 *
 * @return     The ordered sauces in the form of a string.
 */
std::string Appetizer::getSauces() const
{
	return sauces;
}

/**
 * @brief      Reimplementation of Food::getDetails(). Since Appetizer doesn't
 *             allow parts to be removed from the dish, the reimplementation
 *             stops the returned vector from holding the empty string.
 *
 * @return     A vector containing the returned string from getSauces().
 */
std::vector<std::string> Appetizer::getDetails() const
{
	return {getSauces()};
}

/**
 * @brief      Reimplementation of Food::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are both of Appetizer type.
 *
 *             Expands the functionality of Order::operator==() by checking for
 *             the equality in the *sauces* field.
 */
bool Appetizer::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       sauces == static_cast<const Appetizer &>(o).sauces;
}
