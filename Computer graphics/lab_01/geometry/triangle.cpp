#include "triangle.h"

void triangle_free(triangle_t *triangle)
{
    free(triangle->a);
    free(triangle->b);
    free(triangle->c);
}

double segment_len(point_t *pa, point_t *pb)
{
    return sqrt((pb->x - pa->x) * (pb->x - pa->x) + (pb->y - pa->y) * (pb->y - pa->y));
}

bool is_triangle(point_t *pa, point_t *pb, point_t *pc)
{
    double ab = segment_len(pa, pb);
    double ac = segment_len(pa, pc);
    double bc = segment_len(pb, pc);

    if (abs(ab + ac - bc) < EPS or abs(ac + bc - ab) < EPS or abs(ab + bc - ac) < EPS)
        return false;
    return true;
}

// ratio = longer_side / second_side
double bisector_ratio(double side_a, double side_b)
{
    if (abs(side_a) < EPS || abs(side_b) < EPS)
        return 0.0;

    double ratio = 0.0;

    if (side_a >= side_b)
        ratio = side_a / side_b;
    else
        ratio = side_b / side_a;

    return ratio;
}

point_t *find_point_by_bisector_ratio(point_t *pa, point_t *pb, double ratio)
{
    point_t *tmp = point_create((pa->x + ratio * pb->x) / (1 + ratio),
                               (pa->y + ratio * pb->y) / (1 + ratio));

    return tmp;
}

// pa this point is start of bisector
point_t *find_bisector_on_front_side(point_t *pa, point_t *pb, point_t *pc)
{
    point_t *tmp;

    double ab = segment_len(pa, pb);
    double ac = segment_len(pa, pc);

    double ratio = bisector_ratio(ab, ac);

    if (ab < ac)
        tmp = find_point_by_bisector_ratio(pc, pb, ratio);
    else
        tmp = find_point_by_bisector_ratio(pb, pc, ratio);

    return tmp;
}


point_t *find_line_cross(point_t *pa1, point_t *pb1, point_t *pa2, point_t *pb2)
{
    double x, y;

    double k1 = (pb1->y - pa1->y) / (pb1->x - pa1->x);
    double k2 = (pb2->y - pa2->y) / (pb2->x - pa2->x);

    if (pa1->x == pb1->x)
    {
        x = pa1->x;
        y = k2 * x + pa2->y - k2 * pa2->x;
    }
    else if (pa2->x == pb2->x)
    {
        x = pa2->x;
        y = k1 * x + pa1->y - k1 * pa1->x;
    }
    else
    {
        // first line

        double b1 = pa1->y - pa1->x * k1;

        // second line

        double b2 = pa2->y - pa2->x * k2;


        x = (b2 - b1) / (k1 - k2);
        y = k1 * x + b1;
    }

    return point_create(x, y);
}


double find_inscribed_circle_radius(point_t *pa, point_t *pb, point_t *pc)
{
    double ab = segment_len(pa, pb);
    double ac = segment_len(pa, pc);
    double bc = segment_len(pb, pc);

    double p = (ab + ac + bc) / 2;

    double s = sqrt(p * (p - ab) * (p - ac) * (p - bc));

    return s / p;
}

double circle_sqr(double r)
{
    return M_PI * r * r;
}

double triangle_sqr(point_t *pa, point_t *pb, point_t *pc)
{
    double ab = segment_len(pa, pb);
    double ac = segment_len(pa, pc);
    double bc = segment_len(pb, pc);

    double p = (ab + ac + bc) / 2;

    double s = sqrt(p * (p - ab) * (p - ac) * (p - bc));

    return s;
}
