#include "cabin.h"

#include <QString>

#include <QDebug>


Cabin::Cabin(QObject *parent) : QObject(parent),
    state(Cabin::State::UNLOCKED) {

    floorTimerPass.setSingleShot(true);

    QObject::connect(this, SIGNAL(doorsToOpen()), &this->doors, SLOT(doorsOpening()));
    QObject::connect(&this->doors, SIGNAL(closed()), this, SLOT(cabinUnlock()));
}

void Cabin::cabinMove()
{
    if (this->state != State::PREPARE && this->state != State::MOVE)
        return;

    if (this->state == State::PREPARE)
        this->state = State::MOVE;

    this->floorTimerPass.start(ONE_FLOOR_PASS_TIME);
}

void Cabin::cabinStop()
{
    if (this->state != State::MOVE)
        return;

    this->state = State::STOPPED;
    qDebug() << "Кабина остановилась";

    emit cabinLock();
}

void Cabin::cabinPrepare()
{
    if (this->state != State::UNLOCKED)
        return;

    this->state = State::PREPARE;

    qDebug() << "Кабина готовится двигаться";

    emit cabinMove();
}

void Cabin::cabinLock()
{
    if (this->state != State::STOPPED)
        return;

    this->state = State::LOCKED;
    qDebug() << "Кабина заблокировала движение";

    emit doorsToOpen();
}

void Cabin::cabinUnlock()
{
    if (this->state != State::LOCKED)
        return;

    this->state = State::UNLOCKED;
    qDebug() << "Кабина разблокировала движение";

    emit cabinUnlocked();
}
