#include "fourier.h"
#include "..\..\format.h"
#include <iostream>
#include <iomanip>
#include <ctime>

int main()
{
    std::cout << std::setprecision(14);
    std::ios_base::sync_with_stdio(false);

    vector sample = scan();
    vector ffted, iffted;

    {
        time_t begin = clock();
        Fourier fourier(sample.size(), false);
        ffted = fourier.transform(sample);
        time_t end = clock();

        std::cerr << "FFT Time Taken: "
                  << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    }

    {
        time_t begin = clock();
        Fourier fourier(ffted.size(), true);
        iffted = fourier.transform(ffted);
        divide(iffted, iffted.size());
        time_t end = clock();

        std::cerr << "IFFT Time Taken: "
                  << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    }

    removeEpsilonNoise(iffted);
    print(iffted);

    return 0;
}