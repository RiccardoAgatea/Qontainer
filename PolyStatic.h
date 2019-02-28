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
 *             placed in a separated namespace. The alternative (declaring them
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

std::vector<std::vector<std::string>> getInfo(const std::string &);
}

#endif // POLYSTATIC_H