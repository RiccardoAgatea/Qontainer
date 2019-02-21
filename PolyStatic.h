#ifndef POLYSTATIC_H
#define POLYSTATIC_H
#include <string>
#include <vector>
#include "DeepPtr.h"
#include "Order.h"

/**
 * @file PolyStatic.h
 *
 * @brief File defining the PolyStatic namespace
 */

/**
 * @namespace PolyStatic
 *
 * @brief      Collection of functions that provide static functionalities to
 *             the whole Order hieararchy
 *
 * @details    The functions contained in this namespace should be static
 *             methods of the Order hierarchy, but for extensibility they're
 *             placed in a separated namsepace. The alternative (declaring them
 *             as static for the Order class) would then require modifying the
 *             Order.cpp file any time a new tipe is introduced.
 */
namespace PolyStatic
{
std::vector<std::string> getTypes();
DeepPtr<Order> make(const std::string &,
                    unsigned int,
                    const std::string &,
                    const std::vector<std::string> &);

/**
 * @brief      Represents the information about the details of a certain type
 *
 * @details    The three vectors long_texts, short_texts and checks should
 *             contain names for characteristics that are expected to be,
 *             respectively, full structured sentences, simple details, and
 *             true/false questions.
 */
struct Info
{
	std::vector<std::string> long_texts;
	std::vector<std::string> short_texts;
	std::vector<std::string> checks;
};

Info getInfo(const std::string &);
}

#endif // POLYSTATIC_H