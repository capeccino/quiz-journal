#include "FormHeaders/entryframe.h"
#include "ui_entryframe.h"

#include "ItemHeaders/question.h"
#include "ItemHeaders/entry.h"
#include "ItemHeaders/answer.h"

#include "ListHeaders/listofquestions.h"
#include "ListHeaders/listofanswers.h"

#include "ModelHeaders/answermodel.h"

EntryFrame::EntryFrame(QString dbName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryFrame)
{
    ui->setupUi(this);

    listOfQ = new ListOfQuestions(this);
    listOfQ->fillListFromDB(dbName);

    aModel = new AnswerModel(listOfQ->db->getEID(), dbName, this);
    ui->entryAnswersTable->setModel(aModel);

    connect(ui->entryCancelAllButton, SIGNAL(clicked()), parentWidget(), SLOT(switchMainEnt()));

    innerFrames(0);
}

EntryFrame::~EntryFrame()
{
    delete ui;
}

void EntryFrame::innerFrames(int stage)
{
    switch(stage)
    {
        case 0: //Initialize with first Question.
            ui->submitButton->hide();
            ans = new answer;
            listOfQ->list.first()->buildFrame();
            entryQuestionFrame = new QFrame(this);
            entryQuestionFrame->setLayout(listOfQ->list.first()->vLayout);
            ui->verticalLayout_2->insertWidget(1, entryQuestionFrame);
            return;

        case 1: //Proceed to next Question
            ans = new answer;
            ui->verticalLayout_2->removeWidget(entryQuestionFrame);
            delete entryQuestionFrame;
            if(listOfQ->list.size() > 1)
            {
                listOfQ->list.pop_front();
                listOfQ->list.first()->buildFrame();
                entryQuestionFrame = new QFrame(this);
                entryQuestionFrame->setLayout(listOfQ->list.first()->vLayout);
                ui->verticalLayout_2->insertWidget(1, entryQuestionFrame);
                if(listOfQ->list.size() == 1)
                {
                    listOfQ->list.first()->nextButton->setEnabled(false);
                    listOfQ->list.first()->finishButton->setEnabled(true);
                }
            }
            return;

        case 2: //Answer to Final Question has been entered.
            entryQuestionFrame->setEnabled(false);
            ui->submitButton->show();
            return;
    }

    return;
}

void EntryFrame::receiveFromList(QVariant *v)
{
    //Get answer (*v) from Question List signal.

    ans->eid = listOfQ->db->getEID();
    ans->qid = listOfQ->list.first()->QID;
    ans->qAnswer = v->toString();

    addAnswertoList();

    ans = nullptr;

    innerFrames(1);

}

void EntryFrame::receiveFINALFromList(QVariant *v)
{
    ans->eid = listOfQ->db->getEID();
    ans->qid = listOfQ->list.first()->QID;
    ans->qAnswer = v->toString();

    addAnswertoList();

    ans = nullptr;

    innerFrames(2);
}

void EntryFrame::addAnswertoList()
{
    //Put answer into Answer List.

    QModelIndex index = ui->entryAnswersTable->currentIndex();
    aModel->insertRows(index.row()+1, 1, QModelIndex());
    QModelIndex modX = aModel->index(index.row() + 1, 0);

    QVariant v = qVariantFromValue((void *)ans);
    aModel->setData(modX, v, Qt::EditRole);
}


void EntryFrame::on_submitButton_clicked()
{
    //Submit Answers to the appropriate DB.
    //Add the timestamped Entry to the DB.

    aModel->listOfA->dumpListToDB(listOfQ->db->dbName);
    QString date = QDateTime::currentDateTime().toString("ddd MMM d, yyyy h:mmap");
    listOfQ->db->insertEntry(date);

    ui->entryCancelAllButton->click();
}
