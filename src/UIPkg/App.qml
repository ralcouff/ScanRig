import QtQuick 2.0
import QtQuick.Controls 2.0
import "Components"

ApplicationWindow {
    title: "ScanRig App"
    visible: true
    width: 640
    height: 480

    Loader {
        id: pageLoader
        source: "Views/Capture.qml"
    }

    CButton {
        text: "Capture"
        onClicked: pageLoader.source = "Views/Capture.qml"
        x: 150
    }

    CButton {
        text: "Preview"
        onClicked: {
            for (var prop in backend.captureDeviceSettings) {
                console.log("Object item:", prop, "=", backend.captureDeviceSettings[prop])
            }

            pageLoader.source = "Views/Preview.qml"
        }
    }

    CCameraSettings {
        
    }

    Image {
        id: img
        property bool backBuffer: false

        source: "image://cameraProvider/top" + backBuffer
        asynchronous: false
        fillMode: Image.PreserveAspectFit
        width: 600
        y: 100
        x: 200

        function reload() {
            backBuffer = !backBuffer
            source = "image://cameraProvider/top" + backBuffer
        }

        Timer {
            interval: 16; running: true; repeat: true
            onTriggered: img.reload()
        }
    }

}

