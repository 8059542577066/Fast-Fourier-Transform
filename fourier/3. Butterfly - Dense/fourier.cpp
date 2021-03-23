#include "fourier.h"
#include <stdexcept>

typedef std::invalid_argument error;
const double PI = 3.14159265358979323846;

std::size_t Fourier::reverseBits(std::size_t index)
{
    std::size_t selecter = 1, temp, result = 0;
    int bitSize = 0,
        maxBitSize = sizeof(std::size_t) << 3,
        lastBitNum = maxBitSize - 1;

    for (std::size_t size = this->size; size > 1; size >>= 1)
        ++bitSize;

    for (int i = 0; i < bitSize; ++i)
    {
        temp = selecter & index ? 1 : 0;
        result |= temp << (lastBitNum - i);
        selecter <<= 1;
    }

    return result >> (maxBitSize - bitSize);
}

void Fourier::copyButterfly(Complex *sample)
{
    for (std::size_t i = 0; i < this->size; ++i)
        this->temp[i] = sample[reverseBits(i)];
}

void Fourier::transform(Complex *sample, std::size_t gap)
{
    if (gap == this->size)
        return;

    this->transform(sample, gap << 1);
    std::size_t full = this->size / gap;

    for (std::size_t first = 0; first < this->size; first += full)
    {
        std::size_t half = full >> 1,
                    iEv = first, iOd = first | half, iW = 0;

        for (std::size_t i = 0; i < half; ++i)
        {
            sample[iEv] = this->temp[iEv] +
                          this->temp[iOd] * this->lookup[iW];
            sample[iOd] = this->temp[iEv] -
                          this->temp[iOd] * this->lookup[iW];
            ++iEv, ++iOd, iW += gap;
        }

        if (gap > 1)
            for (std::size_t i = 0, j = first; i < full; ++i, ++j)
                this->temp[j] = sample[j];
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
    this->copyButterfly(sample);
    this->transform(sample, 1);
}