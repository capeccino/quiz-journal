#include "ItemHeaders/question.h"

#include "ListHeaders/listofquestions.h"

#include <QDoubleValidator>
#include <QMessageBox>

Question::Question(bool Preview, ListOfQuestions *pList, QWidget *parent) :
    QWidget(parent), isPreview(Preview)
{
    strings = new QStringList();
    activeValue = new QVariant(NULL);

    connect(this, SIGNAL(sendActiveUp(QVariant*)), pList, SLOT(receiveNextSignal(QVariant*)));
    connect(this, SIGNAL(sendActiveUpFINAL(QVariant*)), pList, SLOT(receiveFINALSignal(QVariant*)));
}

Question::~Question(){}

void Question::passCancel()
{
    emit cancelFromPreview(5);
}

void Question::passSubmit()
{
    emit submitFromPreview();
}

void Question::buildFrame()
{
    vLayout = new QVBoxLayout(this);

    if(isPreview)
    {
        previewLabel = new QLabel("Preview", this);
        QFont font ("MS Shell Dlg 2", 14) ;
        font.setBold(true);
        font.setUnderline(true);
        previewLabel->setFont(font);

        vLayout->addWidget(previewLabel);
    }

    borderFrame = new QFrame(this);
    borderFrame->setFrameShape(QFrame::Box);
    borderFrame->setFrameShadow(QFrame::Raised);

    inFrameLayout = new QVBoxLayout;
    borderFrame->setLayout(inFrameLayout);
    vLayout->addWidget(borderFrame);

    mainQuestion = new QLabel(this);
    mainQuestion->setText(strings->at(0));
    mainQuestion->setMaximumHeight(21);
    inFrameLayout->addWidget(mainQuestion);

    if(inputType == 0)
    {
        groupBox = new QGroupBox(this);
        groupBox->setLayout(new QVBoxLayout);

        //Cascading creation of radio buttons.
        switch(strings->length() - 1)
        {
        case 6: opt6 = new QRadioButton(this);
                opt6->setText(strings->at(6));
                connect(opt6, SIGNAL(clicked()), this, SLOT(setActiveValue()));
        case 5: opt5 = new QRadioButton(this);
                opt5->setText(strings->at(5));
                connect(opt5, SIGNAL(clicked()), this, SLOT(setActiveValue()));
        case 4: opt4 = new QRadioButton(this);
                opt4->setText(strings->at(4));
                connect(opt4, SIGNAL(clicked()), this, SLOT(setActiveValue()));
        case 3: opt3 = new QRadioButton(this);
                opt3->setText(strings->at(3));
                connect(opt3, SIGNAL(clicked()), this, SLOT(setActiveValue()));
        case 2: opt2 = new QRadioButton(this);
                opt2->setText(strings->at(2));
                connect(opt2, SIGNAL(clicked()), this, SLOT(setActiveValue()));
                opt1 = new QRadioButton(this);
                opt1->setText(strings->at(1));
                connect(opt1, SIGNAL(clicked()), this, SLOT(setActiveValue()));
        }

        switch(strings->length() - 1)
        {
        case 2:
            groupBox->layout()->addWidget(opt1);
            groupBox->layout()->addWidget(opt2);
            break;
        case 3:
            groupBox->layout()->addWidget(opt1);
            groupBox->layout()->addWidget(opt2);
            groupBox->layout()->addWidget(opt3);
            break;
        case 4:
            groupBox->layout()->addWidget(opt1);
            groupBox->layout()->addWidget(opt2);
            groupBox->layout()->addWidget(opt3);
            groupBox->layout()->addWidget(opt4);
            break;
        case 5:
            groupBox->layout()->addWidget(opt1);
            groupBox->layout()->addWidget(opt2);
            groupBox->layout()->addWidget(opt3);
            groupBox->layout()->addWidget(opt4);
            groupBox->layout()->addWidget(opt5);
            break;
        case 6:
            groupBox->layout()->addWidget(opt1);
            groupBox->layout()->addWidget(opt2);
            groupBox->layout()->addWidget(opt3);
            groupBox->layout()->addWidget(opt4);
            groupBox->layout()->addWidget(opt5);
            groupBox->layout()->addWidget(opt6);
        }

        inFrameLayout->addWidget(groupBox);

    }
    else if (dataType == 0)
    {
        lineEdit = new QLineEdit(this);
        lineEdit->setMaxLength(9);
        QDoubleValidator *val = new QDoubleValidator(this); //ensures numeric value
        lineEdit->setValidator(val);
        inFrameLayout->addWidget(lineEdit);
    }
    else
    {
        textBox = new QTextEdit(this);
        inFrameLayout->addWidget(textBox);
    }

    finishButton = new QPushButton(this);
    finishButton->setText("Finish");
    finishButton->setEnabled(false);
    connect(finishButton, SIGNAL(clicked()), this, SLOT(prepareToSendFINAL()));

    nextButton = new QPushButton(this);
    nextButton->setText("Next");
    connect(nextButton, SIGNAL(clicked()), this, SLOT(prepareToSend()));

    cancelButton = new QPushButton(this);
    cancelButton->setText("Cancel");

    hLayout = new QHBoxLayout;
    hLayout->addWidget(nextButton);
    hLayout->addWidget(finishButton);
    hLayout->addWidget(cancelButton);

    inFrameLayout->addLayout(hLayout);

    if(isPreview)
    {
        connect(this, SIGNAL(cancelFromPreview(int)), parentWidget(), SLOT(innerFrames(int)));
        connect(this, SIGNAL(submitFromPreview()), parentWidget(), SLOT(addQuestionToList()));

        finishButton->setEnabled(false);
        nextButton->setEnabled(false);
        cancelButton->setEnabled(false);

        previewSubmit = new QPushButton("Submit", this);
        connect(previewSubmit, SIGNAL(clicked()), this, SLOT(passSubmit()));
        previewCancel = new QPushButton("Cancel", this);
        connect(previewCancel, SIGNAL(clicked()), this, SLOT(passCancel()));
        pButtonLayout = new QHBoxLayout;
        pButtonLayout->addWidget(previewSubmit);
        pButtonLayout->addWidget(previewCancel);

        vLayout->addLayout(pButtonLayout);

        spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        vLayout->addSpacerItem(spacer);

    }

    return;
}

