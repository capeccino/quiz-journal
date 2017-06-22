#include "ModelHeaders/answermodel.h"
#include "ListHeaders/listofanswers.h"
#include "ItemHeaders/answer.h"

AnswerModel::AnswerModel(int id, QString dataName, QObject *parent)
    : QAbstractTableModel(parent)
{
    dbName = dataName;
    EID = id;
    listOfA = new ListOfAnswers();
}

void AnswerModel::initialFill()
{
    listOfA->fillListFromDB(EID, dbName);

    for(int i = 0; i < listOfA->list.size(); i++)
    {
        insertRows(i, 1, QModelIndex());
    }
}

QVariant AnswerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0:
                    return tr("Question");

                case 1:
                    return tr("Answer");

                default:
                    return QVariant();
            }
        }

        return QVariant();
}

int AnswerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return numRows;
}

int AnswerModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant AnswerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        if (index.row() >= numRows || index.row() < 0)
            return QVariant();

        if (role == Qt::DisplayRole)
        {
            answer *a = listOfA->list[index.row()];
            QString mainText = listOfA->db.getQuestionFromQID(a->qid);
            if (index.column() == 0)
                return mainText;
            else if (index.column() == 1)
                return a->qAnswer;
        }
        return QVariant();
}

bool AnswerModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    numRows++;
    endInsertRows();
    return true;
}

bool AnswerModel::setData(const QModelIndex &index, const QVariant &v, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        answer *a = (answer*)v.value<void*>();
        listOfA->list.append(a);
        emit(dataChanged(index, index));
        return true;
     }

     return false;
}

