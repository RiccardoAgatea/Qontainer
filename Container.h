#ifndef CONTAINER_H
#define CONTAINER_H
#include <initializer_list>
#include "DeepPtr.h"
#include "ContainerExceptions.h"

/**
 * @file Container.h
 * @brief Headerfile containing all the definitions related to the Container class template
 */

template<typename T> class Container;

template<typename T> bool operator==(const Container<T> &,
                                     const Container<T> &);
template<typename T> bool operator!=(const Container<T> &,
                                     const Container<T> &);

/**
 * @namespace ReferenceTypes
 * @brief      Namespace defining similar interfaces for reference and pointer
 *             types to const or non-const objects
 */
namespace ReferenceTypes
{
/**
 * @brief      Template class defining an interface for reference types
 *
 * @tparam     T          Type of the object "pointed to" by the reference.
 * @tparam     constness  If true implies a reference to const T, if false
 *                        implies a reference to T.
 */
template<typename T, bool constness> struct reference;

/**
 * @brief      Specialization of reference template for const reference
 *
 * @tparam     T     Type of the object "pointed to" by the reference.
 */
template<typename T> struct reference<T, true>
{
	using type = const T&;
};

/**
 * @brief      Specialization of reference template for non-const reference
 *
 * @tparam     T     Type of the object "pointed to" by the reference.
 */
template<typename T> struct reference<T, false>
{
	using type = T&;
};

/**
 * @brief      Template class defining an interface for pointer types
 *
 * @tparam     T          Type of the pointed object.
 * @tparam     constness  If true implies a pointer to const T, if false implies
 *                        a pointer to T.
 */
template<typename T, bool constness> struct pointer;

/**
 * @brief      Specialization of reference template for pointer to const object
 *
 * @tparam     T     Type of the pointed object.
 *
 *             The pointer is actually a reference to a smart pointer of type
 *             DeepPtr<T>.
 */
template<typename T> struct pointer<T, true>
{
	using type = const DeepPtr<T> &;
};

/**
 * @brief      Specialization of reference template for pointer to non-const
 *             object
 *
 * @tparam     T     Type of the pointed object.
 */
template<typename T> struct pointer<T, false>
{
	using type = DeepPtr<T> &;
};
}

/**
 * @brief      Container class for polymorphic objects
 *
 * @tparam     T     Type of the objects to be held by an instance of Container.
 *
 *             Container is a class template that provides internal support for
 *             polymorphic types. An instance of Container<T> can hold objects of
 *             any subtype of T; for this, T is required to provide specializations for the
 *             two overloadings of the clone() function template in the
 *             PolyClone namespace.
 */
template <typename T>
class Container
{
private:
	struct Node
	{
		DeepPtr<T> info;
		Node *next, *prev;

		//However it's passed, the T parameter is forwarded untouched to the constructor of the info field
		Node(const T * = nullptr,
		     Node * = nullptr,
		     Node * = nullptr);
		Node(const T &,
		     Node * = nullptr,
		     Node * = nullptr);
		Node(T &&,
		     Node * = nullptr,
		     Node * = nullptr);

		~Node();

		//n1==n2 is well formed if and only if n1 and n2 are heads of different doubly linked lists of the same lenght
		bool operator==(const Node &) const;
	};

	Node *first, *past_the_end;
	unsigned int size_;
public:
	//NOTE:An iterator in the object q is dereferenceable if it's in the range [q.begin(), q.end()), while it's valid if it's either dereferenceable or a past-the-end iterator.

	/**
	 * @brief      (Template of) bidirectional iterator type over a Container
	 *             object
	 *
	 * @tparam     constness  Wether the iterator is also an output iterator or
	 *                        only an input iterator
	 */
	template<bool constness>
	class temp_iterator
	{
		friend class Container;
	private:
		Node *pointing;

		temp_iterator(Node *);
	public:
		using pointer = typename ReferenceTypes::pointer<T, constness>::type;
		using reference = typename
		                  ReferenceTypes::reference<T, constness>::type;

		/**
		 * @brief      Default constructor
		 *
		 *             Constructs an invalid iterator.
		 */
		temp_iterator();

		/**
		 * @brief      Indirection operator
		 *
		 * @return     a reference (const reference if constness is true) to the
		 *             current element __*this__ is iterating over.
		 *
		 * @pre        __*this__ is a dereferenceable iterator.
		 */
		reference operator*() const;

