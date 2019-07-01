#include "Model.h"
#include "UnavailableFile.h"
#include "StaticOrder.h"
#include "PolyStatic.h"

void Model::save(const QString &path) const
{

}

void Model::load(const QString &path)
{

}

Model::Index Model::addOrder(const std::string &type,
							 unsigned int table,
							 const std::string &item,
							 unsigned int quantity,
							 const std::vector<std::string> &details)
{
	to_do.push_back(Order::getMake()[type](table, item, quantity,
										   details));
	return Index(--to_do.end());
}

void Model::removeOrder(const Model::Index &index)
{
	to_do.erase(index);
}

void Model::completeOrder(const Model::Index &index)
{
	to_do.give(index, completed, completed.cend());
}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}

