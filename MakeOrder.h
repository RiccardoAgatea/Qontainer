#ifndef MAKEORDER_H
#define MAKEORDER_H
#include <string>
#include "DeepPtr.h"
#include "Order.h"

namespace MakeOrder
{
DeepPtr<Order> make(const std::string &);
}

#endif // MAKEORDER_H