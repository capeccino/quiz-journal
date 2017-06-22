#include "mainwindow.h"
#include <QApplication>
#include <QtSql>

//These statements add potential pathways to access the SQLite databases.
//There needs to be a different connection for each new object that
//wants to interact with a DB.
QSqlDatabase jdb = QSqlDatabase::addDatabase("QSQLITE", "journals");
QSqlDatabase qdb = QSqlDatabase::addDatabase("QSQLITE", "questions");
QSqlDatabase edb = QSqlDatabase::addDatabase("QSQLITE", "entries");
QSqlDatabase adb = QSqlDatabase::addDatabase("QSQLITE", "answers");
QSqlDatabase x1db = QSqlDatabase::addDatabase("QSQLITE", "extra1");
QSqlDatabase x2db = QSqlDatabase::addDatabase("QSQLITE", "extra2");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.resizeToSmall();
    w.setWindowTitle("Improve: Quiz Journal");
    w.show();

    return a.exec();
}
