#include "TrenchTableModel.h"
#include <qfont.h>
#include <qbrush.h>

TrenchModel::TrenchModel(UserService& _service, QObject* parent) : service{ _service }
{
}

int TrenchModel::rowCount(const QModelIndex& parent) const
{
    return this->service.getBasket().size();
}

int TrenchModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant TrenchModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    auto ts = this->service.getBasket();
    TrenchCoat t = ts[row];

    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0: {
            return QString::fromStdString(t.getSize()); 
        }
        case 1: {
            return QString::fromStdString(t.getColor());
        }
        case 2:{
            return QString::number(t.getPrice());
        }
        case 3: {
            return QString::number(t.getQuantity());
        }
        case 4: {
            return QString::fromStdString(t.getPhotograph());
        }
        default:
            break;
        }
    }
    return QVariant();
}

QVariant TrenchModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            switch (section)
            {
            case 0:
                return QString{ "Size" };
            case 1:
                return QString{ "Color" };
            case 2:
                return QString{ "Price" };
            case 3:
                return QString{ "Quantity" };
            case 4:
                return QString{ "Photograph" };
            default:
                break;
            }
        }
    }

    return QVariant();
}