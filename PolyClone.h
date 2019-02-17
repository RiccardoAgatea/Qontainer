#ifndef POLYCLONE_H
#define POLYCLONE_H

/**
 * @file PolyClone.h
 *
 * @brief      File containing templates for polymorphic cloning.
 */

/**
 * @namespace PolyClone
 *
 * @brief      Namespace containing declarations of overloaded functions for
 *             homogeneous polymorphic copy and move construction
 */
namespace PolyClone
{

/**
 * @brief      Polymorphic copy construction
 *
 * @param[in]  t     Object to be copied.
 *
 * @tparam     T          Type of the constructed object.
 *
 * @return     A pointer to a copy of t on the heap, constructed using the
 *             appropriate method for T.
 *
 * @details    The responsibility of destructing the new object is of the
 *             caller.
 */
template<typename T>
T *clone(const T &);


/**
 * @brief      Polymorphic move construction
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
 *             caller.
 */
template<typename T>
T *clone(T &&);
}
#endif // POLYCLONE_H
