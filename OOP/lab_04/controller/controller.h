#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "../constants.h"

class Controller : public QObject {
Q_OBJECT

enum PanelState { FREE, MOVE, REACHED_TARGET, UPDATE_TARGET };

public:
    explicit Controller(QObject *parent = nullptr);

    void newTarget(int floor);

signals:

    void cabinToStop();

    void cabinDoorsToOpen();

    void cabinToPrepare();

    void cabinToGoOn();


public slots:

    void updateTarget();

    void handleMove();

    void handleFree();

    void reachedTargetFloor();

private:
    int currFloor = 1;
    int mainTarget = -1;

    std::vector<bool> needVisit;

    PanelState state;
    Direction direction;

    int findNearestMainTarget();
    Direction findDirection() const;
};

#endif // CONTROLLER_H
