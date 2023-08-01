import QtQuick
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import MyGeometryExample

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    RoundButton {
        z:1
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Import"
        font.bold: true
        palette.button: "slategrey"
        onClicked: shapeSpawner.addShape()
    }

    ViewManager {
        id: manager
    }

    color: "black"

    View3D {
        id: v3d
        anchors.fill: parent
        camera: camera

        Node {
            id: originNode
            PerspectiveCamera {
                id: camera
                position: Qt.vector3d(0, 0, 600)
            }
        }

        OrbitCameraController {
            anchors.fill: parent
            origin: originNode
            camera: camera
        }

        DirectionalLight {
            position: Qt.vector3d(-500, 500, -100)
            color: Qt.rgba(0.4, 0.2, 0.6, 1.0)
            ambientColor: Qt.rgba(0.1, 0.1, 0.1, 1.0)
        }

        PointLight {
            position: Qt.vector3d(0, 0, 100)
            color: Qt.rgba(0.1, 1.0, 0.1, 1.0)
            ambientColor: Qt.rgba(0.2, 0.2, 0.2, 1.0)
        }

        Node {
            id: shapeSpawner
            property var instances: []
            property int count

            function addShape() {
                manager.loadFile()
                for(var i = 0; i < manager.geometrys.length; i++) {
                    var geo = manager.geometrys[i]
                    var shapeComponent = Qt.createComponent("Shape.qml")
                    if(shapeComponent.status === Component.Ready) {
                        var props = {}
                        props["geometryData"] = geo
                        let instance = shapeComponent.createObject(shapeSpawner, props)
                        instances.push(instance)
                        count = instances.length
                    }
                }
            }
        }
    }

    MouseArea {
        anchors.fill: v3d
        onClicked: function(mouse) {
            var result = v3d.pick(mouse.x, mouse.y)
            if (result.objectHit) {
                var pickedObject = result.objectHit
                pickedObject.isPicked = !pickedObject.isPicked
            }
        }
    }
}
