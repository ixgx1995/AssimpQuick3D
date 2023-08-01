import QtQuick
import QtQuick3D

Node {
    id: shape

    property var geometryData

    property real xRotation: Math.random() * (360 - (-360)) + -360
    property real yRotation: Math.random() * (360 - (-360)) + -360
    property real zRotation: Math.random() * (360 - (-360)) + -360
    property real hue: Math.random()

    property bool isPicked: false

    Model {
        id: model
        property bool isPicked: shape.isPicked
        scale: Qt.vector3d(100, 100, 100)
        eulerRotation.x: 90
        pickable: true
        geometry: geometryData
        onIsPickedChanged: hue = Math.random()
        SequentialAnimation on eulerRotation {
            loops: Animation.Infinite
            running: model.isPicked
            PropertyAnimation {
                duration: Math.random() * (10000 - 1000) + 1000
                to: Qt.vector3d(xRotation -  360, yRotation - 360, zRotation - 360)
                from: Qt.vector3d(xRotation, yRotation, zRotation)
            }
        }

        materials: [ DefaultMaterial { diffuseColor: model.isPicked ? Qt.hsva(hue, 1.0, 1.0, 1.0) : "red"  } ]
    }
}
