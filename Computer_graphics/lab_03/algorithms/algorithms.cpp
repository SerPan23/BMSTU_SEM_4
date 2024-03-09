#include "algorithms.h"

pixel_t pixel_create(int x, int y)
{
    return pixel_create(x, y, 255);
}

pixel_t pixel_create(int x, int y, double intensity)
{
    return pixel_t{x, y, intensity};
}
