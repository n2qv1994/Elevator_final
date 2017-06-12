#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "elevator.h"
#include "simulator.h"
#include "passenger.h"

//class Elevator;

class Controller
{
private:
    static Elevator *elevator1,*elevator2;
    static Controller *_singleton;

public:
    Controller();
    ~Controller();

    static Controller *getInstance();
    void run();
};

#endif // CONTROLLER_H
