#ifndef QTFACTORY_H
#define QTFACTORY_H

#include <QGraphicsScene>
#include <memory>

#include "AbstractFactory.h"


class QtFactory : public AbstractFactory
{
public:
    explicit QtFactory(std::shared_ptr<QGraphicsScene> scene);
    std::unique_ptr<BaseDrawer> create() override;

private:
    std::weak_ptr<QGraphicsScene> scene{};
};

#endif // QTFACTORY_H
