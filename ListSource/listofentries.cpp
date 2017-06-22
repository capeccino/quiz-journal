#include "ListHeaders/listofentries.h"
#include "ItemHeaders/entry.h"

ListOfEntries::ListOfEntries(QString dbName)
{
    //This class is only used when Entries must be displayed
    //in the UI. So the list must be filled at instantiation.

    db.connectDB(dbName);
    fillListFromDB();
}

void ListOfEntries::fillListFromDB()
{
    db.fillEntryStructure(list);
}

QString ListOfEntries::entryFromList(int index)
{
    int id = list[index]->EID;
    QString dateStr = dateString(list[index]->date);

    return QString::number(id) + ". " + dateStr;
}

void ListOfEntries::removeFromList(int index)
{
    list.removeAt(index);
}

QString ListOfEntries::dateString(QDateTime dt)
{
    QString date = dt.toString("ddd MMM d, yyyy h:mmap");

    return date;
}
