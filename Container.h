#ifndef CONTAINER_H
#define CONTAINER_H
#include <initializer_list>
#include <algorithm>
#include "DeepPtr.h"
#include "CustomExceptions.h"

//T is required to provide a T* clone() const method, which should have the standard behaviour for polymorphic clonation (specifically, it should return a pointer to a copy on the heap of the calling object, the destruction of which is responsibility of the Container object)

template<typename T> class Container;

template<typename T> bool operator==(const Container<T> &q1, const Container<T> &q2);
template<typename T> bool operator!=(const Container<T> &q1, const Container<T> &q2);

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

template <typename T>
class Container
{
private:
	struct Node
	{
		DeepPtr<T> info;
		Node *next, *prev;

		Node(DeepPtr<T> dp = DeepPtr<T>(), Node *n = nullptr, Node *p = nullptr);

		//Post: prev points to the last Node of the linked list of which the constructed node is the head
		Node(const Node &n);

		~Node();

		//PRE: *this and n are in different Container objects of the same size
		bool operator==(const Node &n) const;
	};

	Node *first, *past_the_end;
	unsigned int size_;
public:
	//NOTE:An iterator in the object q is dereferenceable if it's in the range [q.begin(), q.end()), it is valid if it's either dereferenceable of a past-the-end iterator.

	template<bool constness>
	class temp_iterator
	{
		friend class Container;
	private:
		Node *pointing;

		temp_iterator(Node *n);
	public:
		using pointer = typename ReferenceTypes::pointer<T, constness>::type;
		using reference = typename ReferenceTypes::reference<T, constness>::type;

		temp_iterator();

		//PRE:calling object is a dereferenceable iterator
		reference operator*() const;
		pointer operator->() const;

		//PRE:calling object is a dereferenceable iterator
		temp_iterator &operator++();
		temp_iterator operator++(int);

		//PRE:calling object is a valid iterator, and is preceded by a dereferenceable iterator
		temp_iterator &operator--();
		temp_iterator operator--(int);

		bool operator==(const temp_iterator &it) const;
		bool operator!=(const temp_iterator &it) const;
	};

	using iterator = temp_iterator<false>;
	using const_iterator = temp_iterator<true>;

	//Constructors, destructor, and assignment operator
	Container();
	Container(unsigned int n, const T &t = T());
	Container(const Container &q);
	Container(Container &&q);
	template<typename InputIterator>
	Container(InputIterator first, InputIterator last);
	Container(std::initializer_list<T> init);
	~Container();
	Container &operator=(const Container &q);
	Container &operator=(Container &&q);

	//Iteration
	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	//Size
	unsigned int size() const noexcept;
	bool empty() const noexcept;

	//Access
	T &front();
	const T &front() const;
	T &back();
	const T &back() const;

	//Content modification
	void push_front(const T &t);
	void push_back(const T &t);
	void pop_front();
	void pop_back();

	//the insert() methods return an iterator to the (eventually first) element newly inserted. position should be a valid iterator in the object *this
	iterator insert(iterator position, const T &t);
	template<typename InputIterator>
	iterator insert(iterator position, InputIterator first, InputIterator last);

	//the erase() methods return an iterator to the first element after the removed one(s). position should be a dereferenceable iterator in the object *this. first and last should be valid iterators in the object *this such that all iterators inthe range [first, last) are dereferenceable.
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

	//it1 and it2 should be dereferenceable iterators, possibly in different objects of type Container<T>
	void swap(const iterator &it1, const iterator &it2) const;

	void swap(Container &q);
	void clear();

	//Finding and Sorting

	//To use any of the two find(const T &) methods, T is required to provide a definition for operator==
	iterator find(const T &t);
	const_iterator find(const T &t) const;

	//p should be a function pointer, a functor or a lambda expression taking a parameter of type const T& and returning bool
	template<typename Pred>
	iterator find_if(Pred p);
	template<typename Pred>
	const_iterator find_if(Pred p) const;

	//To use the sort() method, T is required to provide a definition for operator<
	void sort();

	//p should be a function pointer, a functor or a lambda expression taking two parameters of type const T& and returning bool
	template<typename Pred>
	void sort(Pred p);

	//Comparison operators
	friend bool operator== <T>(const Container &q1, const Container &q2);
	friend bool operator!= <T>(const Container &q1, const Container &q2);
};

//Node methods definition
template<typename T>
Container<T>::Node::Node(DeepPtr<T> dp, Node *n, Node *p):
	info(dp),
	next(n),
	prev(p)
{

}

