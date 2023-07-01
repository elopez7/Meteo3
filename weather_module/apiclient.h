#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;

class ApiClient : public QObject
{
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = nullptr);
    virtual ~ApiClient();

signals:
    void onDataFetchFinished(QJsonDocument weatherJsonDocument);

public slots:
    void onGetLocation(const QString& location);
    void onGetWeather(const QString &latitude, const QString &longitude);
    void dataReadyRead();
    void dataReadFinished();


private:
    bool m_isRequestingLocation;
    QString m_latitude;
    QString m_longitude;
    QNetworkAccessManager *m_netManager;
    QNetworkReply *m_netReply;
    QByteArray *m_dataBuffer;

    QUrl m_weatherAPIUrl;

    QString m_appIdQuery{QStringLiteral("appid")};
    QString m_unitsQuery{QStringLiteral("units")};
    QJsonObject m_userSecrets;

    void parseUserSecrets();
    void buildLocationRequestString(const QString &location);
    void buildWeatheRequestUrl(const QString &latitude, const QString &longitude);
    void getLatitudeAndLongitude(QJsonDocument locationJsonDocument);
    QUrlQuery buildWeatherRequestQueries();
    void sendGetRequest();
};

#endif // APICLIENT_H
