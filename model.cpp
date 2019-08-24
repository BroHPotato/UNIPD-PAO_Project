#include "model.h"

Model::Model(QObject * parent) : QAbstractListModel (parent)
{

}
int Model::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return library.GetSize();
}
bool Model::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; row++) {
        AbstractItem* p =nullptr;
        library.Insert(position,p);
    }
    endInsertRows();
    return true;
}

bool Model::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        library.Remove(position);
    }
    endRemoveRows();
    return true;
}
int Model::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 5;
}
QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole && library[index.row()])
    {
        if ( index.column() == 0)
            return library[index.row()]->GetTitle();

        if ( index.column() == 1)
            return library[index.row()]->GetDesc();

        if ( index.column() == 2)
            return library[index.row()]->GetSize();

        if ( index.column() == 3)
            return library[index.row()]->GetFormat();

        if ( index.column() == 4)
            return dataType(index,Qt::DisplayRole);
    }
    return  QVariant();
}
bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        if (index.column() == 0)
            library[index.row()]->SetTitle(value.toString());
        else if (index.column() == 1)
            library[index.row()]->SetDesc(value.toString());
        else if (index.column() == 2)
            library[index.row()]->SetSize(value.toDouble());
        else if (index.column() == 3)
            library[index.row()]->SetFormat(value.toString());
        else
            return false;

        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

bool Model::setDataItem(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        library[index.row()]=value.value<AbstractItem*>();
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}
QVariant Model::dataType(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole && library[index.row()])
        return library[index.row()]->GetType();

    return  QVariant();
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

Container<AbstractItem *> Model::getLib()const
{
    return library;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return "Nome file";
            case 1:
                return "Descrizione";
            case 2:
                return "Dimensione";
            case 3:
                return "Estensione";
            case 4:
                return "Categoria";
            default:
                return QVariant();
        }
    }
    return QVariant();
}
