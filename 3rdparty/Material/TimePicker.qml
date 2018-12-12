/*
 * QML Material - An application framework implementing Material Design.
 *
 * Copyright (C) 2015 Steve Coffey <scoffey@barracuda.com>
 *               2015 Jordan Neidlinger <JNeidlinger@gmail.com>
 *               2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.4
import Material 0.3
import Material.Extras 0.1
import QtQuick.Controls 1.3 as QuickControls
import QtQuick.Controls.Styles 1.3

FocusScope {
    id: timePicker

    width: 300 * Units.dp
    height: content.height

    /*!
       Set to \c true if selection is 24 hour based. Defaults to false
     */
    property bool prefer24Hour: false

    /*!
       The visual padding around the clock element
     */
    property real clockPadding: 24 * Units.dp

    /*!
       Set to \c true if the time picker should first show the hours. Defaults to true
     */
    property bool isHours: true

    /*!
       Sets the bottom margin for the time picker
     */
    property int bottomMargin: 0

    Keys.onUpPressed: {
        var date = internal.timePicked

        if(isHours)
            date.setHours(internal.timePicked.getHours() + 1)
        else
            date.setMinutes(internal.timePicked.getMinutes() + 1)

        internal.timePicked = date
    }

    Keys.onDownPressed: {
        var date = internal.timePicked

        if(isHours)
            date.setHours(internal.timePicked.getHours() - 1)
        else
            date.setMinutes(internal.timePicked.getMinutes() - 1)

        internal.timePicked = date
    }

    Keys.onLeftPressed: {
        if(!isHours)
            setIsHours(true)
    }

    Keys.onRightPressed: {
        if(isHours)
            setIsHours(false)
    }

    property string __digitsPressed

    Keys.onDigit0Pressed: setDigitsPressed(0)
    Keys.onDigit1Pressed: setDigitsPressed(1)
    Keys.onDigit2Pressed: setDigitsPressed(2)
    Keys.onDigit3Pressed: setDigitsPressed(3)
    Keys.onDigit4Pressed: setDigitsPressed(4)
    Keys.onDigit5Pressed: setDigitsPressed(5)
    Keys.onDigit6Pressed: setDigitsPressed(6)
    Keys.onDigit7Pressed: setDigitsPressed(7)
    Keys.onDigit8Pressed: setDigitsPressed(8)
    Keys.onDigit9Pressed: setDigitsPressed(9)

    QtObject {
        id: internal
        property bool resetFlag: false
        property date timePicked
        property bool completed: false

        onTimePickedChanged: {
            if(completed) {
                var hours = timePicked.getHours()
                if(hours > 11 && !prefer24Hour){
                    hours -= 12
                    amPmPicker.isAm = false
                } else {
                    amPmPicker.isAm = true
                }

                hoursPathView.currentIndex = hours

                var minutes = internal.timePicked.getMinutes()
                minutesPathView.currentIndex = minutes
            }
        }
    }

    Component.onCompleted: {
        internal.completed = true
        internal.timePicked = new Date(Date.now())
                forceActiveFocus()
    }

    Column {
        id:content
        height: childrenRect.height + bottomMargin
        width: parent.width

        Rectangle {
            id: headerView
            width: parent.width
            height: 88 * Units.dp
            color: Theme.accentColor

            NumberLabel {
                id:hoursLabel
                style: "display3"
                color: isHours ? "white" : "#99ffffff"
                number: internal.timePicked.getHours()
                fieldWidth: 2
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: rednikLabel.left

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(!isHours){
                            setIsHours(true)
                        }
                    }
                }
                Behavior on color {
                    ColorAnimation {}
                }
            }

            Label {
                id: rednikLabel
                style: "display3"
                color: "white"
                text:":"
                anchors.centerIn: parent
            }

            NumberLabel {
                id: minutesLabel
                style: "display3"
                color: !isHours ? "white" : "#99ffffff"
                number: internal.timePicked.getMinutes()
                fieldWidth: 2
                fillChar: "0"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: rednikLabel.right

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(isHours){
                            setIsHours(false)
                        }
                    }
                }
                Behavior on color {
                    ColorAnimation {}
                }
            }

            Column {
                id: amPmPicker
                visible: !prefer24Hour

                property bool isAm: true

                anchors {
                    left: minutesLabel.right
                    leftMargin: 12 * Units.dp
                }

                anchors.verticalCenter: parent.verticalCenter

                spacing: 4 * Units.dp

                Label {
                    style: "subheading"
                    font.weight: Font.DemiBold
                    color: amPmPicker.isAm ? "white" : "#99ffffff"
                    text: "AM"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: amPmPicker.isAm = true
                    }

                    Behavior on color {
                        ColorAnimation {}
                    }
                }

                Label {
                    style: "subheading"
                    font.weight: Font.DemiBold
                    color: !amPmPicker.isAm ? "white" : "#99ffffff"
                    text: "PM"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: amPmPicker.isAm = false
                    }

                    Behavior on color {
                        ColorAnimation {}
                    }
                }
            }
        }

        Rectangle {
            id: picker
            width: parent.width
            height: width
            color: "white"

            Rectangle {
                id: circle
                color: "#eee"
                anchors.centerIn: parent
                width: parent.width * 0.9
                height: width
                radius: width / 2

                Rectangle {
                    id: centerPoint
                    anchors.centerIn: parent
                    color: Theme.accentColor
                    width: 8 * Units.dp
                    height: 8 * Units.dp
                    radius: width / 2
                }

                Rectangle {
                    id: pointer
                    color: Theme.accentColor
                    width: 2 * Units.dp
                    height: circle.height / 2 - clockPadding
                    y: clockPadding
                    anchors.horizontalCenter: parent.horizontalCenter
                    antialiasing: true
                    transformOrigin: Item.Bottom

                    Connections {
                        target: hoursPathView
                        onCurrentIndexChanged: {
                            if(isHours)
                                pointer.setAngle()
                        }
                    }

                    Connections {
                        target: minutesPathView
                        onCurrentIndexChanged: {
                            if(!isHours)
                                pointer.setAngle()
                        }
                    }

                    Connections {
                        target: timePicker
                        onIsHoursChanged: pointer.setAngle()
                    }

                    function setAngle()
                    {
                        var idx = isHours ? hoursPathView.currentIndex : minutesPathView.currentIndex
                        var angle
                        if(isHours)
                            angle = (360 / ((prefer24Hour) ? 24 : 12)) * idx
                        else
                            angle = 360 / 60 * idx

                        var adjustAngle = (90 - angle + 360)%360

                        if(Math.abs(pointer.rotation - angle) == 180) {
                            highlightStartRotation.direction = RotationAnimation.Counterclockwise
                            highlightEndRotation.direction = RotationAnimation.Counterclockwise
                            pointerRotation.direction = RotationAnimation.Clockwise
                            canvas.clockwise = true
                        } else {
                            highlightStartRotation.direction = RotationAnimation.Shortest
                            highlightEndRotation.direction = RotationAnimation.Shortest
                            pointerRotation.direction = RotationAnimation.Shortest

                            var diffAngle = canvas.startAngle - adjustAngle
                            if ((0 < diffAngle && diffAngle < 180) ||
                                    ( -360 < diffAngle && diffAngle < -180))
                                canvas.clockwise = true
                            else
                                canvas.clockwise = false
                        }

                        pointer.rotation = angle
                        canvas.startAngle = adjustAngle
                        canvas.endAngle = adjustAngle
                    }

                    Behavior on rotation {
                        RotationAnimation {
                            id: pointerRotation
                            duration: 200
                            direction: RotationAnimation.Shortest
                        }
                    }
                }

                Component {
                    id: pathViewHighlight
                    Rectangle {
                        id: highlight
                        width: 40 * Units.dp
                        height: 40 * Units.dp
                        color: Theme.accentColor
                        radius: width / 2
                    }
                }

                Component {
                    id: pathViewItem
                    Rectangle {
                        id: rectangle
                        width: !isHours && modelData % 5 == 0 ? 20 * Units.dp : isHours ? 30 * Units.dp : 20 * Units.dp
                        height: !isHours && modelData % 5 == 0 ? 20 * Units.dp : isHours ? 30 * Units.dp : 20 * Units.dp
                        color: "transparent"

                        property bool isSelected: false

                        Label {
                            anchors.centerIn: parent
                            text:{
                                var model = isHours ? hoursPathView.model : minutesPathView.model
                                return model.data < 10 && !isHours ? "0" + modelData : modelData
                            }
                            visible: modelData >= 0 && (isHours ? true : modelData % 5 == 0)
                            style: "subheading"
                        }

                        Connections {
                            target: parentMouseArea

                            onClicked: {
                                checkClick(false)
                            }

                            onPositionChanged: {
                                checkClick(true)
                            }

                            function checkClick(isPress)
                            {
                                if((isPress ? parentMouseArea.leftButtonPressed : true) && rectangle.visible) {
                                    var thisPosition = rectangle.mapToItem(null, 0, 0, width, height)

                                    if(parentMouseArea.globalX > thisPosition.x &&
                                        parentMouseArea.globalY > thisPosition.y &&
                                        parentMouseArea.globalX < (thisPosition.x + width) &&
                                        parentMouseArea.globalY < (thisPosition.y + height)) {

                                        if(!rectangle.isSelected) {
                                            rectangle.isSelected = true

                                            var newDate = new Date(internal.timePicked) // Grab a new date from existing

                                            var time = parseInt(modelData)
                                            if(isHours) {
                                                if(!prefer24Hour && !amPmPicker.isAm && time < 12) {
                                                    time += 12
                                                }
                                                else if(!prefer24Hour && amPmPicker.isAm && time === 12) {
                                                    time = 0
                                                }

                                                newDate.setHours(time)
                                            } else {
                                                newDate.setMinutes(time)
                                            }

                                            internal.timePicked = newDate
                                        }
                                    }
                                    else {
                                        rectangle.isSelected = false
                                    }
                                }
                            }
                        }
                    }
                }

                MouseArea {
                    property bool leftButtonPressed
                    property int globalX
                    property int globalY
                    id: parentMouseArea
                    anchors.fill: circle
                    hoverEnabled: true

                    onClicked: {
                        globalX = parentMouseArea.mapToItem(null, mouse.x, mouse.y).x
                        globalY = parentMouseArea.mapToItem(null, mouse.x, mouse.y).y
                    }

                    onPositionChanged: {
                        if(containsPress)
                        {
                            leftButtonPressed = true
                            globalX = parentMouseArea.mapToItem(null, mouse.x, mouse.y).x
                            globalY = parentMouseArea.mapToItem(null, mouse.x, mouse.y).y
                        }
                        else
                        {
                            leftButtonPressed = false
                        }
                    }
                }

                Canvas {
                    id: canvas
                    anchors.fill: parent
                    renderTarget: Canvas.FramebufferObject

                    property int radius: width/2
                    property int lineWidth: 40 * Units.dp
                    property color color: Theme.accentColor
                    property int margin: 4
                    property int startAngle: 0
                    property int endAngle: 0
                    property bool clockwise: true

                    Behavior on startAngle {
                        RotationAnimation {
                            id: highlightStartRotation
                            duration: 200
                            direction: RotationAnimation.Shortest
                        }
                    }

                    Behavior on endAngle {
                        RotationAnimation {
                            id: highlightEndRotation
                            duration: 300
                            direction: RotationAnimation.Shortest
                        }
                    }

                    onStartAngleChanged: requestPaint()
                    onEndAngleChanged: requestPaint()

                    onPaint: {
                        drawCurve(width/2, height/2, radius, startAngle, endAngle);
                    }

                    function drawCurve(x, y, r, startAngle, endAngle) {
                        var sRadian = Math.PI/180 * (360 - startAngle)
                        var eRadian = Math.PI/180 * (360 - endAngle)
                        r = r - lineWidth/2 - margin
                        context.beginPath();

                        context.clearRect(0, 0, width, height);
                        context.arc(width/2, height/2, r, sRadian, eRadian, clockwise);

                        context.stroke();
                    }

                    Component.onCompleted: {
                        var context = getContext("2d")
                        context.lineWidth = lineWidth
                        context.lineCap = "round"
                        context.strokeStyle = color
                    }
                }

                PathView {
                    id: hoursPathView
                    anchors.fill: parent
                    visible: isHours
                    model: {
                        var limit = prefer24Hour ? 24 : 12
                        var zeroBased = prefer24Hour
                        return getTimeList(limit, zeroBased)
                    }
                    highlightRangeMode: PathView.NoHighlightRange
                    highlightMoveDuration: 250

                    onCurrentIndexChanged: {
                        var newText = currentIndex
                        if(currentIndex == 0 && !prefer24Hour)
                            newText = 12
                        hoursLabel.number = newText
                    }

                    delegate: pathViewItem
                    interactive: false
                    highlight: pathViewHighlight

                    path: Path {
                        startX: circle.width / 2
                        startY: clockPadding

                        PathArc {
                            x: circle.width / 2
                            y: circle.height - clockPadding
                            radiusX: circle.width / 2 - clockPadding
                            radiusY: circle.width / 2 - clockPadding
                            useLargeArc: false
                        }

                        PathArc {
                            x: circle.width / 2
                            y: clockPadding
                            radiusX: circle.width / 2 - clockPadding
                            radiusY: circle.width / 2 - clockPadding
                            useLargeArc: false
                        }
                    }
                }

                PathView {
                    id: minutesPathView
                    anchors.fill: parent
                    visible: !isHours
                    model: {
                        return getTimeList(60, true)
                    }
                    highlightRangeMode: PathView.NoHighlightRange
                    highlightMoveDuration: 250

                    delegate: pathViewItem
                    interactive: false
                    highlight: pathViewHighlight

                    path: Path {
                        startX: circle.width / 2
                        startY: clockPadding

                        PathArc {
                            x: circle.width / 2
                            y: circle.height - clockPadding
                            radiusX: circle.width / 2 - clockPadding
                            radiusY: circle.width / 2 - clockPadding
                            useLargeArc: false
                        }

                        PathArc {
                            x: circle.width / 2
                            y: clockPadding
                            radiusX: circle.width / 2 - clockPadding
                            radiusY: circle.width / 2 - clockPadding
                            useLargeArc: false
                        }
                    }
                }
            }
        }
    }

    /**
      Switches contexts

      If previously we hadn't set hours, and we're now switching contexts, disable the auto switch to minutes
      */
    function setIsHours(_isHours) {
        if(_isHours == isHours)
            return

        if(!internal.resetFlag)
            internal.resetFlag = true

        var prevRotation = pointerRotation.duration
        pointerRotation.duration = 0
        isHours = _isHours
        pointerRotation.duration = prevRotation
    }

    function getCurrentTime() {
        var date = new Date(internal.timePicked)
        if(amPmPicker.isAm && date.getHours() > 11)
            date.setHours(date.getHours() - 12)
        else if(!amPmPicker.isAm && date.getHours() < 11)
            date.setHours(date.getHours() + 12)

        return date
    }

    /*!
       \internal
       Resets the view after closing
     */
    function reset() {
        isHours = true
        internal.resetFlag = false
        amPmPicker.isAm = true
        internal.timePicked = new Date(Date.now())
    }

    /*!
       \internal
       Provides list of ints for pathview based on the context and user prefs
     */
    function getTimeList(limit, isZeroBased) {
        var items = []
        if(!isZeroBased) {
            items[0] = limit
        }

        var start = isZeroBased ? 0 : 1

        var jump = limit > 24 ? 1 : 1
        for(var i = start; i < limit; i += jump) {
            items[i / jump] = i
        }
        return items
    }

    /*!
       \internal
     */
    function setDigitsPressed(minute)
    {
        if(__digitsPressed.length > 1) {
            __digitsPressed = ""
            __digitsPressed = minute
        }
        else {
            __digitsPressed += minute
        }

        var date = internal.timePicked
        var value = parseInt(__digitsPressed)

        if((isHours && value > 23) || (!isHours && value > 59)) {
            __digitsPressed = ""
            return
        }

        if(isHours)
            date.setHours(value)
        else
            date.setMinutes(value)

        internal.timePicked = date
    }
}
