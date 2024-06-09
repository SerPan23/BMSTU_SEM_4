#include "mygraphicsscene.h"

#include <QApplication>
#include <Qt>

MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    this->shift_pressed = QApplication::queryKeyboardModifiers() == Qt::ShiftModifier;
    if (mouseEvent->button() == Qt::LeftButton)
    {
        this->is_left_hold = true;
        this->mouse_pos = mouseEvent->scenePos();
        emit posChanged();
        if (shift_pressed)
            emit mouseLeftBtnClickedWithShift();
        else
            emit mouseLeftBtnClicked();
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        this->mouse_pos = mouseEvent->scenePos();
        emit posChanged();
        if (shift_pressed)
            emit mouseRightBtnClickedWithShift();
        else
            emit mouseRightBtnClicked();
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (this->is_left_hold)
    {
        if (this->mouse_pos != mouseEvent->scenePos())
        {
            // std::cout << mouseEvent->scenePos().x() << " " << mouseEvent->scenePos().x() << std::endl;
            this->mouse_pos = mouseEvent->scenePos();
            emit mouseLeftBtnHold();
        }
    }
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        this->is_left_hold = false;
    }
}

QPointF MyGraphicsScene::get_mouse_pos()
{
    return this->mouse_pos;
}
