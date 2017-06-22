#include "FormHeaders/journalframe.h"
#include "ui_journalframe.h"

#include "ItemHeaders/journal.h"
#include "ItemHeaders/entry.h"

#include "ListHeaders/listofjournals.h"
#include "ListHeaders/listofentries.h"

#include "ModelHeaders/journalmodel.h"
#include "ModelHeaders/entrymodel.h"
#include "ModelHeaders/answermodel.h"

JournalFrame::JournalFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JournalFrame)
{
    ui->setupUi(this);

    jModel = new JournalModel(this);
    ui->journalListView->setModel(jModel);

    connect(ui->journalAddButton, SIGNAL(clicked()), parentWidget(), SLOT(switchQC()));
    connect(ui->entryAddButton, SIGNAL(clicked()), parentWidget(), SLOT(switchEnt()));
}

JournalFrame::~JournalFrame()
{
    delete ui;
}

QString JournalFrame::getDBName()
{
    //Returns the DB name of the current selection.
    //Allows all changes to affect the correct DBs.

    QModelIndex jInd = ui->journalListView->currentIndex();
    QString journalName = jModel->listOfJ->list[jInd.row()]->name;
    journalName = journalName.trimmed();

    return journalName;
}

int JournalFrame::getEntry()
{
    //Returns the number of the next Entry.
    //Allows Answers to be associated with the correct Entry.

    QModelIndex jInd = ui->entryListView->currentIndex();
    int eid = eModel->listOfE->list[jInd.row()]->EID;

    return eid;
}

void JournalFrame::innerFrames(int stage)
{
    switch(stage)
    {
        case 0: //Initialize Window.
            ui->entryListFrame->hide();
            ui->answerTableFrame->hide();
            return;
        case 1: //Show Entries for currently selected Journal.
            ui->answerTableFrame->hide();
            if(eModel != nullptr)
            {
                delete eModel;
                eModel = nullptr;
            }
            eModel = new EntryModel(getDBName(), this);
            ui->entryListFrame->show();
            ui->entryListView->setModel(eModel);
            return;
        case 2: //Show Answers for currently selected Entry.
            if(aModel != nullptr)
            {
                delete aModel;
                aModel = nullptr;
            }
            aModel = new AnswerModel(getEntry(), getDBName(), this);
            aModel->initialFill();
            ui->answerTableFrame->show();
            ui->answerTableView->setModel(aModel);
            return;
    }
}

void JournalFrame::receiveJournalFromAbove(QString na)
{
    //Receives the name of a newly created Journal from MainWindow,
    //that is passed up from Question Creation.
    //Adds the Journal to the application's main DB, IQJ_DB.db.

    journal *toAdd = new journal;
    toAdd->name = na.trimmed();
    QDateTime dt = QDateTime::currentDateTime();
    toAdd->date = dt;

    jModel->listOfJ->insertIntoDB(toAdd);

    QModelIndex index = ui->journalListView->currentIndex();
    jModel->insertRows(index.row()+1, 1, QModelIndex());
    QModelIndex modX = jModel->index(index.row()+1);

    QVariant v = qVariantFromValue((void *)toAdd);
    jModel->setData(modX, v, Qt::EditRole);
}


void JournalFrame::on_journalQuitButton_clicked()
{
    QApplication::quit();
}

void JournalFrame::on_journalListView_clicked(const QModelIndex &index)
{
    index; //To stop the compiler from complaining about unused parameters.
    innerFrames(1);
}

void JournalFrame::on_entryListView_clicked(const QModelIndex &index)
{
    index; //To stop the compiler from complaining about unused parameters.
    innerFrames(2);
}
