#include "Order.h"
#include <typeinfo>

/**
 * @brief Constructor for the Order class
 * @param t Table that issued the order
 * @param i Ordered item
 */

Order::Order(unsigned int t,
             const std::string &i):
	table(t),
	item(i)
{

}

/**
 * @brief Getter for the *table* field
 * @return Table that issued the order
 */

unsigned int Order::getTable()
{
	return table;
}

/**
 * @brief Getter for the *item* field
 * @return Ordered item
 */

std::string Order::getItem()
{
	return item;
}

/**
 * @brief Equality operator for Order objects
 * @param o Order with which __*this__ should be compared
 * @return true if all the comparison operators between the respective fields return true and the two objects are of the same subtype of Order
 *
 * Of particular note is the fact that operator==() compares the types of the two objects (it does so through the getType() method). The comparison evaluates to true if the types are the same.
 */

bool Order::operator==(const Order &o) const
{
	return getType() == o.getType() &&
	       table == o.table &&
	       item == o.item;
}

/**
 * @brief Inequality operator for Order objects
 * @param o Order with which __*this__ should be compared
 * @return true if and only if _operator==(o)_ returns false
 *
 * This method is not virtual, but calls operator==(), which is, in its body
 */

bool Order::operator!=(const Order &o) const
{
	return !(*this == o);
}

namespace PolyClone
{
template<>
Order *clone(const Order &t)
{
	return t.clone();
}

template<>
Order *clone(Order &&t)
{
	return t.move();
}
}