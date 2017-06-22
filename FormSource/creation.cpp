#include "FormHeaders/creation.h"
#include "ui_creation.h"

#include "FormHeaders/qcrb_detailed.h"
#include "ItemHeaders/question.h"
#include "ModelHeaders/linkedmodel.h"
#include "ListHeaders/listofquestions.h"

#include <QFont>
#include <QMessageBox>

Creation::Creation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Creation)
{
    ui->setupUi(this);

    linked = new LinkedModel(this);
    ui->questionListView->setModel(linked);

    connect(ui->questionCancelButton, SIGNAL(clicked()), parentWidget(), SLOT(switchMainQC()));
    connect(this, SIGNAL(passAndSwitch(QString)), parentWidget(), SLOT(FrameManager(QString)));
    //connect(this, SIGNAL(makeSmall()), parentWidget(), SLOT(resizeToSmall())); //Not working

    innerFrames(0);
}

Creation::~Creation()
{
    delete ui;
}

void Creation::innerFrames(int stage)
{
    switch(stage)
    {
        case 0: //Initial
            ui->questionCreationFrame->hide();
            ui->questionListFrame->setEnabled(false);
            return;

        case 1: //Add question clicked
            ui->questionListFrame->setEnabled(false);
            ui->questionCreationFrame->show();
            return;

        case 2: //Text input chosen. Show preview.
            ui->questionCreationFrame->setEnabled(false);
            quest->buildFrame();
            questionPreviewFrame->setLayout(quest->vLayout);
            ui->creationMainLayout->addWidget(questionPreviewFrame);
            return;

        case 3://Radio input chosen. Show radio detailed entry.
            ui->questionCreationFrame->setEnabled(false);
            if(ui->qcRBNumbers->isChecked())
                radioFrame = new QCRB_Detailed(true, this);
            else
                radioFrame = new QCRB_Detailed(false, this);
            ui->questionDetailedFrame->layout()->addWidget(radioFrame);
            return;

        case 4: //Finished with radio detailed. Show preview.
            ui->questionDetailedFrame->setEnabled(false);
            quest->buildFrame();
            questionPreviewFrame->setLayout(quest->vLayout);
            ui->creationMainLayout->addWidget(questionPreviewFrame);
            return;

        case 5: //Reset Question Frame, but keep data structure so far.
            delete questionPreviewFrame;
            quest = nullptr;
            if(radioFrame != nullptr)
            {
                delete radioFrame;
                radioFrame = nullptr;
            }
            ui->questionCreationFrame->hide();
            ui->questionCreationFrame->setEnabled(true);
            ui->questionDetailedFrame->setEnabled(true);
            ui->qcMainTextbox->clear();

            ui->qcRBNumbers->setAutoExclusive(false);
            ui->qcRBWords->setAutoExclusive(false);
            ui->qcRBRadioButtons->setAutoExclusive(false);
            ui->qcRBTextbox->setAutoExclusive(false);

            ui->qcRBNumbers->setChecked(false);
            ui->qcRBWords->setChecked(false);
            ui->qcRBRadioButtons->setChecked(false);
            ui->qcRBTextbox->setChecked(false);

            ui->qcRBNumbers->setAutoExclusive(true);
            ui->qcRBWords->setAutoExclusive(true);
            ui->qcRBRadioButtons->setAutoExclusive(true);
            ui->qcRBTextbox->setAutoExclusive(true);

            ui->questionListFrame->setEnabled(true);
    }

    return;
}

void Creation::on_questionAddButton_clicked()
{
    quest = new Question(true, linked->listofQ, this);
    questionPreviewFrame = new QFrame(this);
    innerFrames(1);
}

void Creation::on_questionRemoveButton_clicked()
{
    // Remove Question from Linked List.
    QModelIndex index = ui->questionListView->currentIndex();

    if(index.row() >= 0)
    {
        linked->removeRows(index.row(), 1, QModelIndex());
        linked->removeData(index);
    }
}

