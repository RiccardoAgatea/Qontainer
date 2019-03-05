#ifndef UNIFORMINTERFACE_H
#define UNIFORMINTERFACE_H
/**
 * @file UniformInterface.h
 *
 * @brief      Header file providing an homogeneous interface for types to be
 *             used with the DeepPtr and Container template classes
 */

/**
 * @namespace UniformInterface
 *
 * @brief      Namespace containing functions for a homogeneous interface with
 *             the DeepPtr and Container template classes without enforcing requirements on
 *             the instatiation type. A standard version is provided for all the
 *             functions, but if a different behaviour is needed an appropriate
 *             specialization can be defined.
 */
namespace UniformInterface
{
/**
 * @brief      Copy construction
 *
 * @param[in]  t     Object to be copied.
 *
 * @tparam     T          Type of the constructed object.
 *
 * @return     A pointer to a copy of t on the heap, constructed using the
 *             appropriate method for T.
 *
 * @details    The responsibility of destructing the new object is of the
 *             caller. The standard version requires T to provide a T* clone()
 *             const method implementing th estandard polymporphic construction.
 */
template<typename T>
T *clone(const T &t)
{
	return t.clone();
}

/**
 * @brief      Move construction
 *
 * @param[in]  t     Object to be copied.
 *
 * @tparam     T          Type of the constructed object.
 *
 * @return     A pointer to a copy of t on the heap, constructed using the
 *             appropriate method for T.
 *
 * @post       After the call, t is in a valid but undefined state.
 *
 * @details    The responsibility of destructing the new object is of the
 *             caller. The standard version requires T to provide a T* move()
 *             const method implementing th estandard polymporphic construction.
 */
template<typename T>
T *clone(T &&t)
{
	return t.move();
}

/**
 * @brief      Wrapper for the equality operator
 *
 * @param[in]  t1    First object to be compared.
 * @param[in]  t2    Second object to be compared.
 *
 * @tparam     T          Type of the objects to be compared.
 *
 * @return     true if and only if t1 and t2 are equal.
 *
 * @details    The standard version requires T to provide an overload for
 *             operator==().
 */
template<typename T>
bool equal(const T &t1, const T &t2)
{
	return t1 == t2;
}
}

#endif // UNIFORMINTERFACE_H