		/**
		 * @brief      Indirection operator
		 *
		 * @return     a pointer (pointer to const object if constness is true) to the
		 *             current element __*this__ is iterating over.
		 *
		 * @pre        __*this__ is a dereferenceable iterator.
		 */
		pointer operator->() const;

		/**
		 * @brief      Prefix increment operator
		 *
		 * @return     A reference to the calling object, that's been advanced
		 *             to the next element in the container it's iterating over.
		 *             Might be a past-the-end iterator.
		 *
		 * @pre        __*this__ is a dereferenceable iterator.
		 */
		temp_iterator &operator++();

		/**
		 * @brief      Postfix increment operator
		 *
		 * @param[in]  <unnamed>  Conventional dummy parameter to distinguish
		 *                        between prefix and postfix versions of
		 *                        operators.
		 *
		 * @return     An iterator to the element __*this__ was iterating over
		 *             before being incremented. After the call, __*this__ might
		 *             be a past-the-end iterator.
		 *
		 * @pre        __*this__ is a dereferenceable iterator.
		 */
		temp_iterator operator++(int);

		/**
		 * @brief      Prefix decrement operator
		 *
		 * @return     A reference to the calling object, that's been retroceded
		 *             to the previous element in the container it's iterating
		 *             over.
		 *
		 * @pre        __*this__ is a valid iterator, and is preceded by a
		 *             dereferenceable iterator.
		 */
		temp_iterator &operator--();

		/**
		 * @brief      Postfix decrement operator
		 *
		 * @param[in]  <unnamed>  Conventional dummy parameter to distinguish
		 *                        between prefix and postfix versions of
		 *                        operators.
		 *
		 * @return     An iterator to the element __*this__ was iterating over
		 *             before being decremented.
		 *
		 * @pre        __*this__ is a valid iterator, and is preceded by a
		 *             dereferenceable iterator.
		 */
		temp_iterator operator--(int);

		/**
		 * @brief      Equality operator
		 *
		 * @param[in]  it  Iterator to be compared with __*this__.
		 *
		 * @return     true if and only if __*this__ and it are iterating over
		 *             the same element in the same Container object.
		 */
		bool operator==(const temp_iterator &) const;

		/**
		 * @brief      Inequality operator
		 *
		 * @param[in]  it  Iterator to be compared with __*this__.
		 *
		 * @return     true if and only if operator!=() returns false.
		 */
		bool operator!=(const temp_iterator &) const;
	};

	using iterator = temp_iterator<false>;
	using const_iterator = temp_iterator<true>;

	//Constructors, destructor, and assignment operator

	/**
	 * @brief      Default constructor
	 *
	 *             Constructs an empty container.
	 */
	Container();

	/**
	 * @brief      Fill constructor
	 *
	 * @param[in]  n     Number of copies of t to be inserted into the constructed
	 *                   container.
	 * @param[in]  t     Object to be inserted in the constructed container n times.
	 *                   Defaults to a default constructed object.
	 */
	Container(unsigned int,
	          const T & = T());

	/**
	 * @brief      Copy constructor
	 *
	 * @param[in]  c     container to be copied.
	 */
	Container(const Container &);

	/**
	 * @brief      Move constructor
	 *
	 * @param      c     container to be moved.
	 */
	Container(Container &&);

	/**
	 * @brief      Range constructor
	 *
	 * @param      first  Input iterator to the first element in the range to be copy
	 *                    constructed into the container.
	 * @param      last   Input iterator to the element past-the-end of the range to be
	 *                    copy constructed into the container.
	 *
	 * @tparam     InputIterator  Input iterator type over the range to be copy
	 *                            constructed into the continer.
	 */
	template<typename InputIterator>
	Container(InputIterator,
	          InputIterator);

	/**
	 * @brief      Initializer list constructor
	 *
	 * @param[in]  init  initializer list holding the values to be copy constructed
	 *                   into the container.
	 */
	Container(std::initializer_list<T>);


	/**
	 * @brief      Destructor
	 */
	~Container();

	/**
	 * @brief      Copy assignment operator
	 *
	 * @param[in]  c     container to be copied.
	 *
	 * @return     A reference to __*this__.
	 */
	Container &operator=(const Container &);

	/**
	 * @brief      Move assignment operator
	 *
	 * @param      c     container to be moved.
	 *
	 * @return     A reference to __*this__.
	 */
	Container &operator=(Container &&);

