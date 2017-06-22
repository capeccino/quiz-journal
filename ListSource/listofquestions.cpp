#include "ItemHeaders/question.h"

#include "ListHeaders/listofquestions.h"

#include "database.h"

ListOfQuestions::ListOfQuestions(QObject *parent)
{
    connect(this, SIGNAL(passNextToEntry(QVariant*)), parent, SLOT(receiveFromList(QVariant*)));
    connect(this, SIGNAL(passFINALToEntry(QVariant*)), parent, SLOT(receiveFINALFromList(QVariant*)));
    db = new Database("questions", this);
}

void ListOfQuestions::fillListFromDB(QString dbName)
{
    db->connectDB(dbName);

    db->fillQuestionStructure(list);
}

void ListOfQuestions::dumpListToDB(QString dbName)
{
    db->connectDB(dbName);

    if(db->createTables("SpecificJournal"))
    {
        for(auto iter = list.begin(); iter != list.end(); ++iter)
        {
            db->insertQuestion(*iter);
        }
    }
}

Question* ListOfQuestions::questionFromList(int index)
{
    QLinkedList<Question*>::const_iterator iter;
    iter = list.begin();
    iter += index;

    return *iter;
}

void ListOfQuestions::removeFromList(int index)
{
    QLinkedList<Question*>::iterator iter;
    iter = list.begin();
    iter += index;

    list.erase(iter);
}

void ListOfQuestions::appendToList(Question* q)
{
    list.append(q);
}

void ListOfQuestions::receiveNextSignal(QVariant *v)
{
    emit passNextToEntry(v);
}

void ListOfQuestions::receiveFINALSignal(QVariant *v)
{
    emit passFINALToEntry(v);
}

