#ifndef DEEPPTR_H
#define DEEPPTR_H
#include "PolyConstruct.h"

//T is required to provide specializations for the two overloadings of the clone() function template int the PolyConstruct namespace. Specifically, T *clone(const T &t) should implement the standard polymorphic copy construction, while T *clone(T &&t) should provide the same functionality for move semantics

template<typename T> class DeepPtr;

template<typename T> bool operator==(const DeepPtr<T> &, const DeepPtr<T> &);
template<typename T> bool operator!=(const DeepPtr<T> &, const DeepPtr<T> &);

template<typename T>
class DeepPtr
{
private:
	T *ptr;
public:
	//The constructed DeepPtr points to copy of the T object passed as parameter
	explicit DeepPtr(const T * = nullptr);
	explicit DeepPtr(const T &);
	explicit DeepPtr(T &&);

	//The copy constructor performs a deep copy (as does the copy assignment operator)
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

	//the takeResponsibility method makes the calling DeepPtr point to the object passed as parameter (NOT a copy of it). This means that the calling DeepPtr from that point on will manage this object, and will also destroy it automatically. Destroying the object through different means (an explicit call to delete on the pointer passed as parameter, for example) causes undefined behaviour
	void takeResponsibility(T *);

	//both comparison operators require T to overload operator==.
	//dp1==dp2 returns true if (in this order) dp1 and dp2 are both null, point to the same object, or if *dp1 == *dp2 returns true, and false otherwise. operator!= has the expected behaviour.
	friend bool operator== <T>(const DeepPtr &, const DeepPtr &);
	friend bool operator!= <T>(const DeepPtr &, const DeepPtr &);
};

template<typename T>
DeepPtr<T>::DeepPtr(const T *t):
	ptr(t != nullptr ? PolyConstruct::clone(*t) : nullptr)
{

}

template<typename T>
DeepPtr<T>::DeepPtr(const T &t):
	ptr(PolyConstruct::clone(t))
{

}

template<typename T>
DeepPtr<T>::DeepPtr(T &&t):
	ptr(PolyConstruct::clone(t))
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
	return *ptr;
}

template<typename T>
const T &DeepPtr<T>::operator*() const
{
	return *ptr;
}

template<typename T>
T *DeepPtr<T>::operator->()
{
	return ptr;
}

template<typename T>
const T *DeepPtr<T>::operator->() const
{
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
void DeepPtr<T>::takeResponsibility(T *t)
{
	delete ptr;

	ptr = t;
}

template<typename T>
bool operator==(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2)
{
	if (dp1.ptr == dp2.ptr)
		return true;

	if (dp1.ptr == nullptr || dp2.ptr == nullptr)
		return false;

	return *(dp1.ptr) == *(dp2.ptr);
}

template<typename T>
bool operator!=(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2)
{
	return !(dp1 == dp2);
}
#endif // DEEPPTR_H
