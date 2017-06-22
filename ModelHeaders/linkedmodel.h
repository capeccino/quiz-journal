//LinkedModel would better be called QuestionModel, but renaming in Qt is buggy.
//It is a model to control the views that list questions.
//It contains a ListOfQuestions.

#ifndef LINKEDMODEL_H
#define LINKEDMODEL_H

#include <QAbstractListModel>
#include <QString>

class Question;
class ListOfQuestions;

class LinkedModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LinkedModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeData(const QModelIndex &index);

    ListOfQuestions *listofQ;

private:
    int numRows = 0;


};

#endif //LINKEDMODEL_H
