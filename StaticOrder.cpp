#include "StaticOrder.h"

StaticOrder::Empty::Empty(const std::string &type)
{
	StaticOrder::types.push_back(type);
}

std::vector<std::string> types();

const std::multimap<std::string, std::pair<StaticOrder::DetailType, std::string>>
		StaticOrder::info
{
	{"Steak", {DetailType::SmallText, "Temperature"}},
	{"Hamburger", {DetailType::LargeText, "Not Including"}},
	{"Hamburger", {DetailType::SmallText, "Temperature"}},
	{"Sandwich", {DetailType::LargeText, "Not Including"}},
	{"Appetizer", {DetailType::SmallText, "Sauces"}},
	{"Dessert", {DetailType::LargeText, "Adding"}},
	{"Liquor", {DetailType::CheckBox, "Ice"}},
	{"Beer", {DetailType::SmallText, "Size"}},
	{"Wine", {DetailType::CheckBox, "Vintage"}},
	{"Cocktail", {DetailType::LargeText, "Garnish"}},
	{"Analcoholic", {DetailType::CheckBox, "Ice"}},
	{"Coffee", {DetailType::LargeText, "Notes"}}
};

