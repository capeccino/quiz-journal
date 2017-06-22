//EntryFrame controls the process of entering Answers to Questions.

#ifndef ENTRYFRAME_H
#define ENTRYFRAME_H

#include <QWidget>
#include <QFrame>

class Question;
class ListOfQuestions;
class AnswerModel;
struct answer;

namespace Ui {
class EntryFrame;
}

class EntryFrame : public QWidget
{
    Q_OBJECT

public:
    explicit EntryFrame(QString dbName, QWidget *parent = 0);
    ~EntryFrame();

private:
    Ui::EntryFrame *ui;
    Question *quest = nullptr;
    ListOfQuestions *listOfQ = nullptr;
    AnswerModel *aModel = nullptr;
    answer *ans = nullptr;
    int workingEID = 0;

    QFrame *entryQuestionFrame = nullptr;

public slots:
    void addAnswertoList();

private slots:
    void innerFrames(int stage);
    void receiveFromList(QVariant *v);
    void receiveFINALFromList(QVariant *v);
    void on_submitButton_clicked();
};

#endif // ENTRYFRAME_H
