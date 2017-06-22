//ListOfJournals maintains the data structure that holds the names and dates of user's Journals,
//as well as the DB connection that must interact with the data structure.

#ifndef LISTOFJOURNALS_H
#define LISTOFJOURNALS_H

#include <QList>
#include "database.h"

class ListOfJournals
{
public:
    ListOfJournals();

    QList<journal*> list;

    void fillListFromDB();
    void insertIntoDB(journal* j);
    QString journalFromList(int index);
    void removeFromList(int index);
    void appendToList(journal* j);
    QString dateString(QDateTime dt);

    journal *temp = nullptr;

private:
    Database db = Database("journals");
};

#endif // LISTOFJOURNALS_H
