//Database class controls all access to the SQLite Databases.

#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Question;
class ListOfQuestions;
struct journal;
struct entry;
struct answer;

class Database
{

public:
    Database(QString cName, ListOfQuestions *pList = 0);
    ~Database();

    void connectDB(QString dbName);  //Also creates the DB if it doesn't exist.

    bool createTables(QString type); //If the tables already exist, it does nothing.

    bool insertJournal(QString name, QString date);
    bool insertQuestion(Question* q);
    bool insertEntry(QString date);
    bool insertAnswer(answer* a);

    bool fillJournalStructure(QList<journal*> &journ);
    bool fillEntryStructure(QList<entry*> &ent);
    bool fillQuestionStructure(QLinkedList<Question*> &quest);
    bool fillAnswerStructureFromEID(int id, QList<answer*> &ans);

    int getEID();
    bool updateEID();

    QString getQuestionFromQID(int qid);

    QString dbName;

private:
    QSqlDatabase db;
    QString connectionName;
    QString fileName;

    ListOfQuestions *pLoQ; //Parent list is needed to pass a Question signal to a List slot.
                           //This is because Questions are dynamically generated in this class with no parent otherwise.
};

#endif // DATABASE_H
