#ifndef MAKEORDER_H
#define MAKEORDER_H
#include <string>
#include <vector>
#include "DeepPtr.h"
#include "Order.h"

namespace MakeOrder
{
struct Info
{
	std::vector<std::string> long_texts;
	std::vector<std::string> short_texts;
	std::vector<std::string> checks;
};

Info getInfo(const std::string &);

DeepPtr<Order> make(const std::string &);
}

#endif // MAKEORDER_H