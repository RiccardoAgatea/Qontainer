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

std::vector<Model::Index>
Model::search(const std::function<bool (const Order &)> &pred,
			  bool non_comp,
			  bool comp)
{
	std::vector<Index> aux;

	if (non_comp)
		for (auto it = to_do.begin(); it != to_do.end(); ++it)
			if (pred(*it))
				aux.push_back(it);

	if (comp)
		for (auto it = completed.begin(); it != completed.end(); ++it)
			if (pred(*it))
				aux.push_back(it);

	return aux;
}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}