	//Iteration

	/**
	 * @brief      Standard begin() method for non-const Container objects
	 *
	 * @return     An iterator over __*this__, currently pointing to the first
	 *             element.
	 */
	iterator begin();

	/**
	 * @brief      Standard begin() method for const Container objects
	 *
	 * @return     A const_iterator over __*this__, currently pointing to the first
	 *             element.
	 */
	const_iterator begin() const;

	/**
	 * @brief      Standard cbegin() method
	 *
	 * @return     A const_iterator over __*this__, currently pointing to the first
	 *             element.
	 */
	const_iterator cbegin() const;

	/**
	 * @brief      Standard end() method for non-const Container objects
	 *
	 * @return     An iterator over __*this__, currently pointing to the
	 *             past-the-end element.
	 */
	iterator end();

	/**
	 * @brief      Standard end() method for const Container objects
	 *
	 * @return     A const_iterator over __*this__, currently pointing to the
	 *             past-the-end element.
	 */
	const_iterator end() const;

	/**
	 * @brief      Standard cend() method
	 *
	 * @return     A const_iterator over __*this__, currently pointing to the
	 *             past-the-end element.
	 */
	const_iterator cend() const;


	/**
	 * @brief      Conversion method from iterator to const_iterator
	 *
	 * @param[in]  it    iterator to be cast to constiterator.
	 *
	 * @return     A const_iterator equivalent to it.
	 */
	static const_iterator toConstIter(const iterator &);

	//Size

	/**
	 * @brief      Standard size() method
	 *
	 * @return     The number of elemnts.
	 */
	unsigned int size() const noexcept;

	/**
	 * @brief      Standard empty() method
	 *
	 * @return     true if and only if the size is 0.
	 */
	bool empty() const noexcept;

	//Access

	/**
	 * @brief      Standard front() method for non-const Container objects
	 *
	 * @return     A reference to the first element.
	 */
	T &front();

	/**
	 * @brief      Standard front() method for const Container objects
	 *
	 * @return     A const reference to the first element.
	 */
	const T &front() const;

	/**
	 * @brief      Standard back() method for non-const Container objects
	 *
	 * @return     A reference to the last element.
	 */
	T &back();

	/**
	 * @brief      Standard back() method for const Container objects
	 *
	 * @return     A const reference to the last element.
	 */
	const T &back() const;

	//Content modification

	/**
	 * @brief      Inserts element to the beginning
	 *
	 * @param[in]  t     Element to be copy constructed at the beginning of __*this__.
	 */
	void push_front(const T &);

	/**
	 * @brief      Inserts element to the beginning
	 *
	 * @param[in]  t     Element to be move constructed at the beginning of __*this__.
	 */
	void push_front(T &&);

	/**
	* @brief      Inserts element to the end
	*
	* @param[in]  t     Element to be copy constructed at the end of __*this__.
	*/
	void push_back(const T &);

	/**
	* @brief      Inserts element to the end
	*
	* @param[in]  t     Element to be move constructed at the end of __*this__.
	*/
	void push_back(T &&);

	/**
	 * @brief      Removes element from beginning
	 */
	void pop_front();

	/**
	 * @brief      Removes element from end
	 */
	void pop_back();

	//the insert() methods return an iterator to the (first) element newly inserted. the first parameter should be a valid iterator in the object *this

	/**
	 * @brief      Insert element in arbitrary position
	 *
	 * @param[in]  position  Iterator to the element before which the new element
	 *                       should be copy constructed.
	 * @param[in]  t         Element to be copy constructed.
	 *
	 * @return     An iterator to the inserted element.
	 *
	 * @pre        position is a valid const_iterator over __*this__.
	 */
	iterator insert(const_iterator,
	                const T &);

	/**
	 * @brief      Insert element in arbitrary position
	 *
	 * @param[in]  position  Iterator to the element before which the new element
	 *                       should be move constructed.
	 * @param[in]  t         Element to be move constructed.
	 *
	 * @return     An iterator to the inserted element.
	 *
	 * @pre        position is a valid const_iterator over __*this__.
	 */
	iterator insert(const_iterator,
	                T &&);

