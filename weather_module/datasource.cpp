#include <QJsonArray>
#include <QTimer>
#include "datasource.h"


DataSource::DataSource(QObject *parent)
    : QObject{parent}
    , timer{new QTimer{this}}
{
    connect(&m_apiClient, &ApiClient::onDataFetchFinished, this, &DataSource::onDataFetchFinished);

    timer->setInterval(1800000);
    connect(timer, &QTimer::timeout, this, [&](){
        getWeatherForecast(m_currentLocation);
    });
    this->getWeatherForecast("London");
    timer->start();
}

void DataSource::getWeatherForecast(const QString &location)
{
    m_currentLocation = location;
    m_apiClient.onGetLocation(location);
}

void DataSource::onDataFetchFinished(QJsonDocument weatherObject)
{
    QJsonObject currentWeatherObject = weatherObject["current"].toObject();

    QJsonArray weatherDescription = currentWeatherObject["weather"].toArray();
    QJsonObject weatherDescriptionObject{weatherDescription[0].toObject()};

    setWeatherProperties(weatherDescriptionObject, currentWeatherObject);

    moveWeatherJsonArrayToLocalListModel(weatherObject);
}

void DataSource::setWeatherProperties(QJsonObject weatherDescriptionObject, QJsonObject currentWeatherObject)
{
    m_currentWeather = (weatherDescriptionObject["main"].toString());
    m_currentTemperature = (QString::number(currentWeatherObject["temp"].toDouble(), 'f', 0)) + "°C";
                           m_currentHumidity = "Humidity: " + (QString::number(currentWeatherObject["humidity"].toDouble())) + " %";
    m_currentWind = "Wind: " + (QString::number((currentWeatherObject["wind_speed"].toDouble()/1000)*3600, 'f', 2)) + " km/h";
    QString iconNumber{weatherDescriptionObject["icon"].toString()};
    m_weatherIcon = QStringLiteral("https://openweathermap.org/img/wn/") + iconNumber + QStringLiteral("@2x.png");
}

void DataSource::moveWeatherJsonArrayToLocalListModel(QJsonDocument weatherObject)
{
    resetListModel();

    QJsonArray dailyWeatherArray = weatherObject["daily"].toArray();

    for(auto i : dailyWeatherArray)
    {
        QJsonObject dailyWeatherObject{i.toObject()};
        QJsonObject tempObject{dailyWeatherObject["temp"].toObject()};
        QJsonArray weatherObjectArray = dailyWeatherObject["weather"].toArray();

        double timeStamp{dailyWeatherObject["dt"].toDouble()};
        QDateTime forecastTime{};
        forecastTime.setSecsSinceEpoch(timeStamp);

        WeatherDTO* temporaryWeatherObject{new WeatherDTO(forecastTime.toString("ddd"),
                                                          QStringLiteral("https://openweathermap.org/img/wn/") + weatherObjectArray.at(0)["icon"].toString() + QStringLiteral("@2x.png"),
                                                          QString::number(tempObject["day"].toDouble(), 'f', 0) + "°C",
                                                              this)};
        appendWeatherToList(temporaryWeatherObject);
    }
}

void DataSource::resetListModel()
{
    if(!m_dailyWeatherList.empty())
    {
        emit preResetModel();
        m_dailyWeatherList.clear();
        emit postResetModel();
    }
}

void DataSource::appendWeatherToList(WeatherDTO *weatherToAdd)
{
    emit preAddWeatherToModel();
    m_dailyWeatherList.append(weatherToAdd);
    emit postAddWeatherToModel();
}

QList<WeatherDTO *> DataSource::getDailyWeatherList() const
{
    return m_dailyWeatherList;
}

QString DataSource::getCurrentWeather() const
{
    return m_currentWeather;
}

void DataSource::setCurrentWeather(const QString &newCurrentWeather)
{
    m_currentWeather = newCurrentWeather;
}

QString DataSource::getCurrentTemperature() const
{
    return m_currentTemperature;
}

void DataSource::setCurrentTemperature(const QString &newCurrentTemperature)
{
    m_currentTemperature = newCurrentTemperature;
}

QString DataSource::getCurrentHumidity() const
{
    return m_currentHumidity;
}

void DataSource::setCurrentHumidity(const QString &newCurrentHumidity)
{
    m_currentHumidity = newCurrentHumidity;
}

QString DataSource::getCurrentWind() const
{
    return m_currentWind;
}

void DataSource::setCurrentWind(const QString &newCurrentWind)
{
    m_currentWind = newCurrentWind;
}

QString DataSource::getCurrentLocation() const
{
    return m_currentLocation;
}

void DataSource::setCurrentLocation(const QString &newCurrentLocation)
{
    m_currentLocation = newCurrentLocation;
}

QUrl DataSource::getWeatherIcon() const
{
    return m_weatherIcon;
}

void DataSource::setWeatherIcon(const QUrl &newWeatherIcon)
{
    m_weatherIcon = newWeatherIcon;
}
