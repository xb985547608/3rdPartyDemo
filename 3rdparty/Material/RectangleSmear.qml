import QtQuick 2.0

Item {
    id: root
    property point futurePos: Qt.point(0, 0)
    property color backgroundColor: "#2196F3"
    property bool isSquare: false
    property real radius: 0
    property bool moving: scaleAni.running || verticalAni.running || horizontalAni.running

    property real originalWidth: 24
    property real originalHeight: 24

    property real horizontalMargin: isSquare ? originalWidth < originalHeight ?
                                                   0 : originalWidth/2 - originalHeight/2 : 0
    property real verticalMargin: isSquare ? originalHeight < originalWidth ?
                                                 0 : originalHeight/2 - originalWidth/2 : 0

    width: originalWidth
    height: originalHeight

    Rectangle {
        id: tailDecorate
        x: horizontalMargin; y: verticalMargin
        width: isSquare ? 1 * Math.min(originalWidth, originalHeight) : originalWidth
        height: isSquare ? width : originalHeight
        color: backgroundColor
        radius: root.radius
        visible: horizontalAni.running || verticalAni.running
    }

    Rectangle {
        id: linkDecorate
        anchors.left: horizontalAni.running ?
                          highlight.x < tailDecorate.x ?
                              highlight.horizontalCenter :
                              tailDecorate.horizontalCenter : undefined
        anchors.right: horizontalAni.running ?
                           highlight.x < tailDecorate.x ?
                               tailDecorate.horizontalCenter :
                               highlight.horizontalCenter : undefined
        anchors.top: verticalAni.running ?
                         highlight.y < tailDecorate.y ?
                             highlight.verticalCenter :
                             tailDecorate.verticalCenter : undefined
        anchors.bottom: verticalAni.running ?
                            highlight.y < tailDecorate.y ?
                                tailDecorate.verticalCenter :
                                highlight.verticalCenter : undefined
        anchors.verticalCenter: horizontalAni.running ? highlight.verticalCenter : undefined
        anchors.horizontalCenter: verticalAni.running ? highlight.horizontalCenter : undefined
        width: horizontalAni.running ? undefined : highlight.width
        height: verticalAni.running ? undefined : highlight.height
        color: backgroundColor
        visible: horizontalAni.running || verticalAni.running
    }

    Rectangle {
        id: highlight
        x: horizontalMargin; y: verticalMargin
        width: isSquare ? 1 * Math.min(originalWidth, originalHeight) : originalWidth
        height: isSquare ? width : originalHeight
        color: backgroundColor
        radius: root.radius
    }

    SequentialAnimation {
        id: horizontalAni

        ParallelAnimation {
            NumberAnimation {
                id: horizontalHighlight
                duration: 150
                target: highlight
                property: "x"
                easing.type: Easing.OutCubic
            }
            NumberAnimation {
                id: horizontalTailDecorate
                duration: 350
                target: tailDecorate
                property: "x"
                easing.type: Easing.OutCubic
            }
        }

        ScriptAction { script: root.complete() }
    }

    SequentialAnimation {
        id: verticalAni

        ParallelAnimation {
            NumberAnimation {
                id: verticalHighlight
                duration: 150
                target: highlight
                property: "y"
                easing.type: Easing.OutCubic
            }
            NumberAnimation {
                id: verticalTailDecorate
                duration: 350
                target: tailDecorate
                property: "y"
                easing.type: Easing.OutCubic
            }
        }

        ScriptAction { script: root.complete() }
    }

    ParallelAnimation {
        id: scaleAni
        ScriptAction {
            script: {
                x = futurePos.x
                y = futurePos.y
            }
        }
        NumberAnimation {
            duration: 150
            target: highlight
            property: "scale"
            from: 0; to: 1
        }
    }

    function complete() {
        x = futurePos.x
        y = futurePos.y
        width = originalWidth
        height = originalHeight
        highlight.x = horizontalMargin
        highlight.y = verticalMargin
        tailDecorate.x = horizontalMargin
        tailDecorate.y = verticalMargin
    }

    function move(pos) {
        // NOTE 避免频繁触发导致的动画异常
        if (moving)
            return;

        futurePos = pos;
        if (pos.x !== x && pos.y !== y) {
            scaleAni.running = true
        } else if (pos.x === x) {

            root.height = Math.abs(futurePos.y - y) + originalHeight
            if (y > futurePos.y) {
                highlight.y = root.height - originalHeight + verticalMargin
                y = futurePos.y
            } else {
                highlight.y = verticalMargin
            }
            tailDecorate.y = highlight.y

            verticalHighlight.to = highlight.y === verticalMargin ?
                        root.height - originalHeight + verticalMargin : verticalMargin
            verticalTailDecorate.to = verticalHighlight.to

            verticalAni.running = true;
        } else if (pos.y === y) {

            root.width = Math.abs(futurePos.x - x) + originalWidth
            if (x > futurePos.x) {
                highlight.x = root.width - originalWidth + horizontalMargin
                x = futurePos.x
            } else {
                highlight.x = horizontalMargin
            }
            tailDecorate.x = highlight.x

            horizontalHighlight.to = highlight.x === horizontalMargin ?
                        root.width - originalWidth + horizontalMargin : horizontalMargin
            horizontalTailDecorate.to = horizontalHighlight.to

            horizontalAni.running = true;
        }
    }
}
