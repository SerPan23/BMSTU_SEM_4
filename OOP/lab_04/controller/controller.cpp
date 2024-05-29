#include "controller.h"

#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent),
    currFloor(START_FLOOR), mainTarget(NO_TARGET),
    needVisit(FLOORS_COUNT, false), state(FREE),
    direction(STAY)
{

}

int Controller::findNearestMainTarget() {
    bool isUpdated = false;
    int minDistance = FLOORS_COUNT + 1;
    int potentialNextFloor = -1;

    for (int i = 0; i < this->needVisit.size(); ++i)
    {
        if (needVisit[i])
        {
            int distance = abs(i - currFloor);
            if (distance < minDistance)
            {
                isUpdated = true;
                minDistance = distance;
                potentialNextFloor = i + 1;
            }
        }
    }

    if (isUpdated)
        return potentialNextFloor;
    return -1;
}

void Controller::newTarget(const int floor)
{
    if (this->needVisit[floor - 1])
        return;

    this->needVisit[floor - 1] = true;

    if (state == REACHED_TARGET and floor == this->currFloor)
    {
        this->needVisit[floor - 1] = false;
        emit cabinDoorsToOpen();
    }
    else if (state == FREE)
        emit updateTarget();
}

void Controller::handleMove()
{
    if (state != UPDATE_TARGET and state != MOVE)
        return;

    state = MOVE;

    this->currFloor += this->direction;
    qDebug() << "Этаж №" << this->currFloor << "| Лифт приехал";

    if (this->currFloor != this->mainTarget)
    {
        if (needVisit[this->currFloor - 1])
            emit intermediateTarget();
        else
            emit cabinToGoOn();
    }
    else
        emit reachedTargetFloor();
}

void Controller::handleFree()
{
    if (state != UPDATE_TARGET)
        return;

    this->state = FREE;

    qDebug() << "Этаж №" << this->currFloor << "| Контроллер cвободен";
}

void Controller::reachedTargetFloor()
{
    if (state != MOVE)
        return;

    this->state = REACHED_TARGET;

    needVisit[currFloor - 1] = false;

    qDebug() << "Этаж №" << this->currFloor << "| Контроллер понял, что на нужном этаже";

    emit cabinToStop();
}

void Controller::intermediateTarget()
{
    if (state != MOVE)
        return;

    this->state = INTERMEDIATE_TARGET;

    needVisit[currFloor - 1] = false;

    isIntermediateStop = true;

    qDebug() << "Этаж №" << this->currFloor << "| Контроллер заехал на этаже по дороге";

    emit cabinToStop();
}

void Controller::updateTarget()
{
    if (state != FREE and state != REACHED_TARGET and state != INTERMEDIATE_TARGET)
        return;

    PanelState prevState = state;

    state = UPDATE_TARGET;

    int nextFloor = -1;

    if (prevState == INTERMEDIATE_TARGET)
    {
        nextFloor = mainTarget;
    }
    else
    {
        qDebug() << "Этаж №" << this->currFloor << "| Контроллер ищет куда ехать дальше";
        nextFloor = findNearestMainTarget();
    }

    if (nextFloor != -1)
    {
        if (prevState == INTERMEDIATE_TARGET)
        {
            qDebug() << "Контроллер продолжает движение на этаж №" << mainTarget;
            emit cabinToPrepare();
        }
        else
        {
            mainTarget = nextFloor;
            direction = findDirection();

            qDebug() << "Этаж №" << this->currFloor << "| Контроллер выбрал целью этаж №" << mainTarget;
            emit cabinToPrepare();
        }
    }
    else
        emit handleFree();
}

Direction Controller::findDirection() const
{
    if (mainTarget == currFloor)
        return STAY;
    else if (mainTarget < currFloor)
        return DOWN;

    return UP;
}
