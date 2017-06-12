import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
//import Elevator 1.0
//import Controller 1.0
import Simulator 1.0

Rectangle {
    visible: true
    width: 400
    height: 640
    color: "#ffffff"
//    title: qsTr("Hello Worlds")
    Simulator{
        id: simulator
    }

    Timer {
        id: timer1
        interval: 1000
        repeat: true
        running: false

        onTriggered: {
            simulator.getInstance().next();
            var floorE1 = simulator.getInstance().getFloorElevator1();
            var floorE2 = simulator.getInstance().getFloorElevator2();

            elevator1_img.y = 600 - 30*floorE1;
            elevator2_img.y = 600 - 30*floorE2;

            total_weight1.text = simulator.getInstance().getWeight1().toString();
            total_weight2.text = simulator.getInstance().getWeight2().toString();

        }
    }
    Text {
        id: e1
        text: qsTr("Elevator 1");
        y:620
    }

    Text {
        id: e2
        text: qsTr("Elevator 2");
        y:620
        x:260
    }

    Text {
        id: weight_e1
        text: qsTr("Weight e1");
        y:300
        x:70
    }

    Text {
        id: total_weight1
        text: qsTr("");
        y:320
        x:70
    }

    Text {
        id: weight_e2
        text: qsTr("Weight e2");
        y:300
        x:200
    }

    Text {
        id: total_weight2
        text: qsTr("");
        y:320
        x:200
    }

    Rectangle {
        id: elevator1
        x: 10
        y: 10
        width: 40
        height: 600
        color: "#f9f2bd"
        Rectangle {
            id: elevator1_img
            x: 0
            y: 570
            z: 10
            width: 40
            height: 30
            color: "#123456"
    //        source: "/home/n2qv/viettel/Sample/elevator.jpg"
            states: State {
                    name: "move_e1"
                    PropertyChanges { target: elevator1_img; y: 60}
                }
            transitions: Transition {
                SequentialAnimation {
                    PropertyAnimation { property: "y"; duration: 1000 }
                }
            }
        }
    }

    Rectangle {
        id: elevator2
        x: 280
        y: 10
        width: 40
        height: 600
        color: "#f9f2bd"

        Rectangle {
            id: elevator2_img
            x: 0
            y: 570
            z: 10
            width: 40
            height: 30
            color: "#123456"
    //        source: "/home/n2qv/viettel/Sample/elevator.jpg"
        }
    }

    Text {
        id: text1
        x: 335
        y: 18
        text: qsTr("Floor 20")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 335
        y: 586
        text: qsTr("Floor 1")
        font.pixelSize: 12
    }

    Rectangle {
        id: rectangle_panel
        x: 90
        y: 40
        width: 150
        height: 100
        color: "#50d1e1"

        TextInput {
            id: txt_input
            x: 35
            y: 15
            width: 80
            height: 20
            color: "#350101"
            text: "0"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }

        Button {
            id: btn_panel
            x: 35
            y: 53
            width: 80
            height: 28
            text: qsTr("Enter")
            onClicked: {
                var y = parseInt(txt_input.text);
                timer1.start();
//              elevator1_img.y = y*30;
                txt_input.text = "";
//                elevator1_img.state == 'move_e1' ? elevator1_img.state = '' : elevator1_img.state = 'move_e1'

            }
        }
    }

}
