#pragma once
#include <qabstracttablemodel>
#include "Service/UserService.h"
#include <qtableview.h>
class TrenchModel : public QAbstractTableModel
{
private:
    UserService& service;

public:
    explicit TrenchModel(UserService& service, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};