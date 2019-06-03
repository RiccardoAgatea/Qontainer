#include "Model.h"
#include "UnavailableFile.h"
#include "StaticOrder.h"
#include "PolyStatic.h"

void Model::save(const std::string &path) const
{

}

void Model::load(const std::string &path)
{

}

Model::Index Model::addOrder(const std::string &type,
							 unsigned int table,
							 const std::string &item,
							 const std::vector<std::string> &details)
{
	to_do.push_back(Order::getMake()[type](table, item, details).move());
	return Index(--to_do.end());
}

void Model::removeOrder(const Model::Index &index)
{
	to_do.erase(index);
}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}

