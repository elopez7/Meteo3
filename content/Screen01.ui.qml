

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import weatherModule
import Meteo3
import "MViews"

Item {
    id: root

    WeatherDataSource{
        id: weatherDataSource
        currentLocation: qsTr("London")
    }

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        CityListView {
            id: cityListView
            Layout.preferredWidth: 400
            Layout.fillHeight: true
            clip: true
            weatherDataSource: weatherDataSource
        }

        ColumnLayout {
            id: forecast
            Layout.margins: 50
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 100

            ColumnLayout {
                spacing: 30
                Label {
                    id: dateLabel
                    font {
                        pixelSize: 40
                        family: "Roboto"
                    }

                    Timer {
                        running: Qt.application.state === Qt.ApplicationActive
                        interval: 5000
                        repeat: true
                        triggeredOnStart: true
                        onTriggered: dateLabel.text = Qt.formatDate(
                                         new Date(), Locale.LongFormat)
                    }
                }

                Label {
                    id: cityLabel
                    font {
                        pixelSize: 30
                        family: "Roboto"
                    }
                }
            }

            RowLayout {
                id: currentWeather
                spacing: 100
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                ColumnLayout {
                    id: currentWeatherLeftSide
                    spacing: 30
                    Label {
                        id: currentWeatherLabel
                        text: "clear"
                        font.pixelSize: 30
                    }

                    Image {
                        id: currentWeatherImage
                        source: "images/PlaceHolderIcon.png"
                        sourceSize.height: 128
                        sourceSize.width: 128
                    }

                    Label {
                        id: currentTemperatureLabel
                        text: "29 C"
                        font.pixelSize: 30
                    }
                }

                ColumnLayout {
                    id: currentWeatherrightSide
                    spacing: 30
                    Label {
                        id: humidityLabel
                        text: qsTr("Humidity: 61%")
                        font.pixelSize: 30
                    }

                    Label {
                        id: windSpeed
                        text: qsTr("Wind: 1.2km/h")
                        font.pixelSize: 30
                    }
                }
            }

            WeatherListView {
                id: weatherListView
                clip: true
                Layout.fillWidth: true
                Layout.preferredHeight: contentItem.childrenRect.height
                dataSource: weatherDataSource
            }
        }
    }

    Binding{cityLabel.text: weatherDataSource.currentLocation}
    Binding{currentWeatherLabel.text: weatherDataSource.currentWeather}
    Binding{currentWeatherImage.source: weatherDataSource.weatherIcon}
    Binding{currentTemperatureLabel.text: weatherDataSource.currentTemperature}
    Binding{humidityLabel.text: weatherDataSource.currentHumidity}
    Binding{windSpeed.text: weatherDataSource.currentWind}
}
