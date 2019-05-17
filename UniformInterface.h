#ifndef UNIFORMINTERFACE_H
#define UNIFORMINTERFACE_H

namespace UniformInterface
{
template<typename T>
T *clone(const T &t)
{
	return t.clone();
}

template<typename T>
T *clone(T &&t)
{
	return t.move();
}

template<typename T>
bool equal(const T &t1, const T &t2)
{
	return t1 == t2;
}
}

#endif // UNIFORMINTERFACE_H