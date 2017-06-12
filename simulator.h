#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <QQuickItem>
#include <QObject>

#include <iostream>
#include <list>
#include "passenger.h"
#include "elevator.h"

class Passenger;

class Elevator;

class Simulator : public QObject
{
   Q_OBJECT

private:
    static Simulator* _singleton; // unique instance
    std::list<Passenger*> listPassenger;
    std::list<Elevator*> listElevator;
    int real_time = 0;
public:
    explicit Simulator(QObject* parent = 0);
    virtual ~Simulator();

    Q_INVOKABLE static Simulator* getInstance();
    Q_INVOKABLE void addPassenger(Passenger *passenger);
    Q_INVOKABLE void addElevator(Elevator *elevator);
    Q_INVOKABLE void next();
    Q_INVOKABLE int getRealTime();
//    Q_INVOKABLE std::list<Elevator*> getElevators();
    Q_INVOKABLE int getFloorElevator1();
    Q_INVOKABLE int getFloorElevator2();
    Q_INVOKABLE int getWeight1();
    Q_INVOKABLE int getWeight2();

};

#endif // SIMULATOR_H
