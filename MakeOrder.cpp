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
	unsigned int type_sep = s.find(Order::getSeparator(), 0);
	unsigned int table_sep = s.find(Order::getSeparator(), type_sep + 1);
	unsigned int item_sep = s.find(Order::getSeparator(), table_sep + 1);
	std::string type = s.substr(0, type_sep - 1);

	if (type == "steak")
		return DeepPtr<Order>(
				   Steak(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 2)
				   )
			   );
	else if (type == "hamburger")
	{
		unsigned int det_sep1 = s.find(Order::getSeparator(), item_sep);
		return DeepPtr<Order>(
				   Hamburger(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 1, det_sep1 - 1),
					   s.substr(det_sep1 + 1)
				   )
			   );
	}
	else if (type == "sandwich")
		return DeepPtr<Order>(
		           Sandwich(
		               std::stoul(s.substr(type_sep + 1, table_sep - 1)),
		               s.substr(table_sep + 1, item_sep - 1),
		               s.substr(item_sep + 1)
		           )
		       );
	else if (type == "appetizer")
		return DeepPtr<Order>(
				   Appetizer(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 2)
				   )
			   );
	else if (type == "dessert")
		return DeepPtr<Order>(
				   Dessert(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 2)
				   )
			   );
	else if (type == "liquor")
		return DeepPtr<Order>(
				   Liquor(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 1) == "1"
				   )
			   );
	else if (type == "beer")
		return DeepPtr<Order>(
				   Beer(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 1)
				   )
			   );
	else if (type == "cocktail")
		return DeepPtr<Order>(
				   Cocktail(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 1)
				   )
			   );
	else if (type == "wine")
		return DeepPtr<Order>(
				   Wine(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 1) == "1"
				   )
			   );
	else if (type == "analcoholic")
		return DeepPtr<Order>(
				   Analcoholic(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 1) == "1"
				   )
			   );
	else if (type == "coffee")
		return DeepPtr<Order>(
				   Coffee(
					   std::stoul(s.substr(type_sep + 1, table_sep - 1)),
					   s.substr(table_sep + 1, item_sep - 1),
					   s.substr(item_sep + 1)
				   )
			   );

	throw UnknownType("Tried creating Order object of a type not included in the hierarchy");
}