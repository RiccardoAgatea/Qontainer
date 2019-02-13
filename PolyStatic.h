#ifndef POLYSTATIC_H
#define POLYSTATIC_H
#include <string>
#include <vector>
#include "DeepPtr.h"
#include "Order.h"

namespace PolyStatic
{
struct Info
{
	std::vector<std::string> long_texts;
	std::vector<std::string> short_texts;
	std::vector<std::string> checks;
};

Info getInfo(const std::string &);

DeepPtr<Order> make(const std::string &,
                    unsigned int,
                    const std::string &,
                    const std::vector<std::string> &);
}

#endif // POLYSTATIC_H