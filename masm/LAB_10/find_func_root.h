#ifndef FIND_FUNC_ROOT
#define FIND_FUNC_ROOT

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-6

double func(double x);
double mid_point(double a, double b);
int sign(double x);
double find_func_root(double start, double end, int step_count);
// void str_func_root(double start, double end, int step_count, char *dst);
void str_func_root(char *start, char *end, char *step_count);

// char* num_to_str(double *num);
// double str_to_double(const char *str);

#endif