	/**
	 * @brief      Insert elements from a range in arbitrary position
	 *
	 * @param[in]  position  Iterator to the element before which the new elements
	 *                       should be copy constructed.
	 * @param      first     Input iterator to the first element in the range to be
	 *                       copy constructed into the container.
	 * @param      last      Input iterator to the element past-the-end of the range to
	 *                       be copy constructed into the container.
	 *
	 * @tparam     InputIterator  Input iterator type over the range to be copy
	 *                            constructed into the continer.
	 *
	 * @return     An iterator to the first inserted element.
	 *
	 * @pre        position is a valid const_iterator over __*this__.
	 */
	template<typename InputIterator>
	iterator insert(const_iterator,
	                InputIterator,
	                InputIterator);

	//the erase() methods return an iterator to the first element after the removed one(s). In a call q.erase(position), position should be a dereferenceable iterator in the object *this. In a call q.erase(first, last), first and last should be valid iterators in the object *this such that all iterators in the range [first, last) are dereferenceable.
	iterator erase(iterator);
	iterator erase(iterator,
	               iterator);

	//In a call swap(it1, it2), it1 and it2 should be dereferenceable iterators, eventually in different objects of type Container<T>
	static void swap(const iterator &,
	                 const iterator &);

	void swap(Container &);

	//A call q.takeTo(from, to) moves the element pointed by from to the position before to. from and to don't need to be iterators over the same Container object, but from should be an iterator over the calling object. from should be a dereferenceable iterator, to should be a valid iterator
	void takeTo(const iterator &,
	            const iterator &);
	void clear();

	//Finding

	//To use any of the two find(const T &) methods, T is required to provide an overloading for operator==
	iterator find(const T &);
	const_iterator find(const T &) const;

	//the parameter should be a function pointer, a functor or a lambda expression taking one parameter of type const T& and returning bool
	template<typename Pred>
	iterator find_if(Pred);
	template<typename Pred>
	const_iterator find_if(Pred) const;

	//Comparison operators
	friend bool operator== <T>(const Container &, const Container &);
	friend bool operator!= <T>(const Container &, const Container &);
};

//Node methods definition
template<typename T>
Container<T>::Node::Node(const T *t,
                         Node *n,
                         Node *p):
	info(t), //DeepPtr<T>::DeepPtr(const T*) called
	next(n),
	prev(p)
{

}

template<typename T>
Container<T>::Node::Node(const T &t,
                         Node *n,
                         Node *p):
	info(t), //DeepPtr<T>::DeepPtr(const T&) called
	next(n),
	prev(p)
{

}

template<typename T>
Container<T>::Node::Node(T &&t,
                         Node *n,
                         Node *p):
	info(t), //DeepPtr<T>::DeepPtr(T &&) called
	next(n),
	prev(p)
{

}

template<typename T>
Container<T>::Node::~Node()
{
	delete next;
}

template<typename T>
bool Container<T>::Node::operator==(const Node &n) const
{
	if (info != n.info)
		return false;

	if (next == n.next)
		return true;

	return *next == *(n.next);
}

//temp_iterator methods definition
template<typename T>
template<bool constness>
Container<T>::temp_iterator<constness>::temp_iterator(Node *n):
	pointing(n)
{

}

template<typename T>
template<bool constness>
Container<T>::temp_iterator<constness>::temp_iterator():
	iterator(nullptr)
{

}

template<typename T>
template<bool constness>
typename Container<T>::template temp_iterator<constness>::reference
Container<T>::temp_iterator<constness>::operator*() const
{
	if (pointing == nullptr)
		throw InvalidIterator("Tried dereferencing invalid iterator");

	if (pointing->next == nullptr)
		throw InvalidIterator("Tried dereferencing past-the-end iterator");

	return *(pointing->info);
}

template<typename T>
template<bool constness>
typename Container<T>::template temp_iterator<constness>::pointer
Container<T>::temp_iterator<constness>::operator->() const
{
	if (pointing == nullptr)
		throw InvalidIterator("Tried dereferencing invalid iterator");

	if (pointing->next == nullptr)
		throw InvalidIterator("Tried dereferencing past-the-end iterator");

	return pointing->info;
}

template<typename T>
template<bool constness>
typename Container<T>::template temp_iterator<constness>
&Container<T>::temp_iterator<constness>::operator++()
{
	if (pointing == nullptr)
		throw InvalidIterator("Tried incrementing invalid iterator");

	if (pointing->next == nullptr)
		throw InvalidIterator("Tried incrementing past-the-end iterator");

	pointing = pointing->next;

	return *this;
}

