import QtQuick 2.4
import Material 0.3

Item {
    Wave {
        id: wave
        anchors.fill: parent
        Rectangle {
            anchors.fill: parent
            color: Palette.colors.blueGrey["400"]
        }
    }
    Button {
        anchors.centerIn: parent
        text: qsTr("Toggle")
        onClicked: {
            if (wave.opened)
                wave.close(parent.width - wave.size, parent.height - wave.size)
            else
                wave.open()
        }
    }
}
