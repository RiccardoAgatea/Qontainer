#include "Cocktail.h"

/**
 * @brief      Constructor for a Steak object.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  g     Garnish for the ordered cocktail.
 */
Cocktail::Cocktail(unsigned int t,
                   const std::string &i,
                   const std::string &g):
	Alcoholic(t, i),
	garnish(g)
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
Cocktail *Cocktail::clone() const
{
	return new Cocktail(*this);
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
Cocktail *Cocktail::move()
{
	return new Cocktail(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Cocktail"*.
 */
std::string Cocktail::getType() const
{
	return "Cocktail";
}

/**
 * @brief      Getter for the *garnish* field.
 *
 * @return     The garnish of the ordered cocktail.
 */
std::string Cocktail::getGarnish() const
{
	return garnish;
}

/**
 * @brief      Implementation of Order::getDetails().
 *
 * @return     A vector containing the string returned by getGarnish().
 */
std::vector<std::string> Cocktail::getDetails() const
{
	return {getGarnish()};
}

/**
 * @brief      Reimplementation of Order::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are both of type Cocktail.
 *
 * @details    Expands the functionality of Order::operator==() by checking for
 *             the equality in the *garnish* field.
 */
bool Cocktail::operator==(const Order &o) const
{
	return Alcoholic::operator==(o) &&
	       garnish == static_cast<const Cocktail &>(o).garnish;
}
