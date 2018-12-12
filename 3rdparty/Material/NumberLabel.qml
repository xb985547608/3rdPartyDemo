import QtQuick 2.0
import Material 0.3

Item {
    property int number: 0
    property int lastNumber: 0
    property alias color: label.color
    property alias style: label.style
    property int fieldWidth: 0
    property string fillChar: " "

    onNumberChanged: prepare()

    width: label.implicitWidth
    height: label.implicitHeight

    Label {
        id: label
        style: "display3"
        anchors.verticalCenter: parent.verticalCenter
        text: {
            var str = number.toString()
            while (str.length < Math.abs(fieldWidth)) {
                str = fieldWidth > 0 ? fillChar.charAt(0) + str :
                                       str + fillChar.charAt(0)
            }
            return str
        }
    }

    ParallelAnimation {
        id: animation
        NumberAnimation {
            id: enterAni
            target: label
            property: "anchors.verticalCenterOffset"
            to: 0
            duration: 250
            easing.type: Easing.OutQuad
        }
        NumberAnimation {
            target: label
            property: "opacity"
            from: 0; to: 1
            duration: 250
            easing.type: Easing.InQuad
        }

        onStopped: lastNumber = number
    }

    function prepare() {
        enterAni.from = height*0.3 * (number > lastNumber ? -1 : 1)
        animation.running = true
    }
}