void Question::setActiveValue()
{
    if(inputType == 0)
    {
        QObject *obj = sender();
        if(dataType == 0)
        {
            if(obj == opt1)
            {
                (*activeValue) = opt1->text().toDouble();
                return;
            }

            if(obj == opt2)
            {
                (*activeValue) = opt2->text().toDouble();
                return;
            }

            if(obj == opt3)
            {
                (*activeValue) = opt3->text().toDouble();
                return;
            }

            if(obj == opt4)
            {
                (*activeValue) = opt4->text().toDouble();
                return;
            }

            if(obj == opt5)
            {
                (*activeValue) = opt5->text().toDouble();
                return;
            }

            if(obj == opt6)
            {
                (*activeValue) = opt6->text().toDouble();
                return;
            }
        }
        else
        {
            if(obj == opt1)
            {
                (*activeValue) = opt1->text();
                return;
            }

            if(obj == opt2)
            {
                (*activeValue) = opt2->text();
                return;
            }

            if(obj == opt3)
            {
                (*activeValue) = opt3->text();
                return;
            }

            if(obj == opt4)
            {
                (*activeValue) = opt4->text();
                return;
            }

            if(obj == opt5)
            {
                (*activeValue) = opt5->text();
                return;
            }

            if(obj == opt6)
            {
                (*activeValue) = opt6->text();
                return;
            }
        }
    }
    else if(dataType == 0)
    {
        (*activeValue) = lineEdit->text().toDouble();
    }
    else
    {
        (*activeValue) = textBox->toPlainText();
    }
}

void Question::prepareToSend()
{

    if(inputType == 1)
    {
        setActiveValue();
    }

    if((*activeValue) == NULL)
    {
        QMessageBox::warning(this, tr("Incomplete Question"), tr("Must Enter An Answer."), QMessageBox::Ok );
        return;
    }

    emit sendActiveUp(activeValue);
}

void Question::prepareToSendFINAL()
{

    if(inputType == 1)
    {
        setActiveValue();
    }

    if((*activeValue) == NULL)
    {
        QMessageBox::warning(this, tr("Incomplete Question"), tr("Must Enter An Answer."), QMessageBox::Ok );
        return;
    }

    emit sendActiveUpFINAL(activeValue);
}
