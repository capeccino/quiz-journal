#include "ModelHeaders/entrymodel.h"
#include "ListHeaders/listofentries.h"

EntryModel::EntryModel(QString dbName, QObject *parent)
    : QAbstractListModel(parent)
{
    //Fill at instantiation

    listOfE = new ListOfEntries(dbName);
    initialFill();
}

void EntryModel::initialFill()
{
    for(int i = 0; i < listOfE->list.size(); i++)
    {
        insertRows(i, 1, QModelIndex());
    }
}

int EntryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return numRows;
}

QVariant EntryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        return listOfE->entryFromList(index.row());
    }

    return QVariant();
}

bool EntryModel::insertRows(int row, int count, const QModelIndex &parent)
{
    count = 1; //only add 1 row at a time. Variable needed to override function.
    beginInsertRows(parent, row, row + count);
    numRows++;
    endInsertRows();

    return true;

}

bool EntryModel::removeRows(int row, int count, const QModelIndex &parent)
{
    count = 1; //only remove 1 row at a time. Variable needed to override function.
    beginRemoveRows(parent, row, row + count);
    numRows--;
    endRemoveRows();

    return true;

}

bool EntryModel::setData(const QModelIndex &index, const QVariant &v, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        entry* e = (entry*)v.value<void*>();
        listOfE->list.append(e);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool EntryModel::removeData(const QModelIndex &index)
{
    //remove from entry from datastructure - not implemented.
    emit dataChanged(index, index);
    return true;

}
