#ifndef FOURIER_H
#define FOURIER_H

#include "complex.h"
#include <cmath>

class Fourier
{
private:
    std::size_t size;
    bool *copyFlag;
    Complex *lookup;

    std::size_t reverseBits(std::size_t);
    void copyButterfly(Complex *);
    void transform(Complex *, std::size_t);

public:
    Fourier(std::size_t, bool);
    ~Fourier();
    void transform(Complex *);
};

#endif