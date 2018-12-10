#ifndef QONTAINER_H
#define QONTAINER_H
#include<initializer_list>
#include<algorithm>
#include"DeepPtr.h"

template<typename T> class Qontainer;

template<typename T> bool operator==(const Qontainer<T> &q1, const Qontainer<T> &q2);
template<typename T> bool operator!=(const Qontainer<T> &q1, const Qontainer<T> &q2);

template <typename T>
class Qontainer
{
private:
    unsigned int capacity_, size_;
    DeepPtr<T> *vector;

    //INV = size_<=capacity_
public:
    class iterator
    {
        friend class Qontainer;
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
    };

    class const_iterator
    {
        friend class Qontainer;
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
    };

    //Constructors, destructor, and assignment operator
    Qontainer(unsigned int n = 0, const T &t = T());
    Qontainer(const Qontainer &q);
    Qontainer(Qontainer &&q);
    Qontainer(std::initializer_list<const T &> init);
    ~Qontainer();
    Qontainer &operator=(const Qontainer &q);
    Qontainer &operator=(Qontainer &&q);

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
    T &operator[](unsigned int k) const;
    T &at(unsigned int k) const;
    T &front() const;
    T &back() const;

    //Content modification
    void push_back(const T &t);
    void pop_back();
    iterator insert(const iterator &position, const T &t);
    template<typename InputIterator>
    iterator insert(iterator position, InputIterator first, InputIterator last);
    iterator erase(const iterator &position);
    iterator erase(const iterator &first, const iterator &last);
    void swap(Qontainer &q);
    void clear();

    //Finding and Sorting
    iterator find(const T &t);
    template<typename Pred>
    iterator find(const T &t, Pred p);
    const_iterator find(const T &t) const;
    template<typename Pred>
    const_iterator find(const T &t, Pred p) const;
    void sort();
    template<typename Pred>
    void sort(Pred p);

    //Comparison operators
    friend bool operator== <T>(const Qontainer &q1, const Qontainer &q2);
    friend bool operator!= <T>(const Qontainer &q1, const Qontainer &q2);
};

template<typename T>
Qontainer<T>::Qontainer(unsigned int n, const T &t):
    capacity_(n > 0 ? 1 : 0),
    size_(n)
{
    while (capacity_ < size_)
        capacity_ *= 2;

    vector = capacity_ > 0 ? new DeepPtr<T>[capacity_] : nullptr;

    for (int i = 0; i < size_; ++i)
        vector[i] = t;
}

template<typename T>
Qontainer<T>::Qontainer(const Qontainer &q):
    capacity_(q.capacity_),
    size_(q.size_),
    vector(capacity_ > 0 ? new DeepPtr<T>[capacity_] : nullptr)
{
    for (int i = 0; i < size_; ++i)
        vector[i] = q.vector[i];
}

template<typename T>
Qontainer<T>::Qontainer(Qontainer &&q):
    capacity_(q.capacity_),
    size_(q.size_),
    vector(q.vector)
{
    q.capacity_ = 0;
    q.size_ = 0;
    q.vector = nullptr;
}

template<typename T>
Qontainer<T>::Qontainer(std::initializer_list<const T &> init):
    capacity_(1),
    size_(init.size_)
{
    while (capacity_ < size_)
        capacity_ *= 2;

    vector = new DeepPtr<T>[capacity_];

    int i = 0;

    for (auto it = init.begin(); it != init.end(); ++it, ++i)
        vector[i] = *it;
}

template<typename T>
Qontainer<T>::~Qontainer()
{
    delete[] vector;
}

