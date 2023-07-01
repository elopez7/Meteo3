#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QProperty>
#include <QtQml/qqmlregistration.h>
#include "weatherDTO.h"
#include "apiclient.h"


class QTimer;

class DataSource : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(WeatherDataSource)

    Q_PROPERTY(QString currentLocation READ getCurrentLocation WRITE setCurrentLocation BINDABLE bindableCurrentLocation NOTIFY currentLocationChanged FINAL)
    Q_PROPERTY(QString currentWeather READ getCurrentWeather WRITE setCurrentWeather BINDABLE bindableCurrentWeather NOTIFY currentWeatherChanged FINAL)
    Q_PROPERTY(QString currentTemperature READ getCurrentTemperature WRITE setCurrentTemperature BINDABLE bindableCurrentTemperature NOTIFY currentTemperatureChanged FINAL)
    Q_PROPERTY(QString currentHumidity READ getCurrentHumidity WRITE setCurrentHumidity BINDABLE bindableCurrentHumidity NOTIFY currentHumidityChanged FINAL)
    Q_PROPERTY(QString currentWind READ getCurrentWind WRITE setCurrentWind BINDABLE bindableCurrentWind NOTIFY currentWindChanged FINAL)
    Q_PROPERTY(QUrl weatherIcon READ getWeatherIcon WRITE setWeatherIcon BINDABLE bindableWeatherIcon NOTIFY weatherIconChanged FINAL)

public:
    explicit DataSource(QObject *parent = nullptr);

    Q_INVOKABLE void getWeatherForecast(const QString& location);

    QBindable<QString> bindableCurrentLocation() {return &m_currentLocation;}
    QBindable<QString> bindableCurrentWeather() {return &m_currentWeather;}
    QBindable<QString> bindableCurrentTemperature() {return &m_currentTemperature;}
    QBindable<QString> bindableCurrentHumidity() {return &m_currentHumidity;}
    QBindable<QString> bindableCurrentWind() {return &m_currentWind;}
    QBindable<QUrl> bindableWeatherIcon() {return &m_weatherIcon;}

    QString getCurrentWeather() const;
    void setCurrentWeather(const QString &newCurrentWeather);
    QString getCurrentTemperature() const;
    void setCurrentTemperature(const QString &newCurrentTemperature);
    QString getCurrentHumidity() const;
    void setCurrentHumidity(const QString &newCurrentHumidity);
    QString getCurrentWind() const;
    void setCurrentWind(const QString &newCurrentWind);
    QString getCurrentLocation() const;
    void setCurrentLocation(const QString &newCurrentLocation);
    QUrl getWeatherIcon() const;
    void setWeatherIcon(const QUrl &newWeatherIcon);

    QList<WeatherDTO *> getDailyWeatherList() const;
    void appendWeatherToList(WeatherDTO* weatherToAdd);
    void resetListModel();
signals:
    /*Model Related Signals*/
    void preAddWeatherToModel();
    void postAddWeatherToModel();
    void preResetModel();
    void postResetModel();
    /**/

    void currentLocationChanged();
    void currentWeatherChanged();
    void currentTemperatureChanged();
    void currentHumidityChanged();
    void currentWindChanged();
    void weatherIconChanged();

private slots:
    void onDataFetchFinished(QJsonDocument weatherObject);
private:
    ApiClient m_apiClient;
    QTimer *timer;
    QList<WeatherDTO*> m_dailyWeatherList;
    Q_OBJECT_BINDABLE_PROPERTY(DataSource, QString, m_currentLocation, &DataSource::currentLocationChanged)
    Q_OBJECT_BINDABLE_PROPERTY(DataSource, QString, m_currentWeather, &DataSource::currentWeatherChanged)
    Q_OBJECT_BINDABLE_PROPERTY(DataSource, QString, m_currentTemperature, &DataSource::currentTemperatureChanged)
    Q_OBJECT_BINDABLE_PROPERTY(DataSource, QString, m_currentHumidity, &DataSource::currentHumidityChanged)
    Q_OBJECT_BINDABLE_PROPERTY(DataSource, QString, m_currentWind, &DataSource::currentWindChanged)
    Q_OBJECT_BINDABLE_PROPERTY(DataSource, QUrl, m_weatherIcon, &DataSource::weatherIconChanged)

    void moveWeatherJsonArrayToLocalListModel(QJsonDocument weatherObject);
    void setWeatherProperties(QJsonObject weatherDescriptionObject, QJsonObject currentWeatherObject);
};

#endif // DATASOURCE_H
