#include "elevator.h"
#include <iostream>

Elevator::Elevator(std::string elevator_name)
{
    this->elevator_name = elevator_name;
    Simulator::getInstance()->addElevator(this);
    reset();
}

Elevator::~Elevator()
{

}

void Elevator::reset()
{
   state = STOP;
   current_floor = 1;
   total_weight = 0;
}

int Elevator::getWeight()
{
    return total_weight;
}

Passenger *Elevator::firstRequest()
{
    Passenger *p;
    std::list<Passenger*>::iterator it = listPassengers.begin();
    p = (*it);
    return p;
}

int Elevator::getCurrentFloor()
{
    return current_floor;
}

void Elevator::addPassenger(Passenger *passenger)
{
    listPassengers.insert(listPassengers.begin(),passenger);
//    total_weight = total_weight + passenger->getWeight();
}

void Elevator::removePassenger(Passenger *passenger)
{
    for(std::list<Passenger*>::iterator it = listPassengers.begin();it != listPassengers.end() ; it++)
    {
        if((*it) == passenger)
        {
//            qDebug()<<"remove passenger floor " << passenger->getDepartFloor();
            listPassengers.erase(it);
            total_weight = total_weight - passenger->getWeight();
//            qDebug()<<"weight passenger "<< passenger->getWeight();
             return;
        }
    }
}

void Elevator::increaseWeight(Passenger *passenger)
{
//    qDebug()<<"++++++++++++++++++++++++++++ ";
    total_weight = total_weight + passenger->getWeight();
//    qDebug()<<"increase weight "<< total_weight;
}

void Elevator::decreaseWeight(Passenger *passenger)
{
//    qDebug()<<"--------------------------"<< total_weight;
    total_weight = total_weight - passenger->getWeight();
//    qDebug()<<"decrease weight "<< total_weight;
}

void Elevator::run()
{
    StateElevator nextState = state;
    switch(state)
        {
        case STOP:
            if(listPassengers.size() != 0)
            {
                int depart_floor = firstRequest()->getDepartFloor();
                if(depart_floor < current_floor)
                {
                    nextState = GOING_DOWN;
                }
                else if(depart_floor > current_floor)
                {
                    nextState = GOING_UP;
                }
                else {
                    if(firstRequest()->goingUp()){
                        for(std::list<Passenger*>::iterator it = listPassengers.begin(); it != listPassengers.end(); it ++) {
                            if(((*it)->getDepartFloor()==current_floor) && ((*it)->getState() == WAIT)) {
                                (*it)->setState(GO);
                                this->increaseWeight(*it);
                            }
                        }
                        nextState = STOP_DOWN;
                        _waitedTime = 3;
                    }
                    else {
                        for(std::list<Passenger*>::iterator it = listPassengers.begin(); it != listPassengers.end(); it ++) {
                            if(((*it)->getDepartFloor()==current_floor) && ((*it)->getState() == WAIT)) {
                                (*it)->setState(GO);
                                this->increaseWeight(*it);
                            }
                        }
                        nextState = STOP_UP;
                        _waitedTime = 3;
                    }
                }
            }
            break;
        case GOING_UP:
            current_floor++;
            for(std::list<Passenger*>::iterator it = listPassengers.begin(); it != listPassengers.end(); it ++) {
                if(((*it)->getDestFloor()==current_floor) && ((*it)->getState() == GO)) {
                    _waitedTime = 3;
                    nextState = STOP_UP;
                    (*it)->setState(DONE);
                    this->removePassenger(*it);
                    it = listPassengers.begin();
//                    this->decreaseWeight(*it);
                }
                else if(((*it)->getDepartFloor()==current_floor) && ((*it)->getState() == WAIT)) {
                    _waitedTime = 3;
                    nextState = STOP_UP;
                    (*it)->setState(GO);
                    this->increaseWeight(*it);
                }
                else if(((*it)->getDepartFloor()==current_floor) && ((*it)->getState() == WAIT) && current_floor == 20) {
                    _waitedTime = 3;
                    nextState = STOP_DOWN;
                    (*it)->setState(GO);
                    this->increaseWeight(*it);
                }
                if(current_floor == 20) {
                    _waitedTime = 3;
                    nextState = STOP_DOWN;
                }
            }
            break;
        case GOING_DOWN:
            current_floor--;
            for(std::list<Passenger*>::iterator it = listPassengers.begin(); it != listPassengers.end(); it ++) {
                if(((*it)->getDestFloor()==current_floor) && ((*it)->getState() == GO)) {
                    _waitedTime = 3;
                    nextState = STOP_DOWN;
                    (*it)->setState(DONE);
                      this->removePassenger(*(it++));
                      it = listPassengers.begin();
//                    this->decreaseWeight(*it);
                }
                else if(((*it)->getDepartFloor()==current_floor) && ((*it)->getState() == WAIT)) {
                    _waitedTime = 3;
                    nextState = STOP_DOWN;
                    (*it)->setState(GO);
                    increaseWeight(*it);
                }
                else if(((*it)->getDepartFloor()==current_floor) && ((*it)->getState() == WAIT) && current_floor == 1) {
                    _waitedTime = 3;
                    nextState = STOP_UP;
                    (*it)->setState(GO);
                    this->increaseWeight(*it);
                }
                if(current_floor == 1) {
                    _waitedTime = 3;
                    nextState = STOP_UP;
                }
            }
            break;
        case STOP_UP:
            if(_waitedTime != 0) {
                   _waitedTime --;
            }
            else if(listPassengers.size() == 0)
                 nextState = STOP;
            else
                 nextState = GOING_UP;
           break;
        case STOP_DOWN:
            if(_waitedTime != 0) {
                   _waitedTime --;
            }
            else if(listPassengers.size() == 0)
                 nextState = STOP;
            else
                 nextState = GOING_DOWN;
            break;
    }
    state = nextState;
}

std::string Elevator::getName()
{
    return this->elevator_name;
}

void Elevator::setState(StateElevator state)
{
    this->state = state;
}

StateElevator Elevator::getState()
{
    return state;
}
