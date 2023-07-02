

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: delegate
    width: ListView.view.width / 7
    spacing: 80

    Label {
        id: weekDay
        text: day
        font.pixelSize: 26
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    }

    Image {
        id: weatherIcon
        source: icon
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        sourceSize.height: 128
        sourceSize.width: 128
    }

    Label {
        id: dayTemperature
        text: temperature
        font.pixelSize: 26
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    }
}
