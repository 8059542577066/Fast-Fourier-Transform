#include "fourier.h"
#include <stdexcept>

typedef std::invalid_argument error;
const double PI = 3.14159265358979323846;

vector Fourier::slice(const vector &sample, std::size_t first)
{
    vector result;
    result.reserve(sample.size() / 2);

    for (std::size_t i = first; i < sample.size(); i += 2)
        result.push_back(sample[i]);

    return result;
}

vector Fourier::transform(const vector &sample, std::size_t gap)
{
    if (sample.size() == 2)
    {
        vector result;
        result.reserve(2);
        result.push_back(sample[0] + sample[1]);
        result.push_back(sample[0] - sample[1]);

        return result;
    }

    vector tempEv = this->transform(this->slice(sample, 0), 2 * gap),
           tempOd = this->transform(this->slice(sample, 1), 2 * gap),
           result;
    result.reserve(sample.size());
    result.push_back(tempEv[0] + tempOd[0]);

    for (std::size_t i = 1, j = gap; i < tempEv.size(); ++i, j += gap)
        result.push_back(tempEv[i] + this->lookup[j] * tempOd[i]);

    result.push_back(tempEv[0] - tempOd[0]);

    for (std::size_t i = 1, j = gap; i < tempOd.size(); ++i, j += gap)
        result.push_back(tempEv[i] - this->lookup[j] * tempOd[i]);

    return result;
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
    this->lookup.reserve(lookupLimit);

    for (int i = 0; i < lookupLimit; ++i)
    {
        Complex number;
        number.real = std::cos(2 * i * PI / this->size);
        number.imag = sign * std::sin(2 * i * PI / this->size);
        this->lookup.push_back(number);
    }
}

vector Fourier::transform(const vector &sample)
{
    if (sample.size() != this->size)
        throw error("Sample & DFT matrix sizes are different.");

    return this->transform(sample, 1);
}