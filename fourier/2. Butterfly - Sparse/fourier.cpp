#include "fourier.h"
#include <stdexcept>

typedef std::invalid_argument error;
const double PI = 3.14159265358979323846;

void Fourier::transform(Complex *sample, std::size_t first, std::size_t gap)
{
    if (gap << 1 == this->size)
    {
        this->temp[first] = sample[first] + sample[first | gap];
        this->temp[first | gap] = sample[first] - sample[first | gap];
        sample[first] = this->temp[first];
        sample[first | gap] = this->temp[first | gap];
    }
    else
    {
        this->transform(sample, first, gap << 1);
        this->transform(sample, first | gap, gap << 1);
        std::size_t i = first, iEv = first, iOd = first | gap, iW = 0;

        while (iEv < this->size)
        {
            this->temp[i] = sample[iEv] + this->lookup[iW] * sample[iOd];
            i += gap, iEv += gap << 1, iOd += gap << 1, iW += gap;
        }

        iEv = first, iOd = first | gap, iW = 0;

        while (iOd < this->size)
        {
            this->temp[i] = sample[iEv] - this->lookup[iW] * sample[iOd];
            i += gap, iEv += gap << 1, iOd += gap << 1, iW += gap;
        }

        for (i = first; i < this->size; i += gap)
            sample[i] = this->temp[i];
    }
}

Fourier::Fourier(std::size_t size, bool inverse)
{
    std::size_t check = size;

    while ((check & 1) == 0)
        check >>= 1;

    if (check > 1)
        throw error("DFT matrix size should be power of 2.");

    this->size = size;
    int lookupLimit = this->size / 2,
        sign = inverse ? 1 : -1;
    this->lookup = new Complex[lookupLimit];
    this->temp = new Complex[this->size];

    for (int i = 0; i < lookupLimit; ++i)
    {
        Complex number;
        number.real = std::cos(2 * i * PI / this->size);
        number.imag = sign * std::sin(2 * i * PI / this->size);
        this->lookup[i] = number;
    }
}

Fourier::~Fourier()
{
    delete[] this->lookup;
    delete[] this->temp;
}

void Fourier::transform(Complex *sample)
{
    return this->transform(sample, 0, 1);
}