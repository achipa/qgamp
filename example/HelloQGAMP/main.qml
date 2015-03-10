import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import MeasurementProtocol 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    Component.onCompleted: {
        // A good way to time QML startup performance
        Analytics.reportTiming("startup_QML", false);

        // use showScreen to track user navigation
        // note: onCompleted is only good for first screen
        Analytics.showScreen("ApplicationWindow");
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"));
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
        anchors.fill: parent
        button1.onClicked: {
            messageDialog.show(qsTr("Button 1 pressed"))

            // report event, params: category, action, value
            Analytics.reportEvent("UI", "Button1", 0);

            // start named timer, params: timername, reset timer if already eists
            Analytics.startTiming("b1timer", true);
        }
        button2.onClicked: {
            messageDialog.show(qsTr("Button 2 pressed"))

            // report event, params: category, action, value
            Analytics.reportEvent("UI", "Button2", 0);
            Analytics.reportRawTiming("b2timer", 100);
        }
        button3.onClicked: {
            messageDialog.show(qsTr("Button 3 pressed"))

            // report event, params: category, action, value
            Analytics.reportEvent("UI", "Button3", 0);

            // report time elapsed from starting given timer, params: timername, reset timer
            Analytics.reportTiming("b1timer", true);
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
