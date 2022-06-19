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
#include<iostream>
#include<random>

template <class T>
class Vector
{
    public:
        T *data;

        Vector(unsigned int noe=1, T value=T(0)); // constructor
        Vector(const Vector<T> &input); // copy constructor
        Vector(Vector<T> &&input); // move constructor
        Vector& operator= (const Vector<T> &input); // copy affectation
        Vector& operator= (Vector<T> &&input); // move affectation
        ~Vector(); // destructor

        inline unsigned int size() const {return NumberOfElement;}
        void resize(unsigned int noe);
        void reset(T nv=T(0));

        void linspace(T tstart, T tend); // linearly spaced values between tstart and tend
        void linspace(T tstart, T tend, unsigned int noe); // linearly spaced values between tstart and tend with resize
        void SetRandom(T tstart, T tend); // random distribution min and max value possible respectevely tstart and tend

    private:
        unsigned int NumberOfElement;
};

template <class T>
Vector<T>::Vector(unsigned int noe, T value)
{
    NumberOfElement = noe;
    if (noe == 0) {data = nullptr;}
    else
    {
        data = new T[NumberOfElement]();
        for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = value;}
    }
}

template <class T>
Vector<T>::Vector(const Vector<T> &input)
{
    if (input.NumberOfElement == 0)
    {
        NumberOfElement = 0;
        delete[] data;
        data = nullptr;
    }
    else if (input.NumberOfElement != NumberOfElement)
    {
        NumberOfElement = input.NumberOfElement;
        delete[] data;
        data = new T[NumberOfElement]();
    }
    for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = input.data[k];}
}

template <class T>
Vector<T>::Vector(Vector<T> &&input)
{
    NumberOfElement = input.NumberOfElement;
    data = std::move(input.data);
    input.data = nullptr;
}

template <class T>
Vector<T>& Vector<T>::operator= (const Vector<T> &input)
{
    if (input.NumberOfElement == 0)
    {
        NumberOfElement = 0;
        delete[] data;
        data = nullptr;
    }
    else if (input.NumberOfElement != NumberOfElement)
    {
        NumberOfElement = input.NumberOfElement;
        delete[] data;
        data = new T[NumberOfElement];
    }
    for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = input.data[k];}
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator= (Vector<T> &&input)
{
    NumberOfElement = input.NumberOfElement;
    data = std::move(input.data);
    input.data = nullptr;
    return *this;
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
void Vector<T>::resize(unsigned int noe)
{
    if (noe == 0) {noe = 1;} // we forbid to resize to 0
    if (NumberOfElement != noe)
    {
        NumberOfElement = noe;
        if (data != nullptr) {delete[] data;}
        data = new T[NumberOfElement]();
    }
}

template <class T>
void Vector<T>::reset(T nv)
{
    for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = nv;}
}

template <class T>
void Vector<T>::linspace(T tstart, T tend)
{
    // See how to manage T not scalar?
    if (NumberOfElement > 1)
    {
        data[0] = tstart;
        data[NumberOfElement-1] = tend;
        double t0 = double(tstart);
        double deltax = double(tend-tstart)/double(NumberOfElement-1);
        for (unsigned int k=1 ; k<NumberOfElement-1 ; k++)
        {
            t0 += deltax;
            data[k] = T(t0);
        }
    }
    else
    {
        std::cout << "Warning, number of element of the vector is " << NumberOfElement << " we can't construct linearly space values" << std::endl;
    }
}

template <class T>
void Vector<T>::linspace(T tstart, T tend, unsigned int noe)
{
    resize(noe);
    linspace(tstart, tend);
}

template <class T>
void Vector<T>::SetRandom(T tstart, T tend)
{
    if (tstart == tend) {tend = tstart + T(1);}
    if (tend < tstart)
    {
        T tmp = tend;
        tend = tstart;
        tstart = tmp;
    }
    const double l0=double(tstart), lf=double(tend);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(l0, lf);//double(tstart), double(tend));
    for (unsigned int k=0 ; k<NumberOfElement ; k++)
    {
        data[k] = T( dist(gen) );
    }
}

#endif
