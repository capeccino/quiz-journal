//ListOfEntries maintains the data structure that holds the Entries for a Journal,
//as well as the DB connection that must interact with the data structure.
//Only used for the list of Entries on the main page.

#ifndef LISTOFENTRIES_H
#define LISTOFENTRIES_H

#include <QList>
#include "database.h"

class ListOfEntries
{
public:
    ListOfEntries(QString dbName);

    QList<entry*> list;

    void fillListFromDB();
    QString entryFromList(int index);
    void removeFromList(int index);
    QString dateString(QDateTime dt);

    entry *temp = nullptr;

private:
    Database db = Database("entries");
};

#endif // LISTOFENTRIES_H
