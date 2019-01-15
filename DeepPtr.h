#ifndef DEEPPTR_H
#define DEEPPTR_H

//T is required to provide a T *clone() const method implementing the standard polymorphic cloning (specifically, returning a pointer to a T object allocated on the heap, the destruction of which is responsibility of the DeepPtr)

template<typename T> class DeepPtr;

template<typename T> bool operator==(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2);
template<typename T> bool operator!=(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2);

template<typename T>
class DeepPtr
{
private:
    T *ptr;
public:
    //The DeepPtr constructed points to copy of the T object passed as parameter
    explicit DeepPtr(const T *t = nullptr);

    //The copy constructor performs a deep copy (as does the copy assignment operator)
    DeepPtr(const DeepPtr &dp);

    DeepPtr(DeepPtr &&dp);
    ~DeepPtr();
    DeepPtr &operator=(const DeepPtr &dp);
    DeepPtr &operator=(DeepPtr &&dp);
    T &operator*() const;
    T *operator->() const;

    //the takeResponsibility method returns a new DeepPtr that points to the object passed as parameter (NOT a copy of it). This means that the returned DeepPtr from that point on will manage this object, and will also destroy it automatically. Destroying the object through different means (an explicit call to delete on the pointer passed as parameter, for example) causes undefined behaviour
    static DeepPtr takeResponsibility(T *t);

    //both comparison operators require T to overload operator==.
    //operator== returns true if dp1 and dp2 are both null, point to the same object, or if *dp1 == *dp2 returns true, false otherwise. operator!= has the expected behaviour.
    friend bool operator== <T>(const DeepPtr &dp1, const DeepPtr &dp2);
    friend bool operator!= <T>(const DeepPtr &dp1, const DeepPtr &dp2);
};

template<typename T>
DeepPtr<T>::DeepPtr(const T *t):
    ptr(t != nullptr ? t->clone() : nullptr)
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
bool operator==(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2)
{
    if (dp1.ptr == dp2.ptr)
        return true;

    if (dp1.ptr == nullptr || dp2.ptr == nullptr)
        return false;

    return *(dp1.ptr) == *(dp2.ptr);
}

template<typename T>
bool operator!=(const DeepPtr<T> &dp1, const DeepPtr<T> &dp2)
{
    return !(dp1 == dp2);
}
#endif // DEEPPTR_H
