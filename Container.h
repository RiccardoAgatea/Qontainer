#ifndef CONTAINER_H
#define CONTAINER_H
#include<initializer_list>
#include<algorithm>
#include"DeepPtr.h"

template<typename T> class Container;

template<typename T> bool operator==(const Container<T> &q1, const Container<T> &q2);
template<typename T> bool operator!=(const Container<T> &q1, const Container<T> &q2);

template <typename T>
class Container
{
private:
    unsigned int capacity_, size_;
    DeepPtr<T> *vector;

    //INV = size_<=capacity_
public:
    class iterator
    {
        friend class Container;
    private:
        DeepPtr<T> *pointing;

        iterator(DeepPtr<T> *dp);
    public:
        iterator();
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) = default;
        T &operator*() const;
        T *operator->() const;
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        bool operator==(const iterator &it) const;
        bool operator!=(const iterator &it) const;
        iterator operator+(unsigned int k) const;
        iterator operator-(unsigned int k) const;

        //it should be an iterator in the same Container object as *this
        unsigned int operator-(const iterator &it);
    };

    class const_iterator
    {
        friend class Container;
    private:
        DeepPtr<T> *pointing;

        const_iterator(DeepPtr<T> *dp);
    public:
        const_iterator();
        const_iterator(const const_iterator &) = default;
        const_iterator(const_iterator &&) = default;
        const_iterator &operator=(const const_iterator &) = default;
        const_iterator &operator=(const_iterator &&) = default;
        const T &operator*() const;
        const T *operator->() const;
        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator &operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
        const_iterator operator+(unsigned int k) const;
        const_iterator operator-(unsigned int k) const;

        //it should be a const_iterator in the same Qontainer object as *this
        unsigned int operator-(const const_iterator &it);
    };

    //Constructors, destructor, and assignment operator
    Container(unsigned int n = 0, const T &t = T());
    Container(const Container &q);
    Container(Container &&q);
    template<typename InputIterator>
    Container(InputIterator first, InputIterator last);
    Container(std::initializer_list<const T &> init);
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
    unsigned int capacity() const;
    bool empty() const;

    //Access
    T &operator[](unsigned int k);
    const T &operator[](unsigned int k) const;
    T &at(unsigned int k);
    const T &at(unsigned int k) const;
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;

    //Content modification
    void push_back(const T &t);
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

template<typename T>
Container<T>::Container(unsigned int n, const T &t):
    capacity_(n > 0 ? 1 : 0),
    size_(n)
{
    while (capacity_ < size_)
        capacity_ *= 2;

    vector = capacity_ > 0 ? new DeepPtr<T>[capacity_] : nullptr;

    for (int i = 0; i < size_; ++i)
        vector[i] = t;
}

//what if I define this in terms of the assignment?
//in the initialization list:
//    vector(nullptr)
//and then in the body:
//    *this = q;
template<typename T>
Container<T>::Container(const Container &q):
    capacity_(q.capacity_),
    size_(q.size_),
    vector(capacity_ > 0 ? new DeepPtr<T>[capacity_] : nullptr)
{
    for (int i = 0; i < size_; ++i)
        vector[i] = q.vector[i];
}

template<typename T>
Container<T>::Container(Container &&q):
    capacity_(q.capacity_),
    size_(q.size_),
    vector(q.vector)
{
    q.capacity_ = 0;
    q.size_ = 0;
    q.vector = nullptr;
}

template<typename T>
template<typename InputIterator>
Container<T>::Container(InputIterator first, InputIterator last):
    Container()
{
    for (auto it = first; it != last; ++it)
        push_back(*it);
}

template<typename T>
Container<T>::Container(std::initializer_list<const T &> init):
    capacity_(1),
    size_(init.size())
{
    while (capacity_ < size_)
        capacity_ *= 2;

    vector = new DeepPtr<T>[capacity_];

    int i = 0;

    for (auto it = init.begin(); it != init.end(); ++it, ++i)
        vector[i] = *it;
}

template<typename T>
Container<T>::~Container()
{
    delete[] vector;
}

template<typename T>
Container<T> &Container<T>::operator=(const Container &q)
{
    if (this != &q)
    {
        delete[] vector;

        capacity_ = q.capacity_;
        size_ = q.size_;
        vector = capacity_ > 0 ? new DeepPtr<T>[capacity_] : nullptr;

        for (int i = 0; i < size_; ++i)
            vector[i] = q.vector[i];
    }

    return *this;
}

