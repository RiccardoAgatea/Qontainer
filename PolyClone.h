#ifndef POLYCLONE_H
#define POLYCLONE_H
namespace PolyClone
{
template<typename T>
T *clone(const T &);

template<typename T>
T *clone(T &&);
}
#endif // POLYCLONE_H
