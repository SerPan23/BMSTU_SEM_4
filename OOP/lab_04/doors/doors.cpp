#include "doors.h"

#include <QDebug>

Doors::Doors(QObject *parent) : QObject(parent), state(CLOSED) {
    this->passengersWaitingTimer.setInterval(PASSENGERS_WAITING_DELAY);
    this->passengersWaitingTimer.setSingleShot(true);
    this->openTimer.setSingleShot(true);
    this->closeTimer.setSingleShot(true);


    QObject::connect(&this->openTimer, SIGNAL(timeout()), this, SLOT(doorsOpen()));
    QObject::connect(this, SIGNAL(opened()), &this->passengersWaitingTimer, SLOT(start()));
    QObject::connect(&this->passengersWaitingTimer, SIGNAL(timeout()), this, SLOT(doorsClosing()));
    QObject::connect(&this->closeTimer, SIGNAL(timeout()), this, SLOT(doorsClose()));
}

void Doors::doorsOpening() {
    if (this->state != CLOSING && this->state != CLOSED)
        return;

    if (this->state == CLOSED)
    {
        this->state = OPENING;
        this->openTimer.start(DOORS_DEFAULT_DELAY);
    }
    else
    {
        this->state = OPENING;

        qDebug() << "Прерываю закрытие дверей...";

        int remainingTime = this->closeTimer.remainingTime();
        this->closeTimer.stop();
        this->openTimer.start(DOORS_DEFAULT_DELAY - remainingTime);
    }

    qDebug() << "Двери открываются...";
}

void Doors::doorsClosing() {
    if (this->state != OPENED)
        return;

    this->state = CLOSING;

    this->closeTimer.start(DOORS_DEFAULT_DELAY);
    qDebug() << "Двери закрываются...";
}

void Doors::doorsOpen() {
    if (this->state != OPENING)
        return;

    this->state = OPENED;
    qDebug() << "Двери открыты.\nОжидание пассажиров...";

    emit opened();
}

void Doors::doorsClose() {
    if (this->state != CLOSING)
        return;

    this->state = CLOSED;
    qDebug() << "Двери закрыты.";

    emit closed();
}
