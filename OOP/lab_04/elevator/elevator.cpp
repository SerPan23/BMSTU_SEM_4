#include "elevator.h"

Elevator::Elevator()
{
    QObject::connect(&cabin.floorTimerPass, SIGNAL(timeout()), &controller, SLOT(handleMove()));
    QObject::connect(&cabin, SIGNAL(cabinUnlocked()), &controller, SLOT(updateTarget()));
    QObject::connect(&controller, SIGNAL(cabinToGoOn()), &cabin, SLOT(cabinMove()));
    QObject::connect(&controller, SIGNAL(cabinToPrepare()), &cabin, SLOT(cabinPrepare()));
    QObject::connect(&controller, SIGNAL(cabinToStop()), &cabin, SLOT(cabinStop()));
    QObject::connect(&controller, SIGNAL(cabinDoorsToOpen()), &cabin, SIGNAL(doorsToOpen()));
}

void Elevator::btnClick(int btnNumber)
{
    controller.newTarget(btnNumber);
}
