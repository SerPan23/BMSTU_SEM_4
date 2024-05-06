#include "drawer.h"

Drawer::Drawer(QGraphicsView *view, QObject *parent)
{
    view->setFrameShape(QFrame::NoFrame);

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
    QPainter painter(&_pxp);
    QPen pen(color);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(p.x(), p.y(), p.x(), p.y());
}

void Drawer::draw_line(Point &start, Point &end, QColor& color)
{
    QPainter painter(&_pxp);
    QPen pen(color);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(start.x(), start.y(), end.x(), end.y());
}
void Drawer::draw_lines(lines_t &lines, QColor& color)
{
    for (int i = 0; i < lines.size(); i++)
        draw_line(lines[i].start, lines[i].end, color);
}
void Drawer::draw_rect(rect_t &rect, QColor& color)
{
    Point right_top(rect.p2.x(), rect.p1.y());
    Point left_down(rect.p1.x(), rect.p2.y());

    draw_line(rect.p1, right_top, color);
    draw_line(right_top, rect.p2, color);
    draw_line(rect.p2, left_down, color);
    draw_line(left_down, rect.p1, color);
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
