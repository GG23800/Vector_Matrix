#ifndef VECTOR_HPP
#define VECTOR_HPP

/*
 * Author: Jérôme Dubois
 * Creation: 03/2022
 * Version: 1.0
 *
 *
 */


#include<new> 
#include<cstdint> 
#include<complex>

template <class T>
class Vector
{
    public:
        T *data;

        Vector(unsigned int noe=1, T value=T(0);
        ~Vector();

        inline unsigned int size() const {return NumberOfElement;}
        void resize(unsigned int noe);
        void reset(T nv);
    private:
        unsigned int NumberOfElement;
}

template <class T>
Vector<T>::Vector(unsigned int noe, T value)
{
    NumberOfElement = noe;
    if (noe == 0) {data = nullptr;}
    else
    {
        data = new T[NumberOfElemet]();
        for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = value;}
    }
}

template <class T>
Vector<T>::~Vector()
{
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
}

template <class T>
Vector<T>::resize(unsigned int noe)
{
    if (noe == 0) {noe = 1;} // we forbid to resize to 0
    if (NumberOfElement != noe)
    {
        NumberOfElement = noe;
        if (data == nullptr) {data = new T[N]();}
        else
        {
            delete[] data;
            data = new T[NumberOfElement]();
        }
    }
}

template <class T>
Vector<T>::reset(T nv)
{
    for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = nv;}
}

#endif
