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
					 const std::vector<std::string> &details)
{
	to_do.push_back(*PolyStatic::make(type, table, item, details));
}

/**
 * @brief      Checks whether the order queues are empty or not
 *
 * @return     true if and only if both the unfinished orders queue and the
 *             completed orders one are empty.
 */
bool Model::empty() const
{
	return to_do.empty() && completed.empty();
}

/**
 * @brief      Provides an interface for the PolyStatic::getTypes() function
 *
 * @return     The same vector as PolyStatic::getTypes()
 */
std::vector<std::string> Model::getTypes()
{
	return PolyStatic::getTypes();
}

/**
 * @brief      Interface for the PolyStatic::getInfo() function
 *
 * @param[in]  type  The type for which specifics are requested.
 *
 * @return     An Info structure with the details for the representation of
 *             type.
 */
Model::Info Model::getInfo(const std::string &type)
{
	return PolyStatic::getInfo(type);
}
