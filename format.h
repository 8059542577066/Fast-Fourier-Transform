#ifndef FORMAT_H
#define FORMAT_H

#include "complex.h"
#include <vector>


typedef std::vector<Complex> vector;

vector scan();
void print(const vector &);
void divide(vector &, double);
void removeEpsilonNoise(vector &);


#endif