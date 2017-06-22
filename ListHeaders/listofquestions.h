//ListOfQuestions maintains the data structure that holds Questions,
//for use throughout the application, as well as the DB connection
//that must interact with the data structure.

#ifndef LISTOFQUESTIONS_H
#define LISTOFQUESTIONS_H

#include <QLinkedList>
#include <QObject>

class Database;

class Question;

class ListOfQuestions : public QObject
{
    Q_OBJECT

public:
    ListOfQuestions(QObject *parent = 0);

    QLinkedList<Question*> list; //Linked list used for constant time removals. Possibly not worth it.

    void fillListFromDB(QString dbName);
    void dumpListToDB(QString dbName);
    Question* questionFromList(int index);
    void removeFromList(int index);
    void appendToList(Question* q);

    Database *db = nullptr;

private slots:
    void receiveNextSignal(QVariant *v);
    void receiveFINALSignal(QVariant *v);

signals:
    void passNextToEntry(QVariant*); //Pathway to pass an answer along.
    void passFINALToEntry(QVariant*);
};

#endif // LISTOFQUESTIONS_H
