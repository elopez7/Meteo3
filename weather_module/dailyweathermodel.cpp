#include "enumconverters.h"
#include "weatherDTO.h"
#include "dailyweathermodel.h"

DailyWeatherModel::DailyWeatherModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int DailyWeatherModel::rowCount(const QModelIndex &parent) const
{
    return m_dataSource->getDailyWeatherList().count();
}

QVariant DailyWeatherModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    WeatherDTO* dailyWeather{m_dataSource->getDailyWeatherList().at(index.row())};

    switch (role) {
    case +DailyWeatherRoles::DayRole:
        return dailyWeather->m_day;
        break;
    case +DailyWeatherRoles::IconRole:
        return dailyWeather->m_icon;
        break;
    case +DailyWeatherRoles::TemperatureRole:
        return dailyWeather->m_temperature;
        break;
    default:
        break;
    }
    return QVariant();
}

Qt::ItemFlags DailyWeatherModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> DailyWeatherModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[+DailyWeatherRoles::DayRole] = "day";
    roles[+DailyWeatherRoles::IconRole] = "icon";
    roles[+DailyWeatherRoles::TemperatureRole] = "temperature";
    return roles;
}

DataSource *DailyWeatherModel::setDataSource() const
{
    return m_dataSource;
}

void DailyWeatherModel::setDataSource(DataSource *newDataSource)
{
    beginResetModel();
    if(m_dataSource && m_isConnectedToSignals)
    {
        m_dataSource->disconnect(this);
    }
    m_dataSource = newDataSource;

    connect(m_dataSource, &DataSource::preResetModel, this, [=](){
        beginResetModel();
    });
    connect(m_dataSource, &DataSource::postResetModel, this, [=](){
        endResetModel();
    });

    connect(m_dataSource, &DataSource::preAddWeatherToModel, this, [=](){
        const int index = m_dataSource->getDailyWeatherList().count();
        beginInsertRows(QModelIndex(), index, index);
    });
    connect(m_dataSource, &DataSource::preAddWeatherToModel, this, [=](){
        endInsertRows();
    });
    endResetModel();
}


