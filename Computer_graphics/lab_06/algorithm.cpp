#include "algorithm.h"

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

        drawer->draw_point(x, y, fill_color);

        int wx = x;  // запоминаем абсциссу

        x += 1;
        // заполнение справа
        while (x < drawer->width() && drawer->get_pixel_color(x, y) != border_color)
        {
            drawer->draw_point(x, y, fill_color);
            x += 1;
        }

        int xr = x - 1; // запоминаем пиксель справа

        x = wx;

        x -= 1;
        // заполнение слева
        while (x >= 0 && drawer->get_pixel_color(x, y) != border_color)
        {
            drawer->draw_point(x, y, fill_color);
            x -= 1;
        }

        int xl = x + 1; //запоминаем пиксель слева

        x = xl;
        y = y + 1;

        // Ищем затравочные пиксели на строке выше
        if (y < drawer->height())
        {
            while (x <= xr)
            {
                bool f = false;

                while (x <= xr && drawer->get_pixel_color(x, y) != border_color &&
                       drawer->get_pixel_color(x, y) != fill_color)
                {
                    f = true;
                    x += 1;
                }

                // Помещаем в стек крайний справа пиксель
                if (f)
                {
                    if (x == xr && drawer->get_pixel_color(x, y) != fill_color &&
                        drawer->get_pixel_color(x, y) != border_color)
                        stack.push(Point(x, y));
                    else
                        stack.push(Point(x - 1, y));
                    f = false;
                }

                // Исследуем прерывание интервала
                wx = x;
                while (x < xr && (drawer->get_pixel_color(x, y) == border_color ||
                                  drawer->get_pixel_color(x, y) == fill_color))
                    x += 1;

                if (x == wx)
                    x += 1;
            }
        }

        x = xl;
        y = y - 2;

        // Ищем затравочные пиксели на строке ниже
        if (y >= 0)
        {
            while (x <= xr)
            {
                bool f = false;

                while (x <= xr && drawer->get_pixel_color(x, y) != border_color &&
                       drawer->get_pixel_color(x, y) != fill_color)
                {
                    f = true;
                    x += 1;
                }


                if (f)
                {
                    if (x == xr && drawer->get_pixel_color(x, y) != fill_color &&
                        drawer->get_pixel_color(x, y) != border_color)
                        stack.push(Point(x, y));
                    else
                        stack.push(Point(x - 1, y));
                    f = false;
                }

                // Исследуем прерывание интервала
                wx = x;
                while (x < xr && (drawer->get_pixel_color(x, y) == border_color ||
                                  drawer->get_pixel_color(x, y) == fill_color))
                    x += 1;

                if (x == wx)
                    x += 1;
            }
        }

        if (delay)
        {
            drawer->render();
            wait(delay);
        }
    }

    drawer->render();
}
