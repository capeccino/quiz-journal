#include "database.h"
#include "ItemHeaders/question.h"
#include "ItemHeaders/journal.h"
#include "ItemHeaders/entry.h"
#include "ItemHeaders/answer.h"
#include "ListHeaders/listofquestions.h"

#include <QDebug>

Database::Database(QString cName, ListOfQuestions *pList)
{
    connectionName = cName;
    pLoQ = pList;
}

Database::~Database(){}

void Database::connectDB(QString databaseName)
{
    dbName = databaseName;
    fileName = "DBs/" + dbName + ".db";
    qDebug().noquote() << fileName;
    db = QSqlDatabase::database(connectionName);
    db.setDatabaseName(fileName);
}

bool Database::createTables(QString type)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    if (type == "JournalsDB")
    {
        db.open();

        qry.exec("create table if not exists JOURNALS ("
                 "name text unique,"
                 "date text,"
                 "nextEID integer);");

        db.close();
        return true;
    }

    if (type == "SpecificJournal")
    {
        db.open();


        qry.exec("create table if not exists QUESTIONS ("
                 "qid integer primary key,"
                 "questionText text,"
                 "inputType integer,"
                 "dataType integer,"
                 "additionalStrings text,"
                 "numAdditionals integer);");


        qry.exec("create table if not exists ENTRIES ("
                 "eid integer unique,"
                 "date text);");

        qry.exec("create table if not exists ANSWERS ("
                 "answer text,"
                 "qid integer,"
                 "eid integer);");

        db.close();
        return true;
    }

    return false;
}

//_______QUESTIONS________________________________________________________________________________________________

QString Database::getQuestionFromQID(int qid)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    db.open();

    QString sQry = "select questionText from QUESTIONS where qid=" + QString::number(qid) + ";";

    qry.exec(sQry);

    qry.first();
    QString mainQ = qry.value(0).toString();

    db.close();
    return mainQ;
}

bool Database::insertQuestion(Question *q)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    int numberAdditonals = q->strings->size() > 1 ? ( q->strings->size() - 1 ) : 0;
    QString additionals;

    if(numberAdditonals > 0) //if so, there is more than just the main question in the string list.
    {
        additionals = q->strings->at(1);

        for(int i = 2; i <= numberAdditonals; i++)
        {
            additionals += "\n" + q->strings->at(i);
        }
    }
    else
    {
        additionals = "~";
    }

    db.open();
    QString sQry;

    sQry = "insert into QUESTIONS (questionText, inputType, dataType, additionalStrings, numAdditionals)"
           "values (:qText, :iType, :dType, :addStrs, :numAdds);";

    qry.prepare(sQry);
    qry.bindValue(":qText", q->strings->at(0));
    qry.bindValue(":iType", q->inputType);
    qry.bindValue(":dType", q->dataType);
    qry.bindValue(":addStrs", additionals);
    qry.bindValue(":numAdds", numberAdditonals);

    if(qry.exec())
    {
        db.close();
        return true;
    }

    db.close();
    return false;
}

bool Database::fillQuestionStructure(QLinkedList<Question*> &quest)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    db.open();

    if( qry.exec("select qid, questionText, inputType, dataType, numAdditionals, additionalStrings from QUESTIONS;") )
    {
        int numAdds = 0;
        QStringList splitAdds;

        while(qry.next())
        {
            Question *temp = new Question(false, pLoQ);

            temp->QID = qry.value(0).toInt();
            temp->strings->append( qry.value(1).toString() );
            temp->inputType = qry.value(2).toInt();
            temp->dataType = qry.value(3).toInt();
            numAdds = qry.value(4).toInt();
            if (numAdds > 0)
            {
                splitAdds = qry.value(5).toString().split("\n");
                for(int i = 0; i < numAdds; i++)
                {
                    temp->strings->append(splitAdds.at(i));
                }
            }

            quest.append(temp);
        }

        db.close();
        return true;
    }

    db.close();
    return false;
}

//_____________JOURNALS__________________________________________________________________________________________

bool Database::insertJournal(QString name, QString date)
{

    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    db.open();
    QString sQry = "insert into JOURNALS (name, date, nextEID) values (:na, :da, :eid);";

    date = date.trimmed();

    qry.prepare(sQry);
    qry.bindValue(":na", name);
    qry.bindValue(":da", date);
    qry.bindValue(":eid", 1);

    if(qry.exec())
    {
        db.close();
        return true;
    }

    db.close();
    return false;
}

