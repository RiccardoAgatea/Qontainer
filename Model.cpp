#include "Model.h"
#include "UnavailableFile.h"
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

void Model::addOrder(const std::string &type,
                     unsigned int table,
                     const std::string &item,
                     const std::vector<std::vector<std::string> > &details)
{

}

bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}

std::vector<std::string> Model::getTypes()
{
	return PolyStatic::getTypes();
}

std::vector<std::vector<std::string>> Model::getInfo(
                                       const std::string &type)
{
	return PolyStatic::getInfo(type);
}
