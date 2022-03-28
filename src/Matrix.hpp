#ifndef MATRIX_HPP
#define MATRIX_HPP

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
class Matrix
{
    public:
        T **data;

        Matrix(unsigned int nol=1, unsigned int noc=1, T value=T(0);
        ~Matrix();

        inline unsigned int sizel() const {return NumberOfLine;}
        inline unsigned int sizec() const {return NumberOfColumn;}
        void resize(unsigned int nol, unsigned int noc);
        void reset(T nv);
    private:
        unsigned int NumberOfLine;
        unsigned int NumberOfColumn;
}

template <class T>
Matrix<T>::Matrix(unsigned int nol, unsigned int noc, T value)
{
    NumberOfLine = nol;
    NumberOfColumn = noc;
    if ((nol == 0) || (noc == 0)) {data = nullptr;}
    else
    {
        data = new T*[NumberOfLine]();
        for (unsigned int k=0 ; k<NumberOfLine ; k++) {data[k] = new T[NumberOfColumn];}
        for (unsigned int k=0 ; k<NumberOfLine ; k++) 
        {
            for (unsigned int l=0 ; l<NumberOfColumn ; l++) {data[k][l] = value;}
        }
    }
}

template <class T>
Matrix<T>::~Matrix()
{
    if (data != nullptr)
    {
        for (unsigned int k=0 ; k<NumberOfLine : k++)
        {
            delete[] data[k];
            data[k] = nullptr;
        }
        delete[] data;
        data = nullptr;
    }
}

template <class T>
Matrix<T>::resize(unsigned int nol, unsigned int noc)
{
    if (nol == 0) {nol = 1;}
    if (noc == 0) {noc = 1;} // we forbid resize to 0
    if (NumberOfLine == nol
    {
        if (NumberOfColumn != noc)
        {
            NumberOfColumn = noc;
            for (unsigned int k=0 ; k<NumberOfLine ; k++)
            {
                delete[] data[k];
                data[k] = new T[noc]();
            }
        }
    }
    else
    {
        for (unsigned int k=0 ; k<NumberOfLine ; k++)
        {
            delete[] data[k];
            data[k] = nullptr;
        }
        delete[] data;
        NumberOfLine = nol;
        NumberOfColumn = noc;
        data = new T*[NumberOfLine];
        for (unsigned int k=0 ; k<NumberOfLine ; k++) {data[k] = new T[NumberOfColumn]();}
    }
}

template <class T>
Matrix<T>::reset(T nv)
{
    for (unsigned int k=0 ; k<NumberOfLine ; k++) 
    {
        for (unsigned int l=0 ; l<NumberOfColumn ; l++) {data[k] = nv;}
    }
}

#endif
