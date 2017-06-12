#include "controller.h"
#include <iostream>
#include <stdlib.h>

Controller::Controller()
{

}

Controller::~Controller()
{

}

Controller *Controller::getInstance()
{
    if(_singleton == NULL){
        _singleton = new Controller;
        elevator1 = new Elevator("Elevator1");
        elevator2 = new Elevator("Elevator2");
    }
    return _singleton;
}

void Controller::run()
{
    for(std::list<Passenger*>::iterator it = Passenger::getList()->begin();it != Passenger::getList()->end(); it++) {
        StatePassenger state = (*it)->getState();
        switch(state)
                {
                    case SERVICE: {
                        StateElevator stateE1 = elevator1->getState();
                        StateElevator stateE2 = elevator2->getState();
                        int currentFloorE1 = elevator1->getCurrentFloor();
                        int currentFloorE2 = elevator2->getCurrentFloor();
                        int distanceE1 = std::abs(currentFloorE1 -(*it)->getDepartFloor());
                        int distanceE2 = std::abs(currentFloorE2 -(*it)->getDepartFloor());
                        if((stateE1 == STOP) && (stateE2 == STOP))
                        {
                            if( distanceE1 <= distanceE2){
                                elevator1->addPassenger(*it);
                                (*it)->setElevator(elevator1);
                                (*it)->setState(WAIT);
                            }
                            else {
                                elevator2->addPassenger(*it);
                                (*it)->setElevator(elevator2);
                                (*it)->setState(WAIT);
                            }
                        }
                        else if((stateE1 == GOING_UP || stateE1 == STOP_UP) && (stateE2 == GOING_UP || stateE2 == STOP_UP) && (!(*it)->goingUp()))
                        {
                             if((currentFloorE1 <= (*it)->getDepartFloor()) && (currentFloorE2 <= (*it)->getDepartFloor())) {
                                if(distanceE1 <= distanceE2) {
                                    elevator1->addPassenger(*it);
                                    (*it)->setElevator(elevator1);
                                    (*it)->setState(WAIT);
                                }
                                else {
                                    elevator2->addPassenger(*it);
                                    (*it)->setElevator(elevator2);
                                    (*it)->setState(WAIT);
                                }
                             }
                             else if(currentFloorE1 <= (*it)->getDepartFloor()) {
                                 elevator1->addPassenger(*it);
                                 (*it)->setElevator(elevator1);
                                 (*it)->setState(WAIT);
                             }
                             else if(currentFloorE2 <= (*it)->getDepartFloor()) {
                                 elevator2->addPassenger(*it);
                                 (*it)->setElevator(elevator1);
                                 (*it)->setState(WAIT);
                             }
                        }
                        else if((stateE1 == GOING_DOWN || stateE1 == STOP_DOWN) && (stateE2 == GOING_DOWN || stateE2 == STOP_DOWN) && ((*it)->goingUp()))
                        {
                             if((currentFloorE1 >= (*it)->getDepartFloor()) && (currentFloorE2 >= (*it)->getDepartFloor())) {
                                if(distanceE1 <= distanceE2) {
                                    elevator1->addPassenger(*it);
                                    (*it)->setElevator(elevator1);
                                    (*it)->setState(WAIT);
                                }
                                else {
                                    elevator2->addPassenger(*it);
                                    (*it)->setElevator(elevator2);
                                    (*it)->setState(WAIT);
                                }
                             }
                             else if(currentFloorE1 >= (*it)->getDepartFloor()) {
                                 elevator1->addPassenger(*it);
                                 (*it)->setElevator(elevator1);
                                 (*it)->setState(WAIT);
                             }
                             else if(currentFloorE2 >= (*it)->getDepartFloor()) {
                                 elevator2->addPassenger(*it);
                                 (*it)->setElevator(elevator1);
                                 (*it)->setState(WAIT);
                             }
                        }
                        else if((*it)->goingUp()) {
                            if((stateE1 == GOING_DOWN || stateE1 == STOP_DOWN)) {
                                if (currentFloorE1 >= (*it)->getDepartFloor()) {
                                    elevator1->addPassenger(*it);
                                    (*it)->setElevator(elevator1);
                                    (*it)->setState(WAIT);
                                }
                                else if ((currentFloorE1 <= (*it)->getDepartFloor()) && stateE2 == STOP) {
                                    elevator2->addPassenger(*it);
                                    (*it)->setElevator(elevator2);
                                    (*it)->setState(WAIT);
                                }
                            }
                            else if((stateE2 == GOING_DOWN || stateE2 == STOP_DOWN)) {
                                if (currentFloorE2 >= (*it)->getDepartFloor()) {
                                    elevator2->addPassenger(*it);
                                    (*it)->setElevator(elevator2);
                                    (*it)->setState(WAIT);
                                }
                                else if (currentFloorE2 <= (*it)->getDepartFloor() && stateE1 == STOP) {
                                    elevator1->addPassenger(*it);
                                    (*it)->setElevator(elevator1);
                                    (*it)->setState(WAIT);
                                }
                            }
                        }
                        else if(!(*it)->goingUp()) {
                            if((stateE1 == GOING_UP || stateE1 == STOP_UP)) {
                                if(currentFloorE1 <= (*it)->getDepartFloor()) {
                                    elevator1->addPassenger(*it);
                                    (*it)->setElevator(elevator1);
                                    (*it)->setState(WAIT);
                                }
                                else if ((currentFloorE1 >= (*it)->getDepartFloor()) && stateE2 == STOP) {
                                    elevator2->addPassenger(*it);
                                    (*it)->setElevator(elevator2);
                                    (*it)->setState(WAIT);
                                }
                            }
                            else if((stateE2 == GOING_UP || stateE2 == GOING_UP)) {
                                if(currentFloorE2 <= (*it)->getDepartFloor()) {
                                    elevator2->addPassenger(*it);
                                    (*it)->setElevator(elevator2);
                                    (*it)->setState(WAIT);
                                }
                                else if((currentFloorE2 >= (*it)->getDepartFloor()) && stateE1 == STOP) {
                                    elevator1->addPassenger(*it);
                                    (*it)->setElevator(elevator1);
                                    (*it)->setState(WAIT);
                                }

                            }
                        }
                        break;
                    }
                    case INIT:
                        break;
                    case GO:
                        break;
                    case DONE:
                        break;
                    case WAIT:
                        break;
                }
    }
//    for(std::list<Passenger*>::iterator it = Passenger::getList()->begin();it != Passenger::getList()->end(); it++) {
//        StatePassenger state = (*it)->getState();
//        switch(state)
//        {
//            case INIT:
//                if((*it)->getDepartFloor() % 2 == 0)
//                {
//                    elevator2->addPassenger(*it);
//                    (*it)->setElevator(elevator2);
//                    (*it)->setState(WAIT);
//                }
//                else
//                {
//                    elevator1->addPassenger(*it);
//                    (*it)->setElevator(elevator1);
//                    (*it)->setState(WAIT);
//                }
//                break;
//            case GO:
//                break;
//            case DONE:
//                break;
//            case WAIT:
//                break;
//        }
//    }
}

Controller *Controller::_singleton = NULL;
Elevator *Controller::elevator1 = NULL;
Elevator *Controller::elevator2 = NULL;
