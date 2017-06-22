#include "ListHeaders/listofanswers.h"
#include "ItemHeaders/answer.h"

ListOfAnswers::ListOfAnswers(){}

void ListOfAnswers::fillListFromDB(int id, QString dbName)
{
    db.connectDB(dbName);

    db.fillAnswerStructureFromEID(id, list);
}

void ListOfAnswers::dumpListToDB(QString dbName)
{
    db.connectDB(dbName);

    for(int i = 0; i < list.size(); i++)
    {
        db.insertAnswer(list[i]);
    }
}

answer* ListOfAnswers::answerFromList(int index)
{
    return list[index];
}

void ListOfAnswers::appendToList(answer* a)
{
    list.append(a);
}