bool Database::fillJournalStructure(QList<journal*> &journ)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    db.open();

    if( qry.exec("select name, date from JOURNALS;") )
    {
        int count = 0;
        QString dStr;
        QDateTime dateFromStr;

        while(qry.next())
        {
            journal* temp = new journal;
            temp->name = qry.value(0).toString();
            dStr = qry.value(1).toString();
            dStr = dStr.trimmed();

            dateFromStr = dateFromStr.fromString(dStr, "ddd MMM d, yyyy h:mmap");
            temp->date = dateFromStr;

            journ.append(temp);

            count++;
        }

        db.close();
        return true;
    }

    db.close();
    return false;
}

//______________ENTRIES_________________________________________________________________________________________

int Database::getEID()
{

    QSqlDatabase iqjDB = QSqlDatabase::database("extra1");
    iqjDB.setDatabaseName("DBs/IQJ_DB.db");

    QSqlQuery jQry(iqjDB);

    iqjDB.open();

    QString sQry = "select nextEID from JOURNALS where name=\"" + dbName + "\";";

    jQry.exec(sQry);

    jQry.first();
    int EID = jQry.value(0).toInt();

    iqjDB.close();
    return EID;
}

bool Database::updateEID()
{

    QSqlDatabase iqjDB = QSqlDatabase::database("extra2");
    iqjDB.setDatabaseName("DBs/IQJ_DB.db");

    QSqlQuery jQry(iqjDB);

    iqjDB.open();

    int next = getEID() + 1;
    QString sQry = "update JOURNALS set nextEID = " + QString::number(next) + " where name=\"" + dbName + "\";";

    jQry.exec(sQry);

    iqjDB.close();
    return true;
}

bool Database::insertEntry(QString date)
{

    db = QSqlDatabase::database(connectionName);

    QSqlQuery qry(db);

    db.open();

    QString sQry = "insert into ENTRIES (eid, date) values (:id, :da);";
    date = date.trimmed();
    int idToUse = getEID();

    qry.prepare(sQry);
    qry.bindValue(":da", date);
    qry.bindValue(":id", idToUse);

    updateEID();

    if( qry.exec() )
    {
        db.close();
        return true;
    }

    db.close();
    return false;
}

bool Database::fillEntryStructure(QList<entry*> &ent)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    db.open();

    if( qry.exec("select eid, date from ENTRIES;") )
    {
        QString dStr;
        QDateTime dateFromStr;

        while(qry.next())
        {
            entry* temp = new entry;
            temp->EID = qry.value(0).toInt();
            dStr = qry.value(1).toString();
            dStr = dStr.trimmed();

            dateFromStr = dateFromStr.fromString(dStr, "ddd MMM d, yyyy h:mmap");
            temp->date = dateFromStr;
            ent.append(temp);

        }

        db.close();
        return true;
    }

    db.close();
    return false;
}

//___________ANSWERS____________________________________________________________________________________________

bool Database::insertAnswer(answer *a)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    db.open();
    QString sQry = "insert into ANSWERS (eid, qid, answer) values (:e, :q, :a);";

    qry.prepare(sQry);
    qry.bindValue(":e", a->eid);
    qry.bindValue(":q", a->qid);
    qry.bindValue(":a", a->qAnswer);

    if(qry.exec())
    {
        db.close();
        return true;
    }

    db.close();
    return false;
}

bool Database::fillAnswerStructureFromEID(int id, QList<answer *> &ans)
{
    db = QSqlDatabase::database(connectionName);
    QSqlQuery qry(db);

    db.open();

    QString sQry = "select eid, qid, answer from ANSWERS where eid=(:id);";
    qry.prepare(sQry);
    qry.bindValue(":id", id);

    qry.first();
    if( qry.exec() )
    {
        while(qry.next())
        {
            answer* temp = new answer;
            temp->eid = qry.value(0).toInt();
            temp->qid = qry.value(1).toInt();
            temp->qAnswer = qry.value(2).toString();

            ans.append(temp);
        }
        db.close();
        return true;
    }

    db.close();
    return false;
}
