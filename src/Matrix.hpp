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

        Matrix(unsigned int nol=1, unsigned int noc=1, T value=T(0); // constructor
        Matrix(const Matrix<T> &input); // copy constructor
        Matrix(Matrix<T> &&input); // move constructor
        Matrix& operator= (const Matrix<T> &input); // copy assignement
        Matrix& operator= (Matrix<T> &&input); // move assignement
        ~Matrix(); // destructor

        inline unsigned int sizel() const {return NumberOfLine;}
        inline unsigned int sizec() const {return NumberOfColumn;}
        void resize(unsigned int nol, unsigned int noc);
        void reset(T nv=T(0));
    private:
        unsigned int NumberOfLine;
        unsigned int NumberOfColumn;
}

template <class T>
Matrix<T>::Matrix(unsigned int nol, unsigned int noc, T value)
{
    NumberOfLine = nol;
    NumberOfColumn = noc;
    if ((nol == 0) || (noc == 0)) 
    {
        NumberOfLine = 0;
        NumberOfColumn = 0;
        data = nullptr;
    }
    else
    {
        data = new T*[NumberOfLine]();
        for (unsigned int k=0 ; k<NumberOfLine ; k++) {data[k] = new T[NumberOfColumn]();}
        for (unsigned int k=0 ; k<NumberOfLine ; k++) 
        {
            for (unsigned int l=0 ; l<NumberOfColumn ; l++) {data[k][l] = value;}
        }
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &input)
{
    if ( (input.NumberOfLine == 0) || (input.NumberOfColumn == 0) )
    {
        NumberOfLine = 0;
        NumberOfColumn = 0;
        data = nullptr;
    }
    else if (input.NumberOfLine == NumberOfLine)
    {
        if (input.NumberOfColumn != NumberOfColumn)
        {
            NumberOfColum = input.NumberOfColumn;
            for (unsigned int k=0 ; l<NumberOfLine ; k++)
            {
                delete[] data[k];
                data[k] = new T[NumberOfColumn]();
            }
        }
    }
    else
    {
        for (unsigned int k=0 ; k<NumberOfLine ; k++) {delete[] data[k];}
        NumberOfLine = input.NumberOfLine;
        NumberOfColumn = input.NumberOfColumn;
        delete[] data;
        data = new T*[NumberOfLine]();
        for (unsigned int k=0 ; k<NumberOfLine ; k++) {data[k] = new T[NumberOfColumn]();}
    }
    for (unsigned int k=0 ; k<NumberOfLine ; k++) 
    {
        for (unsigned int l=0 ; l<NumberOfColumn ; l++) {data[k][l] = input.data[k][l];}
    }
}

template <class T>
Matrix<T>::Matrix(Matrix<T> &&input)
{
    NumberOfLine = input.NumberOfLine;
    NumberOfColumn = input.NumberOfColumn;
    data = std::move(input.data);
    input.data = nullptr;
}

template <class T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T> &input)
{
    if ( (input.NumberOfLine == 0) || (input.NumberOfColumn == 0) )
    {
        NumberOfLine = 0;
        NumberOfColumn = 0;
        data = nullptr;
    }
    else if (input.NumberOfLine == NumberOfLine)
    {
        if (input.NumberOfColumn != NumberOfColumn)
        {
            NumberOfColum = input.NumberOfColumn;
            for (unsigned int k=0 ; l<NumberOfLine ; k++)
            {
                delete[] data[k];
                data[k] = new T[NumberOfColumn]();
            }
        }
    }
    else
    {
        for (unsigned int k=0 ; k<NumberOfLine ; k++) {delete[] data[k];}
        NumberOfLine = input.NumberOfLine;
        NumberOfColumn = input.NumberOfColumn;
        delete[] data;
        data = new T*[NumberOfLine]();
        for (unsigned int k=0 ; k<NumberOfLine ; k++) {data[k] = new T[NumberOfColumn]();}
    }
    for (unsigned int k=0 ; k<NumberOfLine ; k++) 
    {
        for (unsigned int l=0 ; l<NumberOfColumn ; l++) {data[k][l] = input.data[k][l];}
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator= (Matrix<T> &&input)
{
    NumberOfLine = input.NumberOfLine;
    NumberOfColumn = input.NumberOfColumn;
    data = std::move(input.data);
    input.data = nullptr;   
    return *this;
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
