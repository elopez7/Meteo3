// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.5
import Meteo3

Window {
    width: 1920
    height: 1080

    visible: true
    title: "Meteo3"

    Image {
        id: background
        source: "images/background.jpg"
    }

    Screen01 {
        id: mainScreen
        anchors.fill: parent
    }

}

