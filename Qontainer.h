#ifndef QONTAINER_H
#define QONTAINER_H
#include<initializer_list>
#include"DeepPtr.h"

template <typename T>
class Qontainer
{
private:
    unsigned int capacity_, size_;
    DeepPtr<T> *vector;
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
    };

    Qontainer(unsigned int n = 0, const T &t = T());
    Qontainer(const Qontainer &q);
    Qontainer(Qontainer &&q);
    Qontainer(std::initializer_list<T> init);
    ~Qontainer();
    Qontainer &operator=(const Qontainer &q);
    Qontainer &operator=(Qontainer &&q);
};

template<typename T>
Qontainer<T>::Qontainer(unsigned int n, const T &t):
    capacity_(n > 0 ? 1 : 0),
    size_(n),
    vector(new DeepPtr<T>[size_])
{
    for (int i = 0; i < size_; ++i)
        vector[i] = t;

    while (capacity_ < size_)
        capacity_ *= 2;
}

template<typename T>
Qontainer<T>::Qontainer(const Qontainer &q):
    capacity_(q.capacity_),
    size_(q.size_),
    vector(new DeepPtr<T>[size_])
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
Qontainer<T>::Qontainer(std::initializer_list<T> init):
    capacity_(1),
    size_(init.size_),
    vector(new DeepPtr<T>[size_])
{
    int i = 0;

    for (auto it = init.begin(); it != init.end(); ++it, ++i)
        vector[i] = *it;

    while (capacity_ < size_)
        capacity_ *= 2;
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
        vector = new DeepPtr<T>[size_];

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

    q.vector = nullptr;

    return *this;
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
#endif // QONTAINER_H
