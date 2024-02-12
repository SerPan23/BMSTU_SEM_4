#ifndef TRIANGLE_H
#define TRIANGLE_H

#define EPS 1e-8

#include <cmath>

#include "point.h"

struct triangle
{
    point_t *a;
    point_t *b;
    point_t *c;
};

using triangle_t = struct triangle;

void triangle_free(triangle_t *triangle);

double segment_len(point_t *pa, point_t *pb);

bool is_triangle(point_t *pa, point_t *pb, point_t *pc);

// ratio = longer_side / second_side
double bisector_ratio(double side_a, double side_b);

point_t *find_point_bisector_ratio(point_t *pa, point_t *pb, double ratio);

// pa this point is start of bisector
point_t *find_bisector_on_front_side(point_t *pa, point_t *pb, point_t *pc);

point_t *find_line_cross(point_t *pa1, point_t *pb1, point_t *pa2, point_t *pb2);

double find_inscribed_circle_radius(point_t *pa, point_t *pb, point_t *pc);

double circle_sqr(double r);
double triangle_sqr(point_t *pa, point_t *pb, point_t *pc);


#endif // TRIANGLE_H
