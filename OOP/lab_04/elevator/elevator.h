#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>

#include "controller.h"
#include "cabin.h"

class Elevator : public QObject
{
Q_OBJECT
public:
    Elevator();

    void btnClick(int btnNumber);

private:
    Controller controller;
    Cabin cabin;
};

#endif // ELEVATOR_H
