#include "MakeOrder.h"
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

DeepPtr<Order> MakeOrder::make(const std::string &s)
{
	unsigned int type_sep = s.find(Order::separator, 0);
	unsigned int table_sep = s.find(Order::separator, type_sep + 1);
	unsigned int item_sep = s.find(Order::separator, table_sep + 1);
	std::string type = s.substr(0, type_sep - 1);

	if (type == "Steak")
		return DeepPtr<Order>(
		           Steak(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 2)
		           )
		       );

	if (type == "Hamburger")
	{
		unsigned int det_sep1 = s.find(Order::separator, item_sep);
		return DeepPtr<Order>(
		           Hamburger(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1, det_sep1 - 1),
		               s.substr(det_sep1 + 1)
		           )
		       );
	}

	if (type == "Sandwich")
		return DeepPtr<Order>(
		           Sandwich(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1)
		           )
		       );

	if (type == "Appetizer")
		return DeepPtr<Order>(
		           Appetizer(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 2)
		           )
		       );

	if (type == "Dessert")
		return DeepPtr<Order>(
		           Dessert(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 2)
		           )
		       );

	if (type == "Liquor")
		return DeepPtr<Order>(
		           Liquor(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1) == "1"
		           )
		       );

	if (type == "Beer")
		return DeepPtr<Order>(
		           Beer(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1)
		           )
		       );

	if (type == "Cocktail")
		return DeepPtr<Order>(
		           Cocktail(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1)
		           )
		       );

	if (type == "Wine")
		return DeepPtr<Order>(
		           Wine(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1) == "1"
		           )
		       );

	if (type == "Analcoholic")
		return DeepPtr<Order>(
		           Analcoholic(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1) == "1"
		           )
		       );

	if (type == "Coffee")
		return DeepPtr<Order>(
		           Coffee(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1)
		           )
		       );

	throw UnknownType("Tried creating Order object of a type not included in the hierarchy");
}

MakeOrder::Info MakeOrder::getInfo(const std::string &type)
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
