#ifndef CONTAINER_H
#define CONTAINER_H
#include <initializer_list>
#include <algorithm>
#include "DeepPtr.h"
#include "ContainerExceptions.h"

//T is required to provide specializations for the two overloadings of the clone() function template int the PolyConstruct namespace. Specifically, T *clone(const T &) should return a pointer to a polymorphic copy of the parameter, while T *clone(T &&) should provide the same functionality for move semantics

template<typename T> class Container;

template<typename T> bool operator==(const Container<T> &, const Container<T> &);
template<typename T> bool operator!=(const Container<T> &, const Container<T> &);

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

		//However it's passed, the T parameter is forwarded untouched to the constructor of the info field
		Node(const T * = nullptr, Node * = nullptr, Node * = nullptr);
		Node(const T &, Node * = nullptr, Node * = nullptr);
		Node(T &&, Node * = nullptr, Node * = nullptr);

		~Node();

		//PRE: n1==n2 is well formed if and only if n1 and n2 are heads of different doubly linked lists of the same lenght
		bool operator==(const Node &) const;
	};

	Node *first, *past_the_end;
	unsigned int size_;
public:
	//NOTE:An iterator in the object q is dereferenceable if it's in the range [q.begin(), q.end()), while it's valid if it's either dereferenceable or a past-the-end iterator.

	template<bool constness>
	class temp_iterator
	{
		friend class Container;
	private:
		Node *pointing;

		temp_iterator(Node *);
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

		bool operator==(const temp_iterator &) const;
		bool operator!=(const temp_iterator &) const;
	};

	using iterator = temp_iterator<false>;
	using const_iterator = temp_iterator<true>;

	//Constructors, destructor, and assignment operator
	Container();
	Container(unsigned int, const T & = T());
	Container(const Container &);
	Container(Container &&);
	template<typename InputIterator>
	Container(InputIterator, InputIterator);
	Container(std::initializer_list<T>);
	~Container();
	Container &operator=(const Container &);
	Container &operator=(Container &&);

	//Iteration
	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cend() const;
	static const_iterator toConstIter(const iterator &);

	//Size
	unsigned int size() const noexcept;
	bool empty() const noexcept;

	//Access
	T &front();
	const T &front() const;
	T &back();
	const T &back() const;

	//Content modification
	void push_front(const T &);
	void push_front(T &&);
	void push_back(const T &);
	void push_back(T &&);
	void pop_front();
	void pop_back();

	//the insert() methods return an iterator to the (first) element newly inserted. the first parameter should be a valid iterator in the object *this
	iterator insert(const_iterator, const T &);
	iterator insert(const_iterator, T &&);
	template<typename InputIterator>
	iterator insert(const_iterator, InputIterator, InputIterator);

	//the erase() methods return an iterator to the first element after the removed one(s). In a call q.erase(position), position should be a dereferenceable iterator in the object *this. In a call q.erase(first, last), first and last should be valid iterators in the object *this such that all iterators in the range [first, last) are dereferenceable.
	iterator erase(iterator);
	iterator erase(iterator, iterator);

	//In a call swap(it1, it2), it1 and it2 should be dereferenceable iterators, eventually in different objects of type Container<T>
	static void swap(const iterator &, const iterator &);

	void swap(Container &);

	//A call q.takeTo(from, to) moves the element pointed by from to the position before to. from and to don't need to be iterators over the same Container object, but from should be an iterator over the calling object. from should be a dereferenceable iterator, to should be a valid iterator
	void takeTo(const iterator &, const iterator &);
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
Container<T>::Node::Node(const T *t, Node *n, Node *p):
	info(t), //DeepPtr<T>::DeepPtr(const T*) called
	next(n),
	prev(p)
{

}

template<typename T>
Container<T>::Node::Node(const T &t, Node *n, Node *p):
	info(t), //DeepPtr<T>::DeepPtr(const T&) called
	next(n),
	prev(p)
{

}

template<typename T>
Container<T>::Node::Node(T &&t, Node *n, Node *p):
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
	Container(q.begin(), q.end())
{

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
typename Container<T>::const_iterator Container<T>::toConstIter(const iterator &it)
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
	insert(begin(), t);
}

template<typename T>
void Container<T>::push_front(T &&t)
{
	insert(begin(), t);
}

template<typename T>
void Container<T>::push_back(const T &t)
{
	insert(end(), t);
}

template<typename T>
void Container<T>::push_back(T &&t)
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
typename Container<T>::iterator Container<T>::insert(const_iterator position, const T &t)
{
	return insert(position, &t, &t + 1);
}

template<typename T>
typename Container<T>::iterator Container<T>::insert(const_iterator position, T &&t)
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
typename Container<T>::iterator Container<T>::insert(const_iterator position, InputIterator first,
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
			aux2 = aux1 = new Node(&*(first++));
		else
		{
			aux2->next = new Node(&*(first++), nullptr, aux2);
			aux2 = aux2->next;
		}
	}

	aux1->prev = position.pointing->prev;

	if (position == begin())
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
typename Container<T>::iterator Container<T>::erase(iterator first, iterator last)
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
void Container<T>::swap(const iterator &it1, const iterator &it2)
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
void Container<T>::takeTo(const iterator &from, const iterator &to)
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
typename Container<T>::iterator Container<T>::find(const T &t)
{
	return find_if([&t](const T & t2)
	{
		return t == t2;
	});
}

template<typename T>
typename Container<T>::const_iterator Container<T>::find(const T &t) const
{
	return find_if([&t](const T & t2)
	{
		return t == t2;
	});
}

template<typename T>
template<typename Pred>
typename Container<T>::iterator Container<T>::find_if(Pred p)
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
typename Container<T>::const_iterator Container<T>::find_if(Pred p) const
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
