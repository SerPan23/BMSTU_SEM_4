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

private:
    QPointF mouse_pos;

signals:
    void posChanged();
};

#endif // MYGRAPHICSSCENE_H
