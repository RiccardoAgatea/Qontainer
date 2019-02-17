#include "PolyStatic.h"
#include "UnknownType.h"
#include "Steak.h"
#include "Hamburger.h"
#include "Sandwich.h"
#include "Appetizer.h"
#include "Dessert.h"
#include "Liquor.h"
#include "Beer.h"
#include "Cocktail.h"
#include "Wine.h"
#include "Analcoholic.h"
#include "Coffee.h"
#include <stdexcept>

/**
 * @brief      Factory function for the Order hierarchy
 *
 * @param      type     Type of the object to be constucted
 * @param      table    Number of the table that issued the order
 * @param      item     Ordered item.
 * @param      details  Vector containing the required details for the order.
 *
 * @return     A DeepPtr to the constructed object of the required type.
 *
 * @pre        *type* is a known type of the Order hierarchy, and details contains the right amout of details to construct an object of type *type*
 */
DeepPtr<Order> PolyStatic::make(const std::string &type,
                                unsigned int table,
                                const std::string &item,
                                const std::vector<std::string> &details)
{
	try
	{
		if (type == "Steak")
			DeepPtr<Order>(Steak(table, item, details.at(0)));

		if (type == "Hamburger")
			DeepPtr<Order>(Hamburger(table, item, details.at(0), details.at(1)));

		if (type == "Sandwich")
			DeepPtr<Order>(Sandwich(table, item, details.at(0)));

		if (type == "Appetizer")
			DeepPtr<Order>(Appetizer(table, item, details.at(0)));

		if (type == "Dessert")
			DeepPtr<Order>(Dessert(table, item, details.at(0)));

		if (type == "Liquor")
			DeepPtr<Order>(Liquor(table, item, std::stoi(details.at(0))));

		if (type == "Beer")
			DeepPtr<Order>(Beer(table, item, details.at(0)));

		if (type == "Cocktail")
			DeepPtr<Order>(Cocktail(table, item, details.at(0)));

		if (type == "Wine")
			DeepPtr<Order>(Wine(table, item, std::stoi(details.at(0))));

		if (type == "Analcoholic")
			DeepPtr<Order>(Analcoholic(table, item, std::stoi(details.at(0))));

		if (type == "Coffee")
			DeepPtr<Order>(Coffee(table, item, details.at(0)));

		throw UnknownType("Tried making an Order object of a type not included in the hierarchy");
	}
	catch (UnknownType &)
	{
		throw;
	}
	catch (std::out_of_range &)
	{
		throw std::invalid_argument("Wrong number of details given for argument to MakeOrder::make()");
	}
}

PolyStatic::Info PolyStatic::getInfo(const std::string &type)
{
	if (type == "Steak")
		return Info{{}, {"Temperature"}, {}};

	if (type == "Hamburger")
		return Info{{"Not Including"}, {"Temperature"}, {}};

	if (type == "Sandwich")
		return Info{{"Not Including"}, {}, {}};

	if (type == "Appetizer")
		return Info{{}, {"Sauces"}, {}};

	if (type == "Dessert")
		return Info{{"Adding"}, {}, {}};

	if (type == "Liquor")
		return Info{{}, {}, {"Ice"}};

	if (type == "Beer")
		return Info{{}, {"Size"}, {}};

	if (type == "Cocktail")
		return Info{{"Garnish"}, {}, {}};

	if (type == "Wine")
		return Info{{}, {}, {"Vintage"}};

	if (type == "Analcoholic")
		return Info{{}, {}, {"Ice"}};

	if (type == "Coffee")
		return Info{{"Notes"}, {}, {}};

	throw UnknownType("Tried obtaining info of a type not included in the hierarchy");
}
