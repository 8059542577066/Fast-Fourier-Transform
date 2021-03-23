#ifndef COMPLEX_H
#define COMPLEX_H


struct Complex
{
    double real;
    double imag;

    Complex operator+(const Complex &) const;
    Complex operator-(const Complex &) const;
    Complex operator*(const Complex &)const;
    void operator*=(double);

    void swap(Complex &);
};


#endif