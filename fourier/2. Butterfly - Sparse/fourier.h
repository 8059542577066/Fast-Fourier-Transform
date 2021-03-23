#ifndef FOURIER_H
#define FOURIER_H

#include "..\..\complex.h"
#include <cmath>

class Fourier
{
private:
    std::size_t size;
    Complex *lookup;
    Complex *temp;

    void transform(Complex *, std::size_t, std::size_t);

public:
    Fourier(std::size_t, bool);
    ~Fourier();
    void transform(Complex *);
};

#endif