template<typename T>
template<bool constness>
typename Container<T>::template temp_iterator<constness>
Container<T>::temp_iterator<constness>::operator++(int)
{
	iterator aux(*this);

	++(*this);

	return aux;
}

template<typename T>
template<bool constness>
typename Container<T>::template temp_iterator<constness>
&Container<T>::temp_iterator<constness>::operator--()
{
	if (pointing == nullptr)
		throw InvalidIterator("Tried decrementing invalid iterator");

	if (pointing->prev == nullptr)
		throw InvalidIterator("Tried decrementing beginning iterator");

	pointing = pointing->prev;

	return *this;
}

template<typename T>
template<bool constness>
typename Container<T>::template temp_iterator<constness>
Container<T>::temp_iterator<constness>::operator--
(int)
{
	iterator aux(*this);

	--(*this);

	return aux;
}

template<typename T>
template<bool constness>
bool Container<T>::temp_iterator<constness>::operator==
(const temp_iterator &it) const
{
	return pointing == it.pointing;
}

template<typename T>
template<bool constness>
bool Container<T>::temp_iterator<constness>::operator!=
(const temp_iterator &it) const
{
	return !(*this == it);
}

//Container method definitions
template<typename T>
Container<T>::Container():
	first(new Node()),
	past_the_end(first),
	size_(0)
{

}

template<typename T>
Container<T>::Container(unsigned int n,
                        const T &t):
	Container()
{
	while (n > 0)
	{
		push_back(t);
		--n;
	}
}

template<typename T>
Container<T>::Container(const Container &c):
	Container(c.begin(), c.end())
{

}

template<typename T>
Container<T>::Container(Container &&c):
	Container()
{
	swap(c);
}

template<typename T>
template<typename InputIterator>
Container<T>::Container(InputIterator first,
                        InputIterator last):
	Container()
{
	insert(begin(), first, last);
}

template<typename T>
Container<T>::Container(std::initializer_list<T> init):
	Container(init.begin(), init.end())
{

}

template<typename T>
Container<T>::~Container()
{
	delete first;
}

template<typename T>
Container<T> &Container<T>::operator=(const Container &c)
{
	Container temp(c);

	swap(temp);

	return *this;
}

template<typename T>
Container<T> &Container<T>::operator=(Container &&c)
{
	swap(c);

	return *this;
}

