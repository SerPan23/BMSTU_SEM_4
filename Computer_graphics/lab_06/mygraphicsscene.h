#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QObject *parent = nullptr);

    QPointF get_mouse_pos();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QPointF mouse_pos;
    bool is_left_hold = false;
    bool shift_pressed;

signals:
    void posChanged();
    void mouseLeftBtnClicked();
    void mouseRightBtnClicked();

    void mouseLeftBtnHold();

    void mouseRightBtnClickedWithShift();
};

#endif // MYGRAPHICSSCENE_H
