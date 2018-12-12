/*
 * QML Material - An application framework implementing Material Design.
 *
 * Copyright (C) 2015-2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.4
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls.Styles 1.3 as ControlStyles

import Material 0.3

/*!
   \qmltype Switch
   \inqmlmodule Material

   \brief On/off switches toggle the state of a single settings option
 */
Controls.Switch {
    id: control

    /*!
       The switch color. By default this is the app's accent color
     */
    property color color: darkBackground ? Theme.dark.accentColor
                                         : Theme.light.accentColor

    /*!
       Set to \c true if the switch is on a dark background
     */
    property bool darkBackground

    style: ControlStyles.SwitchStyle {
        handle: View {
            id: view
            width: 22 * Units.dp
            height: 22 * Units.dp
            radius: height / 2
            elevation: 1
            clipContent: false
            backgroundColor: control.enabled ? control.checked ? control.color
                                                               : darkBackground ? "#BDBDBD"
                                                                                : "#FAFAFA"
                                             : darkBackground ? "#424242"
                                                              : "#BDBDBD"


            Connections {
                target: control
                onPressedChanged: {
                    if (control.pressed)
                        tapEffect.running = true
                }
            }

            Rectangle {
                id: tap
                anchors.centerIn: parent

                width: radius * 2
                height: radius * 2

                opacity: 0
                color: control.checked ? Theme.alpha(view.backgroundColor, 0.20) :
                                         Qt.rgba(0,0,0,0.1)

                SequentialAnimation {
                    id: tapEffect
                    ParallelAnimation {
                        NumberAnimation {
                            target: tap; property: "radius"; duration: 250;
                            from: view.width/2; to: width; easing.type: Easing.InOutQuad
                        }

                        NumberAnimation {
                            target: tap; property: "opacity"; duration: 150;
                            from: 0; to: 1; easing.type: Easing.InOutQuad
                        }
                    }
                    NumberAnimation {
                        target: tap; property: "opacity"; duration: 150;
                        from: 1; to: 0; easing.type: Easing.InOutQuad
                    }
                }
            }
        }

        groove: Item {
            width: 40 * Units.dp
            height: 22 * Units.dp

            Rectangle {
                anchors.centerIn: parent
                width: parent.width - 2 * Units.dp
                height: 16 * Units.dp
                radius: height / 2
                color: control.enabled ? control.checked ? Theme.alpha(control.color, 0.5)
                                                         : darkBackground ? Qt.rgba(1, 1, 1, 0.26)
                                                                          : Qt.rgba(0, 0, 0, 0.26)
                                       : darkBackground ? Qt.rgba(1, 1, 1, 0.12)
                                                        : Qt.rgba(0, 0, 0, 0.12)

                Behavior on color {
                    ColorAnimation {
                        duration: 200
                    }
                }
            }
        }

        panel: Item {

            implicitWidth: Math.round(grooveLoader.width + padding.left + padding.right)
            implicitHeight: grooveLoader.implicitHeight + padding.top + padding.bottom

            property var __handle: handleLoader
            property int min: padding.left
            property int max: grooveLoader.width - handleLoader.width - padding.right



            Loader {
                id: grooveLoader
                y: padding.top
                x: padding.left

                sourceComponent: groove
                anchors.verticalCenter: parent.verticalCenter

                Loader {
                    id: handleLoader

                    z:1

                    x: control.checked ? max : min

                    anchors.top: grooveLoader.top
                    anchors.bottom: grooveLoader.bottom
                    anchors.topMargin: padding.top
                    anchors.bottomMargin: padding.bottom

                    Behavior on x {
                        id: behavior
                        enabled: handleLoader.status === Loader.Ready
                        SpringAnimation {
                            mass: 0.28
                            spring: 3
                            damping: 0.11
                        }
                    }
                    sourceComponent: handle
                }
            }
        }
    } 
}
