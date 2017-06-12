#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <list>

#include "passenger.h"
#include "simulator.h"

enum StateElevator {STOP = 0, GOING_UP, GOING_DOWN, STOP_UP, STOP_DOWN};

class Passenger;

class Elevator
{
private:
    int current_floor;
    int total_weight;
    int _waitedTime;
    StateElevator state;
    std::string elevator_name;
    std::list<Passenger*> listPassengers;
public:
    Elevator(std::string name);
    ~Elevator();

    int getCurrentFloor();
    int getWeight();
    void addPassenger(Passenger *passenger);
    void removePassenger(Passenger *passenger);
    void increaseWeight(Passenger *passenger);
    void decreaseWeight(Passenger *passenger);
    std::string getName();
    void run();
    void setState(StateElevator state);
    StateElevator getState();
    void reset();
    Passenger *firstRequest();

};

#endif // ELEVATOR_H
