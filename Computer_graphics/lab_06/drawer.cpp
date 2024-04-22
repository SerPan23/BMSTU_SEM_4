#include "drawer.h"

Drawer::Drawer(QGraphicsView *view, QObject *parent)
{
    _scene = new MyGraphicsScene(parent);

    view->setScene(_scene);
    view->setStyleSheet("QGraphicsView {background-color: white}");

    QRect rcontent = view->contentsRect();
    view->scene()->setSceneRect(0, 0, rcontent.width(),
                                            rcontent.height());


    _width = _scene->width();
    _height = _scene->height();

    clear();
}

void Drawer::draw_point(int x, int y, QColor& color)
{
    Point p(x, y);
    draw_point(p, color);
}

void Drawer::draw_point(Point &p, QColor& color)
{
    draw_line(p, p, color);
}

void Drawer::draw_line(Point &start, Point &end, QColor& color)
{
    QPainter painter(&_pxp);
    QPen pen(color);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(start.x(), start.y(), end.x(), end.y());
}

void Drawer::draw_figure(Figure &figure, QColor& color)
{
    for (int i = 1; i < figure.size(); i++)
        draw_line(figure.get_point(i - 1), figure.get_point(i), color);

    if (figure.is_closed())
        draw_line(figure.get_point(figure.size() - 1), figure.get_point(0), color);
}

void Drawer::draw_figures(figures_t &figures, QColor& color)
{
    for (int i = 0; i < figures.size(); i++)
        draw_figure(figures[i], color);
}

void Drawer::draw_circle(Point &center, int radius, QColor &color)
{
    Point r(radius, radius);
    draw_ellipse(center, r, color);
}

void Drawer::draw_ellipse(Point &center, Point &radius, QColor &color)
{
    QPainter painter(&_pxp);
    QPen pen(color);
    painter.setPen(pen);

    painter.drawEllipse(center.x() - radius.x(), center.y() - radius.y(),
                        radius.x() * 2, radius.y() * 2);
}

void Drawer::draw_ellipses(ellipses_t &ellipses, QColor &color)
{
    for (int i = 0; i < ellipses.size(); i++)
        draw_ellipse(ellipses[i].center, ellipses[i].radius, color);
}


QColor Drawer::get_pixel_color(const Point &position) const
{
    return QColor(_pxp.toImage().pixelColor(position.x(), position.y()).rgb());
}

QColor Drawer::get_pixel_color(int x, int y) const
{
    return get_pixel_color(Point(x, y));
}

void Drawer::clear()
{
    this->_pxp = QPixmap(_scene->width(), _scene->height());
    // this->_pxp.fill(Qt::transparent);
    this->_pxp.fill(Qt::white);

    _scene->clear();
}

void Drawer::render()
{
    _scene->clear();
    _scene->addPixmap(this->_pxp);
}

MyGraphicsScene *Drawer::scene()
{
    return _scene;
}

int Drawer::width()
{
    return _width;
}

int Drawer::height()
{
    return _height;
}
