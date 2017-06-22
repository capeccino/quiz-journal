//JournalModel is the model to control the Journal List View on the main page.
//It contains the ListOfJournals.

#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include <QAbstractListModel>

class ListOfJournals;

class JournalModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit JournalModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeData(const QModelIndex &index);

    void initialFill();

    ListOfJournals *listOfJ;

private:
    int numRows = 0;
};

#endif // JOURNALMODEL_H
