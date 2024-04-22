#include "algorithm.h"

#include <iostream>

static void wait(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void fill_with_seed(Drawer *drawer, Point &seed, QColor &fill_color, QColor &border_color, int delay)
{
    std::stack <Point> stack;

    stack.push(Point(seed));

    Point point;
    int x, y;

    while (!stack.empty())
    {
        point = stack.top();
        stack.pop();

        x = point.x();
        y = point.y();

        if (y < 0 || drawer->height() < y)
            continue;

        int wx = x;  // запоминаем абсциссу

        // заполнение справа
        while (drawer->get_pixel_color(x, y) != border_color && x <= drawer->width())
        {
            drawer->draw_point(x, y, fill_color);
            x++;
        }

        int xr = x - 1; // запоминаем пиксель справа

        x = wx;


        // заполнение слева
        while (drawer->get_pixel_color(x, y) != border_color and x >= 0)
        {
            drawer->draw_point(x, y, fill_color);
            x--;
        }

        int xl = x + 1; //запоминаем пиксель слева

        x = xl;
        y = y + 1;

        // Ищем затравочные пиксели на строке выше
        while (x <= xr)
        {
            int f = 0;

            while (drawer->get_pixel_color(x, y) != border_color &&
                drawer->get_pixel_color(x, y) != fill_color && x < xr)
            {
                if (f == 0)
                    f = 1;
                x++;
            }

            // Помещаем в стек крайний справа пиксель
            if (f == 1)
            {
               if (x == xr && drawer->get_pixel_color(x, y) != fill_color &&
                   drawer->get_pixel_color(x, y) != border_color)
                    stack.push(Point(x, y));
                else
                   stack.push(Point(x - 1, y));
                f = 0;
            }

            // Исследуем прерывание интервала
            wx = x;
            while ((drawer->get_pixel_color(x, y) == border_color ||
                    drawer->get_pixel_color(x, y) == fill_color) && x < xr)
                x++;

            if (x == wx)
                x++;
        }

        x = xl;
        y = y - 2;

        // Ищем затравочные пиксели на строке ниже
        while (x <= xr)
        {
            int f = 0;

            while (drawer->get_pixel_color(x, y) != border_color &&
                   drawer->get_pixel_color(x, y) != fill_color && x < xr)
            {
                if (f == 0)
                    f = 1;
                x++;
            }


            if (f == 1)
            {
                if (x == xr && drawer->get_pixel_color(x, y) != fill_color &&
                    drawer->get_pixel_color(x, y) != border_color)
                    stack.push(Point(x, y));
                else
                    stack.push(Point(x - 1, y));
                f = 0;
            }

            // Исследуем прерывание интервала
            wx = x;
            while ((drawer->get_pixel_color(x, y) == border_color ||
                    drawer->get_pixel_color(x, y) == fill_color) && x < xr)
                x++;

            if (x == wx)
                x++;
        }

        if (delay)
        {
            drawer->render();
            wait(delay);
        }
    }

    drawer->render();
}
