#ifndef POLYSTATIC_H
#define POLYSTATIC_H
#include <string>
#include <vector>
#include "DeepPtr.h"
#include "Order.h"


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