void Creation::on_questionEditButton_clicked()
{
    //Implement in future.
}

void Creation::on_jNameEnterButton_clicked()
{
    //Sets the Journal Name.
    if(ui->jNameLineEdit->text().length() > 0)
    {
        jNameDisplayLabel = new QLabel(this);
        jNameDisplayLabel->setFont(QFont("MS Shell Dlg 2", 12, 1));
        jNameDisplayLabel->setText(ui->jNameLineEdit->text());

        ui->jNameEnterButton->hide();
        ui->jNameLineEdit->hide();
        ui->jNameLayout->removeWidget(ui->jNameLineEdit);
        ui->jNameLayout->removeWidget(ui->jNameEnterButton);

        ui->jNameLayout->addWidget(jNameDisplayLabel);

        ui->questionListFrame->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, tr("Incomplete"), tr("Must enter a name."), QMessageBox::Ok );
        return;
    }
}

void Creation::on_jNameEditButton_clicked()
{
    //Allows editing the Journal Name
    ui->questionListFrame->setEnabled(false);

    jNameDisplayLabel->hide();
    ui->jNameLayout->removeWidget(jNameDisplayLabel);

    ui->jNameLayout->addWidget(ui->jNameLineEdit);
    ui->jNameLayout->addWidget(ui->jNameEnterButton);

    ui->jNameEnterButton->show();
    ui->jNameLineEdit->show();

}

void Creation::on_qcCancelButton_clicked()
{
    innerFrames(5);
    //emit makeSmall();
}

void Creation::on_qcContinueButton_clicked()
{
    //Verifies that all Question options and texts are in place.
    //Then proceeds to the preview by calling the appropriate innerFrames.

    if(ui->qcMainTextbox->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, tr("Incomplete Form"), tr("Must write a Question."), QMessageBox::Ok );
        return;
    }

    if(! (ui->qcRBRadioButtons->isChecked() ||
          ui->qcRBTextbox->isChecked() ) )
    {
        QMessageBox::warning(this, tr("Incomplete Form"), tr("Must select an Input Widget."), QMessageBox::Ok );
        return;
    }

    if(! (ui->qcRBNumbers->isChecked() |
          ui->qcRBWords->isChecked() ) )
    {
        QMessageBox::warning(this, tr("Incomplete Form"), tr("Must select a Data Type."), QMessageBox::Ok );
        return;
    }

    quest->strings->append(ui->qcMainTextbox->toPlainText());

    if(ui->qcRBNumbers->isChecked())
        quest->dataType = 0;
    else
        quest->dataType = 1;

    if(ui->qcRBRadioButtons->isChecked())
    {
        quest->inputType = 0;
        innerFrames(3);
    }
    else
    {
        quest->inputType = 1;
        innerFrames(2);
    }

    return;
}

void Creation::addString(QString str)
{
    quest->strings->append(str);
}

void Creation::buildPreview()
{
    innerFrames(4);
}

void Creation::addQuestionToList()
{
    // Add Question to Linked List

    QModelIndex index = ui->questionListView->currentIndex();
    linked->insertRows(index.row()+1, 1, QModelIndex());
    QModelIndex modX = linked->index(index.row()+1);

    QVariant v = qVariantFromValue((void *)quest);
    linked->setData(modX, v, Qt::EditRole);

    innerFrames(5);

}

void Creation::on_questionFinishButton_clicked()
{
    //If there are no Questions, it is an error.
    //Otherwise, submit the list of Questions to the DB,
    //and pass up the Journal Name to MainWindow.

    if(linked->listofQ->list.size() < 1)
    {
        QMessageBox::warning(this, tr("Empty List"), tr("No Questions in List. Journal Not Created."), QMessageBox::Ok );
        ui->questionCancelButton->click();
        return;
    }

    linked->listofQ->dumpListToDB(jNameDisplayLabel->text());
    emit passAndSwitch(jNameDisplayLabel->text());
}