template<typename T>
typename Container<T>::iterator Container<T>::begin()
{
	return iterator(first);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::begin() const
{
	return const_iterator(first);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::cbegin() const
{
	return const_iterator(first);
}

template<typename T>
typename Container<T>::iterator Container<T>::end()
{
	return iterator(past_the_end);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::end() const
{
	return const_iterator(past_the_end);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::cend() const
{
	return const_iterator(past_the_end);
}

template<typename T>
typename Container<T>::const_iterator
Container<T>::toConstIter(const iterator &it)
{
	return const_iterator(it.pointing);
}

template<typename T>
unsigned int Container<T>::size() const noexcept
{
	return size_;
}

template<typename T>
bool Container<T>::empty() const noexcept
{
	return size() == 0;
}

template<typename T>
T &Container<T>::front()
{
	if (empty())
		throw EmptyContainer("Tried accessing front of empty Container");

	return *(first->info);
}

template<typename T>
const T &Container<T>::front() const
{
	if (empty())
		throw EmptyContainer("Tried accessing front of empty Container");

	return *(first->info);
}

template<typename T>
T &Container<T>::back()
{
	if (empty())
		throw EmptyContainer("Tried accessing back of empty Container");

	return *(past_the_end->prev->info);
}

template<typename T>
const T &Container<T>::back() const
{
	if (empty())
		throw EmptyContainer("Tried accessing back of empty Container");

	return *(past_the_end->prev->info);
}

template<typename T>
void Container<T>::push_front(const T &t)
{
	insert(cbegin(), t);
}

template<typename T>
void Container<T>::push_front(T &&t)
{
	insert(cbegin(), t);
}

template<typename T>
void Container<T>::push_back(const T &t)
{
	insert(cend(), t);
}

template<typename T>
void Container<T>::push_back(T &&t)
{
	insert(cend(), t);
}

template<typename T>
void Container<T>::pop_front()
{
	erase(cbegin());
}

template<typename T>
void Container<T>::pop_back()
{
	erase(cend());
}

template<typename T>
typename Container<T>::iterator
Container<T>::insert(const_iterator position,
                     const T &t)
{
	return insert(position, &t, &t + 1);
}

template<typename T>
typename Container<T>::iterator
Container<T>::insert(const_iterator position,
                     T &&t)
{
	Node *aux = new Node(t, position.pointing, position.pointing->prev);
	position.pointing->prev = aux;

	if (position != begin())
		aux->prev->next = aux;
	else
		first = aux;
}

template<typename T>
template<typename InputIterator>
typename Container<T>::iterator
Container<T>::insert(const_iterator position,
                     InputIterator first,
                     InputIterator last)
{
	if (first == last)
		throw InvalidIterator("Tried inserting 0 elements in Container");

	Node *aux1 = nullptr, *aux2 = aux1;
	unsigned int count = 0;

	while (first != last)
	{
		++count;

		if (aux1 == nullptr)
			aux2 = aux1 = new Node(&*(first++));
		else
		{
			aux2->next = new Node(&*(first++), nullptr, aux2);
			aux2 = aux2->next;
		}
	}

	aux1->prev = position.pointing->prev;

	if (position == cbegin())
		this->first = aux1;
	else
		position.pointing->prev->next = aux1;

	aux2->next = position.pointing;
	position.pointing->prev = aux2;

	size_ += count;

	return iterator(aux1);
}

template<typename T>
typename Container<T>::iterator Container<T>::erase(iterator position)
{
	try
	{
		auto it = position++;
		return erase(it, position);
	}
	catch (InvalidIterator &)
	{
		throw InvalidIterator("Tried erasing invalid position");
	}
}

template<typename T>
typename Container<T>::iterator
Container<T>::erase(iterator first,
                    iterator last)
{
	if (first != last)
	{
		Node *prev = first.pointing->prev;

		while (first != last)
		{
			--size_;

			Node *del = first.pointing;
			++first;
			del->next = nullptr;
			delete del;
		}

		last.pointing->prev = prev;

		if (prev == nullptr)
			this->first = last.pointing;
		else
			prev->next = last.pointing;
	}

	return last;
}

template<typename T>
void Container<T>::swap(const iterator &it1,
                        const iterator &it2)
{
	it1.pointing->info.swap(it2.pointing->info);
}

template<typename T>
void Container<T>::swap(Container &q)
{
	Node *ptr = q.first;
	q.first = first;
	first = ptr;

	ptr = q.past_the_end;
	q.past_the_end = past_the_end;
	past_the_end = ptr;

	unsigned int temp = q.size_;
	q.size_ = size_;
	size_ = temp;
}

template<typename T>
void Container<T>::takeTo(const iterator &from,
                          const iterator &to)
{
	Node *aux = new Node(nullptr, to.pointing, to.pointing->prev);
	to.pointing->prev = aux;

	if (aux->prev != nullptr)
		aux->prev->next = aux;

	swap(from, iterator(aux));
	erase(from);
}

template<typename T>
void Container<T>::clear()
{
	erase(begin(), end());
}

template<typename T>
typename Container<T>::iterator
Container<T>::find(const T &t)
{
	return find_if([&t](const T & t2)
	{
		return t == t2;
	});
}

template<typename T>
typename Container<T>::const_iterator
Container<T>::find(const T &t) const
{
	return find_if([&t](const T & t2)
	{
		return t == t2;
	});
}

template<typename T>
template<typename Pred>
typename Container<T>::iterator
Container<T>::find_if(Pred p)
{
	auto it = begin();

	while (it != end())
	{
		if (p(*it))
			return it;

		++it;
	}

	return end();
}

template<typename T>
template<typename Pred>
typename Container<T>::const_iterator
Container<T>::find_if(Pred p) const
{
	auto it = begin();

	while (it != end())
	{
		if (p(*it))
			return it;

		++it;
	}

	return end();
}

template<typename T>
bool operator==(const Container<T> &q1,
                const Container<T> &q2)
{
	if (q1.size() != q2.size())
		return false;

	if (q1.empty() || &q1 == &q2)
		return true;

	return *(q1.first) == *(q2.first);
}

template<typename T>
bool operator!=(const Container<T> &q1,
                const Container<T> &q2)
{
	return !(q1 == q2);
}
#endif // CONTAINER_H
