#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>
#include "elevator.h"
#include "passenger.h"
#include "controller.h"
#include "simulator.h"
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;
//    qmlRegisterType<Elevator>("Elevator",1,0,"Elevator");
    qmlRegisterType<Simulator>("Simulator",1,0,"Simulator");
//    qmlRegisterType<Controller>("Controller",1,0,"Controller");
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();
    std::cout << "Hi!, I'm n2qv" << endl;

    Controller *controller = new Controller();
//    // passeger(int depart, int destination, int weight)
//    Passenger *p1 = new Passenger(10, 19, 75);//2
//    Passenger *p2 = new Passenger(9, 4, 82);
//    Passenger *p3 = new Passenger(6, 9, 76);//2
//    Passenger *p4 = new Passenger(3, 18, 100);
//    Passenger *p5 = new Passenger(20, 2, 65);//2
//    Passenger *p6 = new Passenger(17, 3, 120);
    Passenger *p1 = new Passenger(1 ,10, 19, 75);
    Passenger *p2 = new Passenger(5, 9, 4, 82);
    Passenger *p3 = new Passenger(10 ,6, 9, 76);
    Passenger *p4 = new Passenger(15, 2, 18, 100);
    Passenger *p5 = new Passenger(23, 20, 2, 65);
    Passenger *p6 = new Passenger(30, 4, 7, 120);

    return app.exec();
}
