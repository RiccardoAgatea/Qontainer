#include "Analcoholic.h"
#include <utility>
#include <stdexcept>

/**
 * @brief      Constructor for a Steak object.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  ic    Wether the drink should be served with ice or not.
 */
Analcoholic::Analcoholic(unsigned int t,
                         const std::string &i,
                         bool ic):
	Drink(t, i),
	ice(ic)
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
Analcoholic *Analcoholic::clone() const
{
	return new Analcoholic(*this);
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
 *
 * @post       After the call to move(), __*this__ is left in a valid but
 *             unspecified state.
 */
Analcoholic *Analcoholic::move()
{
	return new Analcoholic(std::move(*this));
}

/**
 * @brief      Reimplementation of Order::getType(). Useful to obtain
 *             information about the type of __*this__.
 *
 * @return     The string *"Analcoholic"*.
 */
std::string Analcoholic::getType() const
{
	return "Analcoholic";
}

/**
 * @brief      Getter for the *ice* field.
 *
 * @return     Wether the wine needs to be served with ice or not.
 */
bool Analcoholic::isIced() const
{
	return ice;
}

/**
 * @brief      Implementation of Order::getDetails().
 *
 * @return     A vector containing the string "1" if isIced() returns true, "0"
 *             otherwise.
 */
std::vector<std::string> Analcoholic::getDetails() const
{
	return {isIced() ? "1" : "0"};
}

/**
 * @brief      Reimplementation of Order::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are both of type
 *             Analcoholic.
 *
 * @details    Expands the functionality of Order::operator==() by checking for
 *             the equality in the *ice* field.
 */
bool Analcoholic::operator==(const Order &o) const
{
	return Drink::operator==(o) &&
	       ice == static_cast<const Analcoholic &>(o).ice;
}
