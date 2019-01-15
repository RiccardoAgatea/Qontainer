#ifndef CONTAINER_H
#define CONTAINER_H
#include <initializer_list>
#include <algorithm>
#include "DeepPtr.h"

//T is required to provide a T* clone() const method, which should have the standard behaviour for polymorphic clonation (specifically, it should return a pointer to a copy on the heap of the calling object, the destruction of which is responsibility of the Container object)

template<typename T> class Container;

template<typename T> bool operator==(const Container<T> &q1, const Container<T> &q2);
template<typename T> bool operator!=(const Container<T> &q1, const Container<T> &q2);

template <typename T>
class Container
{
private:
    struct Node
    {
        DeepPtr<T> info;
        Node *next, *prev;

        Node(DeepPtr<T> dp = DeepPtr<T>(), Node *n = nullptr, Node *p = nullptr);

        //Post: prev points to the last Node of the linked list that's being built
        Node(const Node &n);

        ~Node();

        //PRE: *this and n are in different Container objects of the same size
        bool operator==(const Node &n) const;
    };

    Node *first, *last;
    unsigned int size_;
public:
    class iterator
    {
        friend class Container;
    private:
        Node *pointing;

        iterator(Node *n);
    public:
        iterator();
        T &operator*() const;
        T *operator->() const;
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        bool operator==(const iterator &it) const;
        bool operator!=(const iterator &it) const;
    };

    class const_iterator
    {
        friend class Container;
    private:
        Node *pointing;

        const_iterator(Node *n);
    public:
        const_iterator();
        const T &operator*() const;
        const T *operator->() const;
        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator &operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
    };

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

    //Size and capacity
    unsigned int size() const;
    bool empty() const;

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
    iterator insert(const iterator &position, const T &t);
    template<typename InputIterator>
    iterator insert(iterator position, InputIterator first, InputIterator last);
    iterator erase(const iterator &position);
    iterator erase(const iterator &first, const iterator &last);
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
    //Check for existence of T* clone() const method
    T* (T::*test)() const = T::clone;

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

//iterator methods definition
template<typename T>
Container<T>::iterator::iterator(Node *n):
    pointing(n)
{

}

template<typename T>
Container<T>::iterator::iterator()
{

}

template<typename T>
T &Container<T>::iterator::operator*() const
{

}

template<typename T>
T *Container<T>::iterator::operator->() const
{

}

template<typename T>
typename Container<T>::iterator &Container<T>::iterator::operator++()
{

}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator++(int)
{

}

template<typename T>
typename Container<T>::iterator &Container<T>::iterator::operator--()
{

}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator--(int)
{

}

template<typename T>
bool Container<T>::iterator::operator==(const iterator &it) const
{

}

template<typename T>
bool Container<T>::iterator::operator!=(const iterator &it) const
{

}

//const_iterator methods definition
template<typename T>
Container<T>::const_iterator::const_iterator(Node *n)
{

}

template<typename T>
Container<T>::const_iterator::const_iterator()
{

}

template<typename T>
const T &Container<T>::const_iterator::operator*() const
{

}

template<typename T>
const T *Container<T>::const_iterator::operator->() const
{

}

template<typename T>
typename Container<T>::const_iterator &Container<T>::const_iterator::operator++()
{

}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int)
{

}

template<typename T>
typename Container<T>::const_iterator &Container<T>::const_iterator::operator--()
{

}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int)
{

}

template<typename T>
bool Container<T>::const_iterator::operator==(const const_iterator &it) const
{

}

template<typename T>
bool Container<T>::const_iterator::operator!=(const const_iterator &it) const
{

}

//Container method definitions
template<typename T>
Container<T>::Container():
    first(nullptr),
    last(nullptr)
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
    last(first != nullptr ? first->prev : nullptr)
{
    if (first != nullptr)
        first->prev = nullptr;
}

template<typename T>
Container<T>::Container(Container &&q):
    first(q.first),
    last(q.last)
{
    q.first = nullptr;
    q.last = nullptr;
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

}

template<typename T>
typename Container<T>::const_iterator Container<T>::begin() const
{

}

template<typename T>
typename Container<T>::const_iterator Container<T>::cbegin() const
{

}

template<typename T>
typename Container<T>::iterator Container<T>::end()
{

}

template<typename T>
typename Container<T>::const_iterator Container<T>::end() const
{

}

template<typename T>
typename Container<T>::const_iterator Container<T>::cend() const
{

}

template<typename T>
unsigned int Container<T>::size() const
{
    return size_;
}

template<typename T>
bool Container<T>::empty() const
{
    return size() == 0;
}

template<typename T>
T &Container<T>::front()
{
    return *(first->info);
}

template<typename T>
const T &Container<T>::front() const
{
    return *(first->info);
}

template<typename T>
T &Container<T>::back()
{
    return *(last->info);
}

template<typename T>
const T &Container<T>::back() const
{
    return *(last->info);
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
typename Container<T>::iterator Container<T>::insert(const iterator &position, const T &t)
{

}

template<typename T>
template<typename InputIterator>
typename Container<T>::iterator Container<T>::insert(iterator position, InputIterator first,
        InputIterator last)
{

}

template<typename T>
typename Container<T>::iterator Container<T>::erase(const iterator &position)
{

}

template<typename T>
typename Container<T>::iterator Container<T>::erase(const iterator &first, const iterator &last)
{

}

template<typename T>
void Container<T>::swap(const iterator &it1, const iterator &it2) const
{

}

template<typename T>
void Container<T>::swap(Container &q)
{
    Node *temp = q.first;
    q.first = first;
    first = temp;

    temp = q.last;
    q.last = last;
    last = temp;
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
