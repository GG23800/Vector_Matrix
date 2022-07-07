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
        void clear();
        T min();
        T AbsMin();
        T max();
        T AbsMax();
        T mean();
        T modulus();
        T Sum();
        T AbsSum();

        void linspace(T tstart, T tend); // linearly spaced values between tstart and tend
        void linspace(T tstart, T tend, unsigned int noe); // linearly spaced values between tstart and tend with resize
        void SetRandom(T tstart, T tend); // random distribution min and max value possible respectevely tstart and tend

        void print();

    private:
        unsigned int NumberOfElement;
};

// declaration
// operator +


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
        data = nullptr;
    }
    else
    {
        NumberOfElement = input.NumberOfElement;
        data = new T[NumberOfElement]();
        for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = input.data[k];}
    }
}

template <class T>
Vector<T>::Vector(Vector<T> &&input)
{
    if (input.NumberOfElement == 0) {clear();}
    else
    {
        NumberOfElement = input.NumberOfElement;
        data = std::move(input.data);
        input.data = nullptr;
    }
}

template <class T>
Vector<T>& Vector<T>::operator= (const Vector<T> &input)
{
    if (input.NumberOfElement == 0)
    {
        clear();
    }
    else if (input.NumberOfElement != NumberOfElement)
    {
        NumberOfElement = input.NumberOfElement;
        if (data != nullptr) {delete[] data;}
        data = new T[NumberOfElement];
    }
    for (unsigned int k=0 ; k<NumberOfElement ; k++) {data[k] = input.data[k];}
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator= (Vector<T> &&input)
{
    NumberOfElement = input.NumberOfElement;
    if (data != nullptr) {delete[] data;}
    data = std::move(input.data);
    input.data = nullptr;
    return *this;
}

template <class T>
Vector<T>::~Vector()
{
    clear();
}

template <class T>
Vector<T> operator+ (const Vector<T> &left, const Vector<T> &right)
{
    if ( left.size() != right.size() )
    {
        std::cout << "Warning, trying to sum 2 vector that have different size. Returning left vector." << std::endl;
        return left;
    }
    else
    {
        Vector<T> output(left);
        for (unsigned int k=0 ; k<output.size() ; k++)
        {
            output.data[k] += right.data[k];
        }
        return output;
    }
}

template <class T>
Vector<T> operator- (const Vector<T> &left, const Vector<T> &right)
{
    if ( left.size() != right.size() )
    {
        std::cout << "Warning, trying to substarct 2 vector that have different size. Returning left vector." << std::endl;
        return left;
    }
    else
    {
        Vector<T> output(left);
        for (unsigned int k=0 ; k<output.size() ; k++)
        {
            output.data[k] -= right.data[k];
        }
        return output;
    }
}

template <class T>
void Vector<T>::resize(unsigned int noe)
{
    if (noe == 0) {clear();}
    else if (NumberOfElement != noe)
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
void Vector<T>::clear()
{
    NumberOfElement = 0;
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
}

template <class T>
T Vector<T>::min()
{
    T output = data[0];
    for (unsigned int k=1 ; k<NumberOfElement ; k++)
    {
        if (data[k] < output) {output = data[k];}
    }
    return output;
}

template <class T>
T Vector<T>::AbsMin()
{
    T output = std::abs(data[0]);
    for (unsigned int k=1 ; k<NumberOfElement ; k++)
    {
        if (std::abs(data[k]) < output) {output = std::abs(data[k]);}
    }
    return output;
}

template <class T>
T Vector<T>::max()
{
    T output = data[0];
    for (unsigned int k=1 ; k<NumberOfElement ; k++)
    {
        if (data[k] > output) {output = data[k];}
    }
    return output;
}

template <class T>
T Vector<T>::AbsMax()
{
    T output = std::abs(data[0]);
    for (unsigned int k=1 ; k<NumberOfElement ; k++)
    {
        if (std::abs(data[k]) > output) {output = std::abs(data[k]);}
    }
    return output;
}

template <class T>
T Vector<T>::mean()
{
    double sum = 0.0;
    for (unsigned int k=0 ; k<NumberOfElement ; k++)
    {
        sum += double( data[k] );
    }
    return T( sum/double(NumberOfElement) );
}

template <class T>
T Vector<T>::modulus()
{
    double sq = std::abs(data[0])*std::abs(data[0]);
    for(unsigned int k=0 ; k<NumberOfElement ; k++)
    {
        sq += std::abs(data[k])*std::abs(data[k]); //abs is here in case of complex number, need a specific overload function
    }
    return T( std::sqrt(sq) );
}

template <class T>
T Vector<T>::Sum()
{
    T output = T(0);
    for (unsigned int k=0 ; k<NumberOfElement ; k++)
    {
        output += data[k];
    }
    return output;
}

template <class T>
T Vector<T>::AbsSum()
{
    T output = T(0);
    for (unsigned int k=0 ; k<NumberOfElement ; k++)
    {
        output += std::abs(data[k]);
    }
    return output;
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

template <class T>
void Vector<T>::print()
{
    // TODO print T type?
    std::cout << "Vector with " << NumberOfElement << " elements:";
    for (unsigned int k=0 ; k<NumberOfElement ;  k++)
    {
        std::cout << " [" << k << "]=" << data[k];
    }
    std::cout << std::endl;
}

#endif
