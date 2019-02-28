#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <vector>

/**
 * @brief      A polymorphic abstract base class representing an order arriving
 *             to the kitchen af a restaurant.
 */
class Order
{
private:
	unsigned int table;
	std::string item;
public:
	Order(unsigned int,
	      const std::string &);

	/**
	 * @brief      Destructor for Order class.
	 *
	 * @details    It's virtual since the class is polymorphic. It does nothing
	 *             more than the standard destructor.
	 */
	virtual ~Order() = default;

	/**
	 * @brief      Standard polymorphic clone method, necessary to implement
	 *             polymorphic copy construction.
	 *
	 * @return     a pointer to a copy of __*this__ on the heap.
	 *
	 * @details    The responsibility about the destruction of the constructed
	 *             object is of the caller.
	 */
	virtual Order *clone() const = 0;

	/**
	 * @brief      Similar to the clone() method, necessary to implement
	 *             polymorphic move construction.
	 *
	 * @return     A pointer to a copy of __*this__ on the heap.
	 *
	 * @details    The responsibility about the destruction of the constructed
	 *             object is of the caller.
	 *
	 * @post       After the call to move(), __*this__ is left in a valid but
	 *             unspecified state.
	 */
	virtual Order *move() = 0;

	unsigned int getTable();
	std::string getItem();

	/**
	 * @brief      Useful to obtain information about the type of __*this__.
	 *
	 * @return     The type of __*this__, in the form of a string.
	 *
	 * @details    A call _p->getType()_ is very similar to a call
	 *             _typeid(*p).name()_; the main difference is that the string
	 *             returned by _getType()_ is not implementation defined.
	 */
	virtual std::string getType() const = 0;

	/**
	 * @brief      Getter method for the deatils about __*this__.
	 *
	 * @return     A vector of strings, each one associated to a detail about
	 *             the calling object.
	 */
	virtual std::vector<std::string> getDetails() const = 0;
	virtual bool operator==(const Order &) const;
	bool operator!=(const Order &) const;
};

#endif // ORDER_H