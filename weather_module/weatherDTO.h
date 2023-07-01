#ifndef WEATHERDTO_H
#define WEATHERDTO_H

#include <QString>
#include <QUrl>

struct WeatherDTO
{
    WeatherDTO(const QString& day, const QUrl& icon, const QString& temperature, QObject *parent = nullptr)
        : m_day{day}
        , m_icon{icon}
        , m_temperature{temperature}
    {}

    QString m_day;
    QUrl m_icon;
    QString m_temperature;
};

#endif // WEATHERDTO_H
