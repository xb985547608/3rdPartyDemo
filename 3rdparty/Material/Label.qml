/*
 * QML Material - An application framework implementing Material Design.
 *
 * Copyright (C) 2014-2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.4
import Material 0.3

/*!
   \qmltype Label
   \inqmlmodule Material

   \brief A text label with many different font styles from Material Design.
 */
Text {
    id: label
    property string style: "body1"

    property var fontStyles: {
        "h1": {
            "size": 96,
            "font": "light",
            "letterSpacing": -1.5
        },
        "h2": {
            "size": 60,
            "font": "light",
            "letterSpacing": -0.5
        },
        "h3": {
            "size": 48,
            "font": "regular",
            "letterSpacing": 0
        },
        "h4": {
            "size": 34,
            "font": "regular",
            "letterSpacing": 0.25
        },
        "h5": {
            "size": 24,
            "font": "regular",
            "letterSpacing": 0
        },
        "h6": {
            "size": 20,
            "font": "medium",
            "letterSpacing": 0.15
        },

        // 通常用于长度较短的中等强调文本
        "subtitle1": {
            "size": 16,
            "font": "regular",
            "letterSpacing": 0.15
        },
        "subtitle2": {
            "size": 14,
            "font": "medium",
            "letterSpacing": 0.1
        },

        // 通常用于较长文本
        "body1": {
            "size": 16,
            "font": "regular",
            "letterSpacing": 0.5
        },
        "body2": {
            "size": 14,
            "font": "regular",
            "letterSpacing": 0.25
        },

        "button": {
            "size": 14,
            "font": "medium",
            "letterSpacing": 1.25
        },

        // caption和overline通常用于注释图像或引入标题
        "caption": {
            "size": 12,
            "font": "regular",
            "letterSpacing": 0.4
        },
        "overline": {
            "size": 10,
            "font": "regular",
            "letterSpacing": 1.5
        },

        /*******************************************************************/
        "display4": {
            "size": 112,
            "font": "light"
        },

        "headline": {
            "size": 24,
            "font": "regular"
        },

        "title": {
            "size": 20,
            "font": "medium"
        },

        "dialog": {
            "size": 18,
            "size_desktop": 17,
            "font": "regular"
        },

        "subheading": {
            "size": 16,
            "size_desktop": 15,
            "font": "regular"
        },

        "menu": {
            "size": 14,
            "size_desktop": 13,
            "font": "medium"
        },

        "tooltip": {
            "size_desktop": 13,
            "size": 14,
            "font": "medium"
        }
    }

    property var fontInfo: fontStyles[style]

    font.pixelSize: (!Device.isMobile && fontInfo.size_desktop
            ? fontInfo.size_desktop : fontInfo.size) * Units.dp
    font.family: "Roboto"
    font.weight: {
        var weight = fontInfo.font

        if (weight === "medium") {
            return Font.Medium
        } else if (weight === "regular") {
            return Font.Normal
        } else if (weight === "light") {
            return Font.Light
        }
    }
    font.letterSpacing: fontInfo.letterSpacing ? fontInfo.letterSpacing : 0
    font.capitalization: style == "button" || style == "overline"
                         ? Font.AllUppercase
                         : Font.MixedCase

    color: Theme.light.textColor


}
