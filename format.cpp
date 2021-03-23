#include "format.h"
#include <iostream>
#include <cmath>

const double EPSILON = 1e-7;

vector scan()
{
    std::size_t size;
    std::cin >> size;
    vector result;
    result.reserve(size);

    for (std::size_t i = 0; i < size; ++i)
    {
        Complex number;
        std::cin >> number.real >> number.imag;
        result.push_back(number);
    }

    return result;
}

void print(const vector &sample)
{
    std::cout << sample.size() << "\n";

    for (std::size_t i = 0; i < sample.size(); ++i)
        std::cout << sample[i].real << " "
                  << sample[i].imag << "\n";
}

void divide(vector &sample, double value)
{
    value = 1 / value;

    for (std::size_t i = 0; i < sample.size(); ++i)
        sample[i] *= value;
}

void removeEpsilonNoise(vector &sample)
{
    for (std::size_t i = 0; i < sample.size(); ++i)
    {
        if (std::abs(sample[i].real) < EPSILON)
            sample[i].real = 0;

        if (std::abs(sample[i].imag) < EPSILON)
            sample[i].imag = 0;
    }
}