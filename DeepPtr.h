#ifndef DEEPPTR_H
#define DEEPPTR_H
#include <utility>
#include "PolyClone.h"
#include "NullPtrExcept.h"

//T is required to provide specializations for the two overloadings of the clone() function template int the PolyConstruct namespace. Specifically, T *clone(const T &t) should implement the standard polymorphic copy construction, while T *clone(T &&t) should provide the same functionality for move semantics

/**
 * @brief      A smart pointer providing automatic management of memory for the
 *             pointed to object
 *
 * @tparam     T     Type of the pointed to object.
 */
template<typename T>
class DeepPtr
{
private:
	T *ptr;
public:

	/**
	 * @brief      Constructs a pointer to a copy of the object pointed to by t
	 *
	 * @param[in]  t     Object to be copied.
	 *
	 * @details    If t is nullptr, the constructed object is a null smart
	 *             pointer.
	 */
	explicit DeepPtr(const T * = nullptr);

	/**
	 * @brief      Constructs a pointer to a copy of the object t
	 *
	 * @param[in]  t     Object to be copied.
	 */
	explicit DeepPtr(const T &);

	/**
	 * @brief      Constructs a pointer to an object move-constructed from t
	 *
	 * @param[in]  t     Object to be copied.
	 */
	explicit DeepPtr(T &&);

	/**
	 * @brief      Copy constructor
	 *
	 * @param[in]  dp    Object to be copied.
	 *
	 * @details    Performs a deep copy.
	 */
	DeepPtr(const DeepPtr &);

	/**
	 * @brief      Move constructor
	 *
	 * @param      dp  Object to be copied.
	 */
	DeepPtr(DeepPtr &&);


	/**
	 * @brief      Destructor.
	 *
	 * @details    Manages destruction for the pointed to object.
	 */
	~DeepPtr();

	/**
	 * @brief      Copy assignment operator
	 *
	 * @param[in]  t  Object to be copied.
	 *
	 * @return     A reference to __*this__.
	 *
	 * @details    Performs a deep copy.
	 */
	DeepPtr &operator=(const DeepPtr &);

	/**
	 * @brief      Move assignemnt operator
	 *
	 * @param      t  Object to be copied
	 *
	 * @return     A reference to __*this__
	 */
	DeepPtr &operator=(DeepPtr &&);

	/**
	 * @brief      Indirection operator for non-const DeepPtr
	 *
	 * @return     A reference to the pointed to object.
	 *
	 * @pre        __*this__ isn't a null smart pointer
	 */
	T &operator*();

	/**
	 * @brief      Indirection operator for const DeepPtr
	 *
	 * @return     A const reference to the pointed to object.
	 *
	 * @pre        __*this__ isn't a null smart pointer
	 */
	const T &operator*() const;

	/**
	 * @brief      Indirection operator for non-const DeepPtr
	 *
	 * @return     A pointer to the pointed to object.
	 *
	 * @pre        __*this__ isn't a null smart pointer
	 */
	T *operator->();

	/**
	 * @brief      Indirection operator for const DeepPtr
	 *
	 * @return     A pointer to the pointed to object, seen as const.
	 *
	 * @pre        __*this__ isn't a null smart pointer
	 */
	const T *operator->() const;

	/**
	 * @brief      Swaps the pointed to objects of __*this__ and the parameter
	 *
	 * @param      dp    DeepPtr the constent of which will be swapped with __*this__
	 */
	void swap(DeepPtr &);

	/**
	 * @brief      Gives access to the pointed to object as an r-value reference
	 *
	 * @return     An r-value reference to the pointed to object.
	 *
	 * @pre        __*this__ isn't a null smart pointer.
	 *
	 * @post       The pointed to object is in a valid but unspecified state.
	 */
	T &&move();

	/**
	 * @brief      Gives memory management responsibility for the passed object
	 *             to __*this__
	 *
	 * @param      t     Object to be managed by __*this__.
	 *
	 * @details    Fram the moment this method is called, *t will be manged by
	 *             __*this__. Destroying it by any means different from the
	 *             automatic management provided by DeepPtr causes undefined
	 *             behaviour.
	 */
	void takeResponsibility(T *);

	/**
	 * @brief      Equality operator
	 *
	 * @param[in]  dp    DeepPtr to be compared to __*this__.
	 *
	 * @return     true if the two smart pointers ar both null, pointing to the
	 *             same object or pointing to two objects that compare equal
	 *             using operator==(), false otherwise.
	 *
	 * @pre        T provides an overloading for operator==().
	 */
	bool operator==(const DeepPtr &);

	/**
	 * @brief      Inequality operator
	 *
	 * @param[in]  dp    Object to be compared with __*this__.
	 *
	 * @return     true if and only if operator==() returns false.
	 *
	 * @pre        T provides an oveloading for operator==().
	 */
	bool operator!=(const DeepPtr &);
};

template<typename T>
DeepPtr<T>::DeepPtr(const T *t):
	ptr(t != nullptr ? PolyClone::clone(*t) : nullptr)
{

}

template<typename T>
DeepPtr<T>::DeepPtr(const T &t):
	ptr(PolyClone::clone(t))
{

}

template<typename T>
DeepPtr<T>::DeepPtr(T &&t):
	ptr(PolyClone::clone(t))
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
