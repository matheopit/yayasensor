#ifndef UTILS_SINGLETON_H
#define UTILS_SINGLETON_H


#include <stdio.h>

template <typename T>
class MGBasicSingleton
{
protected:
    MGBasicSingleton (){}
    virtual ~MGBasicSingleton (){}
public:
    static T *Instance ()
    {
        if (!_singleton)
        {
            if (!_singleton)
                _singleton = new T;

        }
        return (static_cast<T*> (_singleton));
    }

    static void DestroyObjects()
    {
        if (NULL != _singleton)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }
private:
    static T *_singleton;
};

template <typename T>
T *MGBasicSingleton<T>::_singleton = NULL;

#endif /* UTILS_SINGLETON_H */
