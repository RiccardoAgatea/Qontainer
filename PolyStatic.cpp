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

namespace PolyStatic
{
std::vector<std::string> getTypes()
{
	return
	{
		"Steak",
		"Hamburger",
		"Sandwich",
		"Appetizer",
		"Dessert",
		"Liquor",
		"Beer",
		"Wine",
		"Cocktail",
		"Analcoholic",
		"Coffee"
	};
}

DeepPtr<Order> make(const std::string &type,
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

std::vector<std::vector<std::string>> getInfo(const std::string &type)
{
	if (type == "Steak")
		return {{}, {"Temperature"}, {}};

	if (type == "Hamburger")
		return {{"Not Including"}, {"Temperature"}, {}};

	if (type == "Sandwich")
		return {{"Not Including"}, {}, {}};

	if (type == "Appetizer")
		return {{}, {"Sauces"}, {}};

	if (type == "Dessert")
		return {{"Adding"}, {}, {}};

	if (type == "Liquor")
		return {{}, {}, {"Ice"}};

	if (type == "Beer")
		return {{}, {"Size"}, {}};

	if (type == "Cocktail")
		return {{"Garnish"}, {}, {}};

	if (type == "Wine")
		return {{}, {}, {"Vintage"}};

	if (type == "Analcoholic")
		return {{}, {}, {"Ice"}};

	if (type == "Coffee")
		return {{"Notes"}, {}, {}};

	throw UnknownType("Tried obtaining info of a type not included in the hierarchy");
}
}
