#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        this->mouse_pos = mouseEvent->scenePos();
        emit posChanged();
        emit mouseLeftBtnClicked();
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        // this->mouse_pos = mouseEvent->scenePos();
        // emit posChanged();
        emit mouseRightBtnClicked();
    }
}

QPointF MyGraphicsScene::get_mouse_pos()
{
    return this->mouse_pos;
}