template<typename T>
Container<T> &Container<T>::operator=(Container &&q)
{
    delete[] vector;

    capacity_ = q.capacity_;
    size_ = q.size_;
    vector = q.vector;

    q.capacity_ = 0;
    q.size_ = 0;
    q.vector = nullptr;

    return *this;
}

template<typename T>
typename Container<T>::iterator Container<T>::begin()
{
    return iterator(vector);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::begin() const
{
    return const_iterator(vector);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::cbegin() const
{
    return const_iterator(vector);
}

template<typename T>
typename Container<T>::iterator Container<T>::end()
{
    return iterator(vector + size_);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::end() const
{
    return const_iterator(vector + size_);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::cend() const
{
    return const_iterator(vector + size_);
}

template<typename T>
unsigned int Container<T>::size() const
{
    return size_;
}

template<typename T>
unsigned int Container<T>::capacity() const
{
    return capacity_;
}

template<typename T>
bool Container<T>::empty() const
{
    return size() == 0;
}

template<typename T>
T &Container<T>::operator[](unsigned int k)
{
    return *(vector[k]);
}

template<typename T>
const T &Container<T>::operator[](unsigned int k) const
{
    return *(vector[k]);
}

template<typename T>
T &Container<T>::at(unsigned int k)
{
    /*if(k>=size_)
        throw out_of_range();*/

    return (*this)[k];
}

template<typename T>
const T &Container<T>::at(unsigned int k) const
{
    /*if(k>=size_)
        throw out_of_range();*/

    return (*this)[k];
}

template<typename T>
T &Container<T>::front()
{
    return *(begin());
}

template<typename T>
const T &Container<T>::front() const
{
    return *(begin());
}

template<typename T>
T &Container<T>::back()
{
    return *(--end());
}

template<typename T>
const T &Container<T>::back() const
{
    return *(--end());
}

template<typename T>
void Container<T>::push_back(const T &t)
{
    if (capacity_ == 0)
    {
        capacity_ = 1;

        vector = new DeepPtr<T>[capacity_];
    }
    else if (size_ == capacity_)
    {
        capacity_ = capacity_ * 2;

        DeepPtr<T> *aux = new DeepPtr<T>[capacity_];

        std::move(vector, vector + size_, aux);

        delete[] vector;
        vector = aux;
    }

    vector[size_] = t;
    ++size_;
}

template<typename T>
void Container<T>::pop_back()
{
    --size_;
}

template<typename T>
typename Container<T>::iterator Container<T>::insert(const iterator &position, const T &t)
{
    if (size_ == capacity_)
    {
        capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;

        DeepPtr<T> *aux = new DeepPtr<T>[capacity_];

        std::move(begin(), position + 1, aux);
        aux[position - begin()] = t;
        std::move(position + 1, end(), aux + (position - begin()));

        delete[] vector;
        vector = aux;
    }
    else
    {
        std::move_backward(position + 1, end(), end() + 1);
        *(position + 1) = t;
    }
}

template<typename T>
template<typename InputIterator>
typename Container<T>::iterator Container<T>::insert(iterator position,
        InputIterator first,
        InputIterator last)
{
    for (auto it = first; it != last; ++it)
    {
        insert(position, *it);
        ++position;
    }
}

template<typename T>
typename Container<T>::iterator Container<T>::erase(const iterator &position)
{
    std::move(position + 1, end(), position);
}

template<typename T>
typename Container<T>::iterator Container<T>::erase(const iterator &first, const iterator &last)
{
    std::move(last + 1, end(), first);
}

template<typename T>
void Container<T>::swap(Container &q)
{
    {
        unsigned int temp;

        temp = q.capacity_;
        q.capacity_ = capacity_;
        capacity_ = temp;

        temp = q.size_;
        q.size_ = size_;
        size_ = temp;
    }

    auto temp = q.vector;
    q.vector = vector;
    vector = temp;
}

template<typename T>
void Container<T>::swap(const iterator &it1, const iterator &it2) const
{
    DeepPtr<T> temp = std::move(*(it1.pointing));
    *(it1.pointing) = std::move(*(it2.pointing));
    *(it2.pointing) = std::move(temp);
}

template<typename T>
void Container<T>::clear()
{
    erase(begin(), end());
}

template<typename T>
bool operator==(const Container<T> &q1, const Container<T> &q2)
{
    if (q1.size() != q2.size())
        return false;

    for (int i = 0; i < q1.size(); ++i)
        if (q1[i] != q2[i])
            return false;

    return true;
}

template<typename T>
bool operator!=(const Container<T> &q1, const Container<T> &q2)
{
    return !(q1 == q2);
}

template<typename T>
typename Container<T>::iterator Container<T>::find(const T &t)
{
    return find_if([t](const T & x)->bool {return t == x;});
}

template<typename T>
typename Container<T>::const_iterator Container<T>::find(const T &t) const
{
    return find_if([t](const T & x)->bool {return t == x;});
}

template<typename T>
template<typename Pred>
typename Container<T>::iterator Container<T>::find_if(Pred p)
{
    for (auto it = begin(); it != end(); ++it)
        if (p(*it))
            return it;

    return end();
}

template<typename T>
template<typename Pred>
typename Container<T>::const_iterator Container<T>::find_if(Pred p) const
{
    for (auto it = cbegin(); it != cend(); ++it)
        if (p(*it))
            return it;

    return cend();
}

template<typename T>
void Container<T>::sort()
{
    sort([](const T & t1, const T & t2)->bool {return t1 < t2;});
}

template<typename T>
template<typename Pred>
void Container<T>::sort(Pred p)
{
    if (size_ >= 2)
    {
        bool flag = true;

        while (flag)
        {
            flag = false;

            for (auto it = begin(); it != end() - 1; ++it)
                if (!p(*it, *(it + 1)))
                {
                    swap(*it, *(it + 1));
                    flag = true;
                }
        }
    }
}

template<typename T>
Container<T>::iterator::iterator(DeepPtr<T> *dp):
    pointing(dp)
{

}

template<typename T>
Container<T>::iterator::iterator():
    iterator(nullptr)
{

}

template<typename T>
T &Container<T>::iterator::operator*() const
{
    return **pointing;
}

template<typename T>
T *Container<T>::iterator::operator->() const
{
    return &(**pointing);
}

template<typename T>
typename Container<T>::iterator &Container<T>::iterator::operator++()
{
    ++pointing;

    return *this;
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator++(int)
{
    iterator aux(*this);

    ++(*this);

    return aux;
}

template<typename T>
typename Container<T>::iterator &Container<T>::iterator::operator--()
{
    --pointing;

    return *this;
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator--(int)
{
    iterator aux(*this);

    --(*this);

    return aux;
}

template<typename T>
bool Container<T>::iterator::operator==(const iterator &it) const
{
    return pointing == it.pointing;
}

template<typename T>
bool Container<T>::iterator::operator!=(const iterator &it) const
{
    return !(*this == it);
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator+(unsigned int k) const
{
    return iterator(pointing + k);
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator-(unsigned int k) const
{
    return iterator(pointing - k);
}

template<typename T>
unsigned int Container<T>::iterator::operator-(const iterator &it)
{
    return pointing - it.pointing;
}

template<typename T>
Container<T>::const_iterator::const_iterator(DeepPtr<T> *dp):
    pointing(dp)
{

}

template<typename T>
Container<T>::const_iterator::const_iterator():
    const_iterator(nullptr)
{

}

template<typename T>
const T &Container<T>::const_iterator::operator*() const
{
    return **pointing;
}

template<typename T>
const T *Container<T>::const_iterator::operator->() const
{
    return &(**pointing);
}

template<typename T>
typename Container<T>::const_iterator &Container<T>::const_iterator::operator++()
{
    ++pointing;

    return *this;
}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int)
{
    const_iterator aux(*this);

    ++(*this);

    return aux;
}

template<typename T>
typename Container<T>::const_iterator &Container<T>::const_iterator::operator--()
{
    --pointing;

    return *this;
}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int)
{
    const_iterator aux(*this);

    --(*this);

    return aux;
}

template<typename T>
bool Container<T>::const_iterator::operator==(const const_iterator &it) const
{
    return pointing == it.pointing;
}

template<typename T>
bool Container<T>::const_iterator::operator!=(const const_iterator &it) const
{
    return !(*this == it);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator+(unsigned int k) const
{
    return const_iterator(pointing + k);
}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator-(unsigned int k) const
{
    return const_iterator(pointing - k);
}


template<typename T>
unsigned int Container<T>::const_iterator::operator-(const const_iterator &it)
{
    return pointing - it.pointing;
}
#endif // CONTAINER_H
