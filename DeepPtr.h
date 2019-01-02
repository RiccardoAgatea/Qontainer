#ifndef DEEPPTR_H
#define DEEPPTR_H


//T is required to define a T* clone() method (necessary to simulate a virtual copy constructor)

template<typename T> class DeepPtr;

template<typename T> bool operator==(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2);
template<typename T> bool operator!=(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2);

template<typename T>
class DeepPtr
{
public:
    T *ptr;

    //The DeepPtr constructed points to copy of the T object passed as parameter
    explicit DeepPtr(const T *t = nullptr);
    explicit DeepPtr(const T &t);

    //The copy constructor performs a deep copy (as does the copy assignment operator)
    DeepPtr(const DeepPtr &dp);

    DeepPtr(DeepPtr &&dp);
    ~DeepPtr();
    DeepPtr &operator=(const DeepPtr &dp);
    DeepPtr &operator=(DeepPtr &&dp);
    T &operator*() const;
    T *operator->() const;

    //the takeResponsibility methods return a new DeepPtr that points to the object passed as parameter (NOT a copy of it). This means that the returned DeepPtr from that point on will manage this object, and will also destroy it automatically. Destroying the object through different means (an explicit call to delete, for example) causes undefined behaviour
    static DeepPtr takeResponsibility(T *t);
    static DeepPtr takeResponsibility(T &t);

    friend bool operator== <T>(const DeepPtr &dp1, const DeepPtr &dp2);
    friend bool operator!= <T>(const DeepPtr &dp1, const DeepPtr &dp2);
};

template<typename T>
DeepPtr<T>::DeepPtr(const T *t):
    ptr(t != nullptr ? t->clone() : nullptr)
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

        ptr = dp.ptr != nullptr ? dp.ptr->clone() : nullptr;
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
DeepPtr<T> DeepPtr<T>::takeResponsibility(T *t)
{
    DeepPtr aux;

    aux.ptr = t;

    return aux;
}

template<typename T>
DeepPtr<T> DeepPtr<T>::takeResponsibility(T &t)
{
    return takeResponsibility(&t);
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
