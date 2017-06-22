//ListOfAnswers maintains the data structure that holds the Answers to an Entry,
//as well as the DB connection that must interact with the data structure.

#ifndef LISTOFANSWERS_H
#define LISTOFANSWERS_H

#include <QList>
#include "database.h"

struct answer;

class ListOfAnswers
{
public:
    ListOfAnswers();

    QList<answer*> list;

    void fillListFromDB(int id, QString dbName);
    void dumpListToDB(QString dbName);
    answer* answerFromList(int index);
    void appendToList(answer* a);

    Database db = Database("answers");
};

#endif // LISTOFANSWERS_H
