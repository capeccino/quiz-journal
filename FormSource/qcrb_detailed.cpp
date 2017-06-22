#include "FormHeaders/creation.h"
#include "FormHeaders/qcrb_detailed.h"
#include "ui_qcrb_detailed.h"

#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>


QCRB_Detailed::QCRB_Detailed(bool numeric, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCRB_Detailed), isNumeric(numeric)
{
    ui->setupUi(this);

    connect(this, SIGNAL(callAddString(QString)), parentWidget(), SLOT(addString(QString)));
    connect(this, SIGNAL(callBuildPreview()), parentWidget(), SLOT(buildPreview()));
    connect(this, SIGNAL(cancelRadio(int)), parentWidget(), SLOT(innerFrames(int)));

    currentButton = 1;
    setButtonLabel();

    ui->radioFinishButton->setEnabled(false);

    if(isNumeric)
    {
        QDoubleValidator *val = new QDoubleValidator(this); //ensures a numeric value
        ui->radioLineEdit->setValidator(val);
    }
}

QCRB_Detailed::~QCRB_Detailed()
{
    delete ui;
}

void QCRB_Detailed::on_radioNextButton_clicked()
{
    if(ui->radioLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Incomplete"), tr("Must enter text."), QMessageBox::Ok );
        return;
    }

    emit callAddString(ui->radioLineEdit->text());
    clearForNext();
}

void QCRB_Detailed::on_radioFinishButton_clicked()
{
    if(ui->radioLineEdit->text().isEmpty())
    {
        if(currentButton <= 2)
        {
            QMessageBox::warning(this, tr("Incomplete"), tr("Must enter text for at least 2 options."), QMessageBox::Ok );
            return;
        }
        emit callBuildPreview();
    }
    else
    {
        emit callAddString(ui->radioLineEdit->text());
        emit callBuildPreview();
    }
}

void QCRB_Detailed::on_radioCancelButton_clicked()
{
    emit cancelRadio(5); //calls Creation innerFrames(5)
}

void QCRB_Detailed::setButtonLabel()
{
    ui->radioCurrentButton->setText("Current Button: " + QString::number(currentButton));
}

void QCRB_Detailed::clearForNext()
{
    currentButton++;
    setButtonLabel();

    ui->radioLineEdit->clear();
    ui->radioLineEdit->setFocus();

    if(currentButton >= 2)
        ui->radioFinishButton->setEnabled(true);

    if(currentButton >= 6)
        ui->radioNextButton->setEnabled(false);
}
