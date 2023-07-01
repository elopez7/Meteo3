

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import weatherModule

ListView {
    property alias dataSource: dailyWeatherModel.dataSource

    id: view
    width: 420
    height: 420
    interactive: false
    orientation: ListView.Horizontal

    DailyWeatherModel{
        id: dailyWeatherModel
        dataSource: dataSource
    }

    model: dailyWeatherModel

    delegate: WeatherListViewDelegate {}
}
