//EntryModel is the model to control the Entry List View on the main page.
//It is the only class to interact with ListOfEntries.

#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <QAbstractListModel>

class ListOfEntries;

class EntryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit EntryModel(QString dbName, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeData(const QModelIndex &index);

    void initialFill();

    ListOfEntries *listOfE = nullptr;

private:
    int numRows = 0;
};

#endif // ENTRYMODEL_H
