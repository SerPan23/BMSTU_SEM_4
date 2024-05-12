#ifndef QTDRAWER_H
#define QTDRAWER_H

#include <memory>
#include <QGraphicsScene>

#include "BaseDrawer.h"

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;
    explicit QtDrawer(std::weak_ptr<QGraphicsScene> &scene_) : scene(scene_) {};

    void clear() override;
    void drawLine(int x1, int y1, int x2, int y2) override;

private:
    std::weak_ptr<QGraphicsScene> scene;
};

#endif // QTDRAWER_H
