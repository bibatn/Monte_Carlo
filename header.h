#include <cstdio>
#include <cstdlib>
#include "mpi.h"
#include <cmath>
#include <stdint.h>
#include <cstring>

#define MASTER		0

const double I = M_PI / 6;
double VOLUME = M_PI / 3;
const uint64_t MAX_SAMPLES_COUNT = 10;
const uint64_t MAX_ITER_COUNT = 10000000;

int NODE_COUNT = 0;

double generate_values();
double f_func(double x, double y, double z);

