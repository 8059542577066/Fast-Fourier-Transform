#ifndef FOURIER_H
#define FOURIER_H

#include "..\..\complex.h"
#include <vector>
#include <cmath>

typedef std::vector<Complex> vector;

class Fourier
{
private:
    std::size_t size;
    vector lookup;

    vector slice(const vector &, std::size_t);
    vector transform(const vector &, std::size_t);

public:
    Fourier(std::size_t, bool);
    vector transform(const vector &);
};

#endif