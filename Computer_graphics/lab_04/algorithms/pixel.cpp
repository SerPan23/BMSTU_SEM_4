#include "pixel.h"

pixel_t pixel_create(int x, int y)
{
    return pixel_t{x, y, 255};
}

pixel_t pixel_create(int x, int y, double intensity)
{
    return pixel_t{x, y, intensity};
}

pixel_t pixel_create(point_t point)
{
    return pixel_t{(int)point.x, (int)point.y, 255};
}
