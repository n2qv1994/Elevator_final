#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <list>
#include "elevator.h"
#include "simulator.h"

enum StatePassenger {INIT = 0, GO, WAIT, DONE, SERVICE};

class Elevator;

class Passenger
{
private:
    int depart_floor;
    int dest_floor;
    int weight;
    int id;
    int time_request;
    static std::list<Passenger*> *listPassenger;
    Elevator *elevator;
    StatePassenger state;
public:
    Passenger(int depart_floor, int dest_floor, int weight);
    Passenger(int time_request, int depart_floor, int dest_floor, int weight);
    ~Passenger();

    int getDepartFloor();
    int getDestFloor();
    int getWeight();
    int getTimeRequest();
    StatePassenger getState();
    void setElevator(Elevator* elevator);
    Elevator *getElevator();
    StatePassenger getStatePassenger();
    void setState(StatePassenger state);
    static std::list<Passenger*> *getList();
    bool goingUp();
};

#endif // PASSENGER_H
