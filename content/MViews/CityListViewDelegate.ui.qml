

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls

Button {
    signal cityButtonPressed(string cityName)
    id: delegate
    width: ListView.view.width
    height: ListView.view.height / 7
    text: name
    font.pixelSize: 32

    Connections{
        function onClicked(){
            delegate.ListView.view.currentIndex = index
            cityButtonPressed(name)
            //weatherDataSource.getWeatherForecast(name)
        }
    }
}
