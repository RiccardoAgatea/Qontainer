#include "Model.h"
#include "UnavailableFile.h"
#include "PolyStatic.h"

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

Model::Model(const std::string &path_to_do,
			 const std::string &path_completed)
{
	load(path_to_do, path_completed);
}

void Model::save(const std::string &path_to_do,
				 const std::string &path_completed) const
{

}

void Model::load(const std::string &path_to_do,
				 const std::string &path_completed)
{

}

void Model::addOrder(const std::string &ord)
{

}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}