template<typename T>
Qontainer<T> &Qontainer<T>::operator=(const Qontainer &q)
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
Qontainer<T> &Qontainer<T>::operator=(Qontainer &&q)
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
typename Qontainer<T>::iterator Qontainer<T>::begin()
{
    return iterator(vector);
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::begin() const
{
    return const_iterator(vector);
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::cbegin() const
{
    return const_iterator(vector);
}

template<typename T>
typename Qontainer<T>::iterator Qontainer<T>::end()
{
    return iterator(vector + size_);
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::end() const
{
    return const_iterator(vector + size_);
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::cend() const
{
    return const_iterator(vector + size_);
}

template<typename T>
unsigned int Qontainer<T>::size() const
{
    return size_;
}

template<typename T>
unsigned int Qontainer<T>::capacity() const
{
    return capacity_;
}

template<typename T>
bool Qontainer<T>::empty() const
{
    return size() == 0;
}

template<typename T>
T &Qontainer<T>::operator[](unsigned int k) const
{
    return vector[k];
}

template<typename T>
T &Qontainer<T>::at(unsigned int k) const
{
    /*if(k>=size_)
        throw out_of_range();*/

    return (*this)[k];
}

template<typename T>
T &Qontainer<T>::front() const
{
    return (*this)[0];
}

template<typename T>
T &Qontainer<T>::back() const
{
    return (*this)[size_ - 1];
}

template<typename T>
void Qontainer<T>::push_back(const T &t)
{
    if (size_ == capacity_)
    {
        capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;

        DeepPtr<T> *aux = new DeepPtr<T>[capacity_];

        std::move(vector, vector + size_, aux);

        delete[] vector;
        vector = aux;
    }

    vector[size_] = t;
    ++size_;

}

template<typename T>
void Qontainer<T>::pop_back()
{
    --size_;
}

template<typename T>
typename Qontainer<T>::iterator Qontainer<T>::insert(const iterator &position, const T &t)
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
typename Qontainer<T>::iterator Qontainer<T>::insert(iterator position,
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
typename Qontainer<T>::iterator Qontainer<T>::erase(const iterator &position)
{
    std::move(position + 1, end(), position);
}

template<typename T>
typename Qontainer<T>::iterator Qontainer<T>::erase(const iterator &first, const iterator &last)
{
    std::move(last + 1, end(), first);
}

template<typename T>
void Qontainer<T>::swap(Qontainer &q)
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
void Qontainer<T>::clear()
{
    erase(begin(), end());
}

template<typename T>
bool operator==(const Qontainer<T> &q1, const Qontainer<T> &q2)
{
    if (q1.size() != q2.size())
        return false;

    for (int i = 0; i < q1.size(); ++i)
        if (q1[i] != q2[i])
            return false;

    return true;
}

template<typename T>
bool operator!=(const Qontainer<T> &q1, const Qontainer<T> &q2)
{
    return !(q1 == q2);
}

template<typename T>
Qontainer<T>::iterator::iterator(DeepPtr<T> *dp):
    pointing(dp)
{

}

template<typename T>
Qontainer<T>::iterator::iterator():
    iterator(nullptr)
{

}

template<typename T>
T &Qontainer<T>::iterator::operator*() const
{
    return **pointing;
}

template<typename T>
T *Qontainer<T>::iterator::operator->() const
{
    return &(**pointing);
}

template<typename T>
typename Qontainer<T>::iterator &Qontainer<T>::iterator::operator++()
{
    ++pointing;

    return *this;
}

template<typename T>
typename Qontainer<T>::iterator Qontainer<T>::iterator::operator++(int)
{
    iterator aux(*this);

    ++(*this);

    return aux;
}

template<typename T>
typename Qontainer<T>::iterator &Qontainer<T>::iterator::operator--()
{
    --pointing;

    return *this;
}

template<typename T>
typename Qontainer<T>::iterator Qontainer<T>::iterator::operator--(int)
{
    iterator aux(*this);

    --(*this);

    return aux;
}

template<typename T>
bool Qontainer<T>::iterator::operator==(const iterator &it) const
{
    return pointing == it.pointing;
}

template<typename T>
bool Qontainer<T>::iterator::operator!=(const iterator &it) const
{
    return !(*this == it);
}

template<typename T>
typename Qontainer<T>::iterator Qontainer<T>::iterator::operator+(unsigned int k) const
{
    return iterator(pointing + k);
}

template<typename T>
typename Qontainer<T>::iterator Qontainer<T>::iterator::operator-(unsigned int k) const
{
    return iterator(pointing - k);
}

template<typename T>
Qontainer<T>::const_iterator::const_iterator(DeepPtr<T> *dp):
    pointing(dp)
{

}

template<typename T>
Qontainer<T>::const_iterator::const_iterator():
    const_iterator(nullptr)
{

}

template<typename T>
const T &Qontainer<T>::const_iterator::operator*() const
{
    return **pointing;
}

template<typename T>
const T *Qontainer<T>::const_iterator::operator->() const
{
    return &(**pointing);
}

template<typename T>
typename Qontainer<T>::const_iterator &Qontainer<T>::const_iterator::operator++()
{
    ++pointing;

    return *this;
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator++(int)
{
    const_iterator aux(*this);

    ++(*this);

    return aux;
}

template<typename T>
typename Qontainer<T>::const_iterator &Qontainer<T>::const_iterator::operator--()
{
    --pointing;

    return *this;
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator--(int)
{
    const_iterator aux(*this);

    --(*this);

    return aux;
}

template<typename T>
bool Qontainer<T>::const_iterator::operator==(const const_iterator &it) const
{
    return pointing == it.pointing;
}

template<typename T>
bool Qontainer<T>::const_iterator::operator!=(const const_iterator &it) const
{
    return !(*this == it);
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator+(unsigned int k) const
{
    return const_iterator(pointing + k);
}

template<typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator-(unsigned int k) const
{
    return const_iterator(pointing - k);
}
#endif // QONTAINER_H
