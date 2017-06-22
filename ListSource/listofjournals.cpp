#include "ListHeaders/listofjournals.h"
#include "ItemHeaders/journal.h"

ListOfJournals::ListOfJournals()
{
    //Connects to main application DB
    //Fills Journal List at application start.

    db.connectDB("IQJ_DB");
    db.createTables("JournalsDB");
    fillListFromDB();
}

void ListOfJournals::fillListFromDB()
{
    db.fillJournalStructure(list);
}

void ListOfJournals::insertIntoDB(journal* j)
{
    db.insertJournal(j->name, dateString(j->date));
}

QString ListOfJournals::journalFromList(int index)
{
    QString name = list[index]->name;
    QString dateStr = dateString(list[index]->date);

    return name + "\n    Created:\t" + dateStr;
}

void ListOfJournals::removeFromList(int index)
{
    list.removeAt(index);
}

void ListOfJournals::appendToList(journal* j)
{
    list.append(j);
    insertIntoDB(j);
}

QString ListOfJournals::dateString(QDateTime dt)
{
    QString date = dt.toString("ddd MMM d, yyyy h:mmap");

    return date;
}
