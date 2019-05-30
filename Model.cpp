#include "Model.h"
#include "UnavailableFile.h"
#include "StaticOrder.h"
#include "PolyStatic.h"

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

const Order &Model::addOrder(const std::string &type,
							 unsigned int table,
							 const std::string &item,
							 const std::vector<std::string> &details)
{
	to_do.push_back(Order::getMake()[type](table, item, details).move());
	return to_do.back();
}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}
