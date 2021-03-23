#include "complex.h"


Complex Complex::operator+(const Complex &other) const
{
    Complex result;
    result.real = this->real + other.real;
    result.imag = this->imag + other.imag;

    return result;
}

Complex Complex::operator-(const Complex &other) const
{
    Complex result;
    result.real = this->real - other.real;
    result.imag = this->imag - other.imag;

    return result;
}

Complex Complex::operator*(const Complex &other) const
{
    Complex result;
    result.real = this->real * other.real - this->imag * other.imag;
    result.imag = this->real * other.imag + this->imag * other.real;

    return result;
}

void Complex::operator*=(double value)
{
    this->real *= value;
    this->imag *= value;
}


void Complex::swap(Complex &other)
{
    double temp = this->real;
    this->real = other.real;
    other.real = temp;
    temp = this->imag;
    this->imag = other.imag;
    other.imag = temp;
}