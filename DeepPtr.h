#ifndef DEEPPTR_H
#define DEEPPTR_H
template<typename T> class DeepPtr;

template<typename T> bool operator==(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2);
template<typename T> bool operator!=(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2);

template<typename T>
class DeepPtr
{
public:
    T *ptr;

    explicit DeepPtr(const T *t = nullptr);
    explicit DeepPtr(const T &t);
    DeepPtr(const DeepPtr &dp);
    DeepPtr(DeepPtr &&dp);
    ~DeepPtr();
    DeepPtr &operator=(const DeepPtr &dp);
    DeepPtr &operator=(DeepPtr &&dp);
    T &operator*() const;
    T *operator->() const;
    friend bool operator== <T>(const DeepPtr &dp1, const DeepPtr &dp2);
    friend bool operator!= <T>(const DeepPtr &dp1, const DeepPtr &dp2);
};

template<typename T>
DeepPtr<T>::DeepPtr(const T *t):
    ptr(t != nullptr ? new T(*t) : nullptr)
{

}

template<typename T>
DeepPtr<T>::DeepPtr(const T &t):
    DeepPtr<T>(&t)
{

}

template<typename T>
DeepPtr<T>::DeepPtr(const DeepPtr<T> &dp):
    DeepPtr<T>(dp.ptr)
{

}

template<typename T>
DeepPtr<T>::DeepPtr(DeepPtr<T> &&dp):
    ptr(dp.ptr)
{
    dp.ptr = nullptr;
}

template<typename T>
DeepPtr<T>::~DeepPtr<T>()
{
    delete ptr;
}

template<typename T>
DeepPtr<T> &DeepPtr<T>::operator=(const DeepPtr<T> &dp)
{
    if (this != &dp)
    {
        delete ptr;

        ptr = dp.ptr != nullptr ? new T(*dp.ptr) : nullptr;
    }

    return *this;
}

template<typename T>
DeepPtr<T> &DeepPtr<T>::operator=(DeepPtr &&dp)
{
    delete ptr;

    ptr = dp.ptr;
    dp.ptr = nullptr;

    return *this;
}

template<typename T>
T &DeepPtr<T>::operator*() const
{
    return *ptr;
}

template<typename T>
T *DeepPtr<T>::operator->() const
{
    return ptr;
}

template<typename T>
bool operator==(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2)
{
    return *(dp1.ptr) == *(dp2.ptr);
}

template<typename T>
bool operator!=(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2)
{
    return !(dp1 == dp2);
}
#endif // DEEPPTR_H
