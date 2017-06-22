#include "ModelHeaders/linkedmodel.h"

#include "ListHeaders/listofquestions.h"

#include "ItemHeaders/question.h"

LinkedModel::LinkedModel(QObject *parent)
    : QAbstractListModel(parent), numRows(0)
{
    listofQ = new ListOfQuestions();
}

int LinkedModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return numRows;
}

QVariant LinkedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        return listofQ->questionFromList(index.row())->strings->at(0);
    }

    return QVariant();
}

bool LinkedModel::insertRows(int row, int count, const QModelIndex &parent)
{
    count = 1; //only add 1 row at a time. Variable needed to override function.
    beginInsertRows(parent, row, row + count);
    numRows++;
    endInsertRows();

    return true;
}

bool LinkedModel::removeRows(int row, int count, const QModelIndex &parent)
{
    count = 1; //only remove 1 row at a time. Variable needed to override function.
    beginRemoveRows(parent, row, row + count);
    numRows--;
    endRemoveRows();

    return true;

}

bool LinkedModel::setData(const QModelIndex &index, const QVariant &v, int role)
{
    //Must convert the Question pointer to a void pointer, in order to use QVariant
    //So it must be converted back to Question pointer from the variant value here,
    //before being inserted into the data structure.

    if(index.isValid() && role == Qt::EditRole)
    {
        Question* q = (Question*)v.value<void*>();
        listofQ->appendToList(q);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool LinkedModel::removeData(const QModelIndex &index)
{
    //Remove by row of view.

    listofQ->removeFromList(index.row());
    emit dataChanged(index, index);
    return true;

}



