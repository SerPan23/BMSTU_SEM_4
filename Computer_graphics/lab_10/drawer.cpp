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
