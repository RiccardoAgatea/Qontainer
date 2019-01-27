#ifndef POLYCONSTRUCT_H
#define POLYCONSTRUCT_H
namespace PolyConstruct
{
template<typename T>
T *clone(const T &);

template<typename T>
T *clone(T &&);
}
#endif // POLYCONSTRUCT_H
