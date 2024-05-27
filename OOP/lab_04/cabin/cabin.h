#ifndef CABIN_H
#define CABIN_H

#include <QObject>

#include "../constants.h"

#include "controller.h"
#include "doors.h"

class Cabin : public QObject
{
Q_OBJECT

public:
    explicit Cabin(QObject *parent = nullptr);
    enum class State { MOVE, STOPPED, LOCKED, UNLOCKED, PREPARE };

signals:

    void cabinUnlocked();

    void doorsToOpen();

    void cabinFloorPassed();

public slots:

    void cabinLock();

    void cabinUnlock();

    void cabinPrepare();

    void cabinMove();

    void cabinStop();

    void floorTimerPassed();


private:
    QTimer floorTimerPass;
    Cabin::State state;
    Doors doors;
};

#endif // CABIN_H
