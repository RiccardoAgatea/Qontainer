#include "Model.h"
#include <fstream>
#include <sstream>
#include "UnavailableFile.h"
#include "MakeOrder.h"

const std::vector<std::string> Model::types =
{
	"Steak",
	"Hamburger",
	"Sandwich",
	"Appetizer",
	"Dessert",
	"Liquor",
	"Beer",
	"Cocktail",
	"Wine",
	"Analcoholic",
	"Coffee"
};

const std::vector<std::string> &Model::getTypes()
{
	return types;
}

Model::Model(const std::string &path_to_do, const std::string &path_completed)
{
	load(path_to_do, path_completed);
}

void Model::save(const std::string &path_to_do, const std::string &path_completed) const
{
	std::ostringstream buffer1, buffer2;

	for (auto it = to_do.begin(); it != to_do.end(); ++it)
		buffer1 << it->recap() << std::endl;

	for (auto it = completed.begin(); it != completed.end(); ++it)
		buffer2 << it->recap() << std::endl;

	std::ofstream file1(path_to_do), file2(path_completed);

	if (!file1)
		throw UnavailableFile("Invalid path to save uncompleted orders");

	if (!file2)
		throw UnavailableFile("Invalid path to save completed orders");

	file1 << buffer1.str() << std::endl;
	file2 << buffer2.str() << std::endl;
}

void Model::load(const std::string &path_to_do, const std::string &path_completed)
{
	std::ifstream file1(path_to_do), file2(path_completed);

	if (!file1)
		throw UnavailableFile("Invalid path to load uncompleted orders");

	if (!file2)
		throw UnavailableFile("Invalid path to load completed orders");

	std::string temp;

	while (std::getline(file1, temp))
		to_do.push_back(*MakeOrder::make(temp));

	while (std::getline(file2, temp))
		completed.push_back(*MakeOrder::make(temp));
}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}
