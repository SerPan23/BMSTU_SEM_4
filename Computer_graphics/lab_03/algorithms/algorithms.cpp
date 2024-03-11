#include "algorithms.h"

pixel_t pixel_create(int x, int y)
{
    return pixel_create(x, y, 255);
}

pixel_t pixel_create(int x, int y, double intensity)
{
    return pixel_t{x, y, intensity};
}

int count_steps(line_t line)
{
    int count = 0;

    int x = line.pixels[0].x;
    int y = line.pixels[0].y;

    for (int i = 0; i < line.pixels.size(); i++)
    {
        if (x != line.pixels[i].x and y != line.pixels[i].y)
            count += 1;
        x = line.pixels[i].x;
        y = line.pixels[i].y;
    }

    return count;
}
