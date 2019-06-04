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
							 unsigned int quantity,
							 const std::vector<std::string> &details)
{
	to_do.push_back(Order::getMake()[type](table, item, quantity,
										   details).move());
	return Index(--to_do.end());
}

void Model::removeOrder(const Model::Index &index)
{
	to_do.erase(index);
}

void Model::completeOrder(const Model::Index &index)
{
	completed.push_back(*index->move());
	to_do.erase(index);
}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}

