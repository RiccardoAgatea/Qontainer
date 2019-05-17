#ifndef DEEPPTR_H
#define DEEPPTR_H
#include <utility>
#include "UniformInterface.h"
#include "NullPtrExcept.h"

template<typename T> class DeepPtr;

namespace ReferenceTypes
{
template<typename T, bool constness> struct reference;

template<typename T> struct reference<T, true>
{
	using type = const T&;
};

template<typename T> struct reference<T, false>
{
	using type = T&;
};

template<typename T, bool constness> struct pointer;

template<typename T> struct pointer<T, true>
{
	using type = const DeepPtr<T> &;
};

template<typename T> struct pointer<T, false>
{
	using type = DeepPtr<T> &;
};
}

template<typename T>
class DeepPtr
{
private:
	T *ptr;
public:
	explicit DeepPtr(const T * = nullptr);
	explicit DeepPtr(const T &);
	explicit DeepPtr(T &&);
	DeepPtr(const DeepPtr &);
	DeepPtr(DeepPtr &&);
	~DeepPtr();
	DeepPtr &operator=(const DeepPtr &);
	DeepPtr &operator=(DeepPtr &&);
	T &operator*();
	const T &operator*() const;
	T *operator->();
	const T *operator->() const;
	void swap(DeepPtr &);
	T &&move();
	void takeResponsibility(T *);
	bool operator==(const DeepPtr &);
	bool operator!=(const DeepPtr &);
};

template<typename T>
DeepPtr<T>::DeepPtr(const T *t):
	ptr(t != nullptr ? UniformInterface::clone(*t) : nullptr)
{

}

template<typename T>
DeepPtr<T>::DeepPtr(const T &t):
	ptr(UniformInterface::clone(t))
{

}

template<typename T>
DeepPtr<T>::DeepPtr(T &&t):
	ptr(UniformInterface::clone(t))
{

}

template<typename T>
DeepPtr<T>::DeepPtr(const DeepPtr &dp):
	DeepPtr(dp.ptr)
{

}

template<typename T>
DeepPtr<T>::DeepPtr(DeepPtr &&dp):
	ptr(dp.ptr)
{
	dp.ptr = nullptr;
}

template<typename T>
DeepPtr<T>::~DeepPtr()
{
	delete ptr;
}

template<typename T>
DeepPtr<T> &DeepPtr<T>::operator=(const DeepPtr<T> &dp)
{
	DeepPtr temp(dp);

	swap(temp);

	return *this;
}

template<typename T>
DeepPtr<T> &DeepPtr<T>::operator=(DeepPtr &&dp)
{
	swap(dp);

	return *this;
}

template<typename T>
T &DeepPtr<T>::operator*()
{
	if (ptr == nullptr)
		throw NullPtrExcept("Tried dereferencing null smart pointer");

	return *ptr;
}

template<typename T>
const T &DeepPtr<T>::operator*() const
{
	if (ptr == nullptr)
		throw NullPtrExcept("Tried dereferencing null smart pointer");

	return *ptr;
}

template<typename T>
T *DeepPtr<T>::operator->()
{
	if (ptr == nullptr)
		throw NullPtrExcept("Tried dereferencing null smart pointer");

	return ptr;
}

template<typename T>
const T *DeepPtr<T>::operator->() const
{
	if (ptr == nullptr)
		throw NullPtrExcept("Tried dereferencing null smart pointer");

	return ptr;
}

template<typename T>
void DeepPtr<T>::swap(DeepPtr &dp)
{
	T *temp = dp.ptr;
	dp.ptr = ptr;
	ptr = temp;
}

template<typename T>
T &&DeepPtr<T>::move()
{
	if (ptr == nullptr)
		throw NullPtrExcept("Tried dereferencing null smart pointer");

	return std::move(*ptr);
}

template<typename T>
void DeepPtr<T>::takeResponsibility(T *t)
{
	delete ptr;

	ptr = t;
}

template<typename T>
bool DeepPtr<T>::operator==(const DeepPtr<T> &dp)
{
	if (ptr == dp.ptr)
		return true;

	if (ptr == nullptr || dp.ptr == nullptr)
		return false;

	return *(ptr) == *(dp.ptr);
}

template<typename T>
bool DeepPtr<T>::operator!=(const DeepPtr<T> &dp)
{
	return !((*this) == dp);
}
#endif // DEEPPTR_H
