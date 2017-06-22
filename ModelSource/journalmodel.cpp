#include "ModelHeaders/journalmodel.h"
#include "ListHeaders/listofjournals.h"

JournalModel::JournalModel(QObject *parent)
    : QAbstractListModel(parent), numRows(0)
{
    listOfJ = new ListOfJournals();
    initialFill();
}

void JournalModel::initialFill()
{
    for(int i = 0; i < listOfJ->list.size(); i++)
    {
        insertRows(i, 1, QModelIndex());
    }
}

int JournalModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return numRows;
}

QVariant JournalModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        return listOfJ->journalFromList(index.row());
    }

    return QVariant();
}

bool JournalModel::insertRows(int row, int count, const QModelIndex &parent)
{
    count = 1; //only add 1 row at a time. Variable needed to override function.
    beginInsertRows(parent, row, row + count);
    numRows++;
    endInsertRows();

    return true;

}

bool JournalModel::removeRows(int row, int count, const QModelIndex &parent)
{
    count = 1; //only remove 1 row at a time. Variable needed to override function.
    beginRemoveRows(parent, row, row + count);
    numRows--;
    endRemoveRows();

    return true;

}

bool JournalModel::setData(const QModelIndex &index, const QVariant &v, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        journal* j = (journal*)v.value<void*>();
        listOfJ->list.append(j);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool JournalModel::removeData(const QModelIndex &index)
{
    //remove from journal from datastructure - not implemented.
    emit dataChanged(index, index);
    return true;

}
