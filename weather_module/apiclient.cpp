#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QUrlQuery>
#include <QFile>
#include <QDebug>

#include "apiclient.h"

ApiClient::ApiClient(QObject *parent)
    : QObject{parent}
    , m_netManager{new QNetworkAccessManager{this}}
    , m_netReply{nullptr}
    , m_dataBuffer{new QByteArray{}}
{
    Q_INIT_RESOURCE(weatherResources);
    parseUserSecrets();
}

ApiClient::~ApiClient()
{

}

void ApiClient::parseUserSecrets()
{
    QFile file(":/secrets.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to Open File " + file.errorString();
        return;
    }

    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObject = jsonDocument.object();
    m_userSecrets = jsonObject;
    file.close();
}

void ApiClient::onGetLocation(const QString &location)
{
    m_isRequestingLocation = true;
    buildLocationRequestString(location);
    sendGetRequest();
}

void ApiClient::onGetWeather(const QString &latitude, const QString &longitude)
{
    buildWeatheRequestUrl(latitude, longitude);
}

void ApiClient::sendGetRequest()
{
    QNetworkRequest request{m_weatherAPIUrl};
    m_netReply = m_netManager->get(request);

    connect(m_netReply, &QIODevice::readyRead, this, &ApiClient::dataReadyRead);
    connect(m_netReply, &QNetworkReply::finished, this, &ApiClient::dataReadFinished);
}

void ApiClient::dataReadyRead()
{
    m_dataBuffer->append(m_netReply->readAll());
}

void ApiClient::dataReadFinished()
{
    if(m_netReply->error())
    {
        qDebug() << "Error: " << m_netReply->errorString();
        return;
    }
    QJsonDocument doc{QJsonDocument::fromJson(*m_dataBuffer)};
    m_dataBuffer->clear();

    if(!m_isRequestingLocation)
    {
        emit onDataFetchFinished(doc);
        return;
    }

    getLatitudeAndLongitude(doc);
}

void ApiClient::buildLocationRequestString(const QString &location)
{
    m_weatherAPIUrl.setScheme(m_userSecrets["url_scheme"].toString());
    m_weatherAPIUrl.setHost(m_userSecrets["host"].toString());
    m_weatherAPIUrl.setPath(m_userSecrets["location_path"].toString());

    QUrlQuery locationQueries;
    locationQueries.addQueryItem(m_userSecrets["location_query"].toString(), location);
    locationQueries.addQueryItem(m_userSecrets["app_id_query"].toString(), m_userSecrets["api_key"].toString());

    m_weatherAPIUrl.setQuery(locationQueries);
}

void ApiClient::getLatitudeAndLongitude(QJsonDocument locationJsonDocument)
{
    m_isRequestingLocation = false;
    QJsonArray locationsArray = locationJsonDocument.array();
    QJsonObject locationObject{locationsArray[0].toObject()};
    m_latitude = QString::number(locationObject.value(QStringLiteral("lat")).toDouble(), 'f');
    m_longitude = QString::number(locationObject.value(QStringLiteral("lon")).toDouble(), 'f');

    buildWeatheRequestUrl(m_latitude, m_longitude);
    sendGetRequest();
}

void ApiClient::buildWeatheRequestUrl(const QString &latitude, const QString &longitude)
{
    m_weatherAPIUrl.setScheme(m_userSecrets["url_scheme"].toString());
    m_weatherAPIUrl.setHost(m_userSecrets["host"].toString());
    m_weatherAPIUrl.setPath(m_userSecrets["weather_path"].toString());

    QUrlQuery weatherQueries;
    weatherQueries.addQueryItem("lat", latitude);
    weatherQueries.addQueryItem("lon", longitude);
    weatherQueries.addQueryItem("units", "metric");
    weatherQueries.addQueryItem(m_userSecrets["app_id_query"].toString(), m_userSecrets["api_key"].toString());

    m_weatherAPIUrl.setQuery(weatherQueries);
}



QUrlQuery ApiClient::buildWeatherRequestQueries()
{
    return QUrlQuery();
}
