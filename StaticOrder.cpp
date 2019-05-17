#include "StaticOrder.h"

const std::vector<std::string> StaticOrder::types
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