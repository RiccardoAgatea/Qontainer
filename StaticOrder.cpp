#include "StaticOrder.h"

StaticOrder::Empty::Empty(const std::string &type,
                          const std::vector<std::pair<DetailType, std::string>> &details)
{
	types.push_back(type);

	for (auto &x : details)
		info.insert({type, x});
}

std::vector<std::string> StaticOrder::types;

std::multimap<std::string, std::pair<StaticOrder::DetailType, std::string>>
        StaticOrder::info
{
	{"Steak", {DetailType::SmallText, "Temperature"}},
	{"Hamburger", {DetailType::LargeText, "Not Including"}},
	{"Hamburger", {DetailType::SmallText, "Temperature"}},
	{"Sandwich", {DetailType::LargeText, "Not Including"}},
	{"Appetizer", {DetailType::SmallText, "Sauces"}},
	{"Dessert", {DetailType::LargeText, "Adding"}},
	{"Liquor", {DetailType::Choice, "Ice"}},
	{"Beer", {DetailType::SmallText, "Size"}},
	{"Wine", {DetailType::Choice, "Vintage"}},
	{"Cocktail", {DetailType::LargeText, "Garnish"}},
	{"Analcoholic", {DetailType::Choice, "Ice"}},
	{"Coffee", {DetailType::LargeText, "Notes"}}
};

