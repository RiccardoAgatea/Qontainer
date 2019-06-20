#ifndef CONTAINER_H
#define CONTAINER_H
#include <initializer_list>
#include "DeepPtr.h"
#include "ContainerExceptions.h"

template <typename T>
class Container
{
private:
	struct Node
	{
		DeepPtr<T> info;
		Node *next, *prev;

		Node(const DeepPtr<T> & = DeepPtr<T>(),
			 Node * = nullptr,
			 Node * = nullptr);
		Node(DeepPtr<T> &&,
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

		temp_iterator();
		reference operator*() const;
		pointer operator->() const;
		temp_iterator &operator++();
		temp_iterator operator++(int);
		temp_iterator &operator--();
		temp_iterator operator--(int);
		bool operator==(const temp_iterator &) const;
		bool operator!=(const temp_iterator &) const;
	};

	using iterator = temp_iterator<false>;
	using const_iterator = temp_iterator<true>;

	//Constructors, destructor, and assignment operator

	Container();
	Container(unsigned int,
	          const T & = T());
	Container(const Container &);
	Container(Container &&);
	template<typename InputIterator>
	Container(InputIterator,
	          InputIterator);
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

	void push_front(const DeepPtr<T> &);
	void push_front(DeepPtr<T> &&);
	void push_front(const T &);
	void push_front(T &&);
	void push_back(const DeepPtr<T> &);
	void push_back(DeepPtr<T> &&);
	void push_back(const T &);
	void push_back(T &&);
	void pop_front();
	void pop_back();
	iterator insert(const_iterator,
					const DeepPtr<T> &);
	iterator insert(const_iterator,
					DeepPtr<T> &&);
	iterator insert(const_iterator,
	                const T &);
	iterator insert(const_iterator,
	                T &&);
	template<typename InputIterator>
	iterator insert(const_iterator,
	                InputIterator,
	                InputIterator);
	iterator erase(iterator);
	iterator erase(iterator,
	               iterator);
	static void swap(const iterator &,
	                 const iterator &);
	void swap(Container &);
	void give(const iterator &,
			  Container &,
			  const const_iterator &);

	void clear();

	//Finding

	iterator find(const T &);
	const_iterator find(const T &) const;
	//the parameter should be a function pointer, a functor or a lambda expression taking one parameter of type const T& and returning bool


	template<typename Pred>
	iterator find_if(Pred);
	template<typename Pred>
	const_iterator find_if(Pred) const;
	//Comparison operators

	bool operator==(const Container &);
	bool operator!=(const Container &);
};

//Node methods definition
template<typename T>
Container<T>::Node::Node(const DeepPtr<T> &t,
						 Node *n,
						 Node *p):
	info(t),
	next(n),
	prev(p)
{

}

template<typename T>
Container<T>::Node::Node(DeepPtr<T> &&t,
						 Node *n,
						 Node *p):
	info(t),
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
void Container<T>::push_front(const DeepPtr<T> &t)
{
	insert(cbegin(), t);
}

template<typename T>
void Container<T>::push_front(DeepPtr<T> &&t)
{
	insert(cbegin(), t);
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
void Container<T>::push_back(const DeepPtr<T> &t)
{
	insert(cend(), t);
}

template<typename T>
void Container<T>::push_back(DeepPtr<T> &&t)
{
	insert(cend(), t);
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
	erase(begin());
}

template<typename T>
void Container<T>::pop_back()
{
	erase(--end());
}

template<typename T>
typename Container<T>::iterator
Container<T>::insert(const_iterator position,
					 const DeepPtr<T> &t)
{
	Node *aux = new Node(t, position.pointing, position.pointing->prev);
	position.pointing->prev = aux;

	if (position != cbegin())
		aux->prev->next = aux;
	else
		first = aux;

	return iterator(aux);
}

template<typename T>
typename Container<T>::iterator
Container<T>::insert(const_iterator position,
					 DeepPtr<T> &&t)
{
	Node *aux = new Node(t, position.pointing, position.pointing->prev);
	position.pointing->prev = aux;

	if (position != cbegin())
		aux->prev->next = aux;
	else
		first = aux;

	return iterator(aux);
}

template<typename T>
typename Container<T>::iterator
Container<T>::insert(const_iterator position,
                     const T &t)
{
	Node *aux = new Node(t, position.pointing, position.pointing->prev);
	position.pointing->prev = aux;

	if (position != cbegin())
		aux->prev->next = aux;
	else
		first = aux;

	return iterator(aux);
}

template<typename T>
typename Container<T>::iterator
Container<T>::insert(const_iterator position,
                     T &&t)
{
	Node *aux = new Node(t, position.pointing, position.pointing->prev);
	position.pointing->prev = aux;

	if (position != cbegin())
		aux->prev->next = aux;
	else
		first = aux;

	return iterator(aux);
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
void Container<T>::swap(Container &c)
{
	Node *ptr = c.first;
	c.first = first;
	first = ptr;

	ptr = c.past_the_end;
	c.past_the_end = past_the_end;
	past_the_end = ptr;

	unsigned int temp = c.size_;
	c.size_ = size_;
	size_ = temp;
}

template<typename T>
void Container<T>::give(const iterator &this_one,
						Container &to,
						const const_iterator &here)
{
	to.insert(here, std::move(this_one.pointing->info));

	//swap(from, iterator(aux));
	erase(this_one);
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
bool Container<T>::operator==(const Container<T> &c)
{
	if (size() != c.size())
		return false;

	if (empty() || this == &c)
		return true;

	return (*first) == *(c.first);
}

template<typename T>
bool Container<T>::operator!=(const Container<T> &c)
{
	return !((*this) == c);
}
#endif // CONTAINER_H
