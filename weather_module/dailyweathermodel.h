#ifndef DAILYWEATHERMODEL_H
#define DAILYWEATHERMODEL_H

#include <QAbstractListModel>
#include <qqml.h>
#include "datasource.h"

class DailyWeatherModel : public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DailyWeatherModel)
    Q_PROPERTY(DataSource* dataSource READ setDataSource WRITE setDataSource NOTIFY dataSourceChanged FINAL)
public:
    explicit DailyWeatherModel(QObject *parent = nullptr);

    enum class DailyWeatherRoles
    {
        DayRole = Qt::UserRole,
        IconRole,
        TemperatureRole
    };
    Q_ENUM(DailyWeatherRoles);

signals:
    // QAbstractItemModel interface
    void dataSourceChanged();

public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    DataSource *setDataSource() const;
    void setDataSource(DataSource *newDataSource);
private:
    DataSource *m_dataSource{nullptr};
    bool m_isConnectedToSignals{false};
};

#endif // DAILYWEATHERMODEL_H