template<typename T>
Container<T>::Node::Node(const Node &n):
	info(n.info),
	next(n.next != nullptr ? new Node(*(n.next)) : nullptr),
	prev(next != nullptr ? next->prev : this)
{
	if (next != nullptr)
		next->prev = this;
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

	++pointing;

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

	--pointing;

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
bool Container<T>::temp_iterator<constness>::operator==(const temp_iterator &it) const
{
	return pointing == it.pointing;
}

template<typename T>
template<bool constness>
bool Container<T>::temp_iterator<constness>::operator!=(const temp_iterator &it) const
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
Container<T>::Container(unsigned int n, const T &t):
	Container()
{
	while (n > 0)
	{
		push_back(t);
		--n;
	}
}

template<typename T>
Container<T>::Container(const Container &q):
	first(q.first != nullptr ? new Node(*(q.first)) : nullptr),
	past_the_end(first != nullptr ? first->prev : nullptr),
	size_(q.size_)
{
	if (first != nullptr)
		first->prev = nullptr;
}

template<typename T>
Container<T>::Container(Container &&q):
	Container()
{
	swap(q);
}

template<typename T>
template<typename InputIterator>
Container<T>::Container(InputIterator first, InputIterator last):
	Container()
{
	while (first != last)
	{
		push_back(*first);
		++first;
	}
}

template<typename T>
Container<T>::Container(std::initializer_list<T> init):
	Container(init.begin(), init.last())
{

}

template<typename T>
Container<T>::~Container()
{
	delete first;
}

template<typename T>
Container<T> &Container<T>::operator=(const Container &q)
{
	Container temp(q);

	swap(temp);

	return *this;
}

template<typename T>
Container<T> &Container<T>::operator=(Container &&q)
{
	swap(q);

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
	insert(begin(), t);
}

template<typename T>
void Container<T>::push_back(const T &t)
{
	insert(end(), t);
}

template<typename T>
void Container<T>::pop_front()
{
	erase(begin());
}

template<typename T>
void Container<T>::pop_back()
{
	erase(end());
}

template<typename T>
typename Container<T>::iterator Container<T>::insert(iterator position, const T &t)
{
	return insert(position, &t, &t + 1);
}

template<typename T>
template<typename InputIterator>
typename Container<T>::iterator Container<T>::insert(iterator position, InputIterator first,
        InputIterator last)
{
	if (first == last)
		return position;

	Node *aux1 = nullptr, *aux2 = aux1;
	unsigned int count = 0;

	while (first != last)
	{
		++count;

		if (aux1 == nullptr)
			aux2 = aux1 = new Node(*(first++));
		else
		{
			aux2->next = new Node(*(first++), nullptr, aux2);
			aux2 = aux2->next;
		}
	}

	aux1->prev = position.pointing->prev;

	if (position.pointing->prev != nullptr)
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
		return erase(position, ++position);
	}
	catch (InvalidIterator &)
	{
		throw InvalidIterator("Tried erasing invalid position");
	}
}

template<typename T>
typename Container<T>::iterator Container<T>::erase(iterator first, iterator last)
{
	Node *prev = first.pointing->prev;

	while (first != last)
	{
		--size_;
		delete (first++).pointing;
	}

	last.pointing->prev = prev;

	if (prev != nullptr)
		prev->next = last.pointing;

	return last;
}

template<typename T>
void Container<T>::swap(const iterator &it1, const iterator &it2) const
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
void Container<T>::clear()
{
	erase(begin(), end());
}

template<typename T>
typename Container<T>::iterator Container<T>::find(const T &t)
{
	return std::find(begin(), end(), t);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::find(const T &t) const
{
	return std::find(begin(), end(), t);
}

template<typename T>
template<typename Pred>
typename Container<T>::iterator Container<T>::find_if(Pred p)
{
	return std::find_if(begin(), end(), p);
}

template<typename T>
template<typename Pred>
typename Container<T>::const_iterator Container<T>::find_if(Pred p) const
{
	return std::find_if(begin(), end(), p);
}

template<typename T>
void Container<T>::sort()
{
	std::sort(begin(), end());
}

template<typename T>
template<typename Pred>
void Container<T>::sort(Pred p)
{
	std::sort(begin(), end(), p);
}

template<typename T>
bool operator==(const Container<T> &q1, const Container<T> &q2)
{
	if (q1.size() != q2.size())
		return false;

	if (q1.empty() || &q1 == &q2)
		return true;

	return *(q1.first) == *(q2.first);
}

template<typename T>
bool operator!=(const Container<T> &q1, const Container<T> &q2)
{
	return !(q1 == q2);
}
#endif // CONTAINER_H
