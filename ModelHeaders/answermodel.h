//Answer Model is the model to interact with Answer Table Views.
//It contains the ListOfAnswers.

#ifndef ANSWERMODEL_H
#define ANSWERMODEL_H

#include <QAbstractTableModel>

class ListOfAnswers;

class AnswerModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AnswerModel(int id, QString dbName, QObject *parent = 0);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void initialFill();

    ListOfAnswers *listOfA = nullptr;
    QString dbName;
    int EID;

private:
    int numRows = 0;
};

#endif // ANSWERMODEL_H
