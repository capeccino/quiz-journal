//Question Creation Radio Button Detailed (QCRB_Detailed)
//Creates and controls the frame used to enter detailed
//text for radio buttons.

#ifndef QCRB_DETAILED_H
#define QCRB_DETAILED_H

#include <QWidget>

namespace Ui {
class QCRB_Detailed;
}

class QCRB_Detailed : public QWidget
{
    Q_OBJECT

public:
    explicit QCRB_Detailed(bool numeric, QWidget *parent = 0);
    ~QCRB_Detailed();

signals:
    void callAddString(QString); //Passes value to Creation's addString method.
    void callBuildPreview();     //Passes control signal to create the Preview frame.
    void cancelRadio(int);       //Cancels the process of creating a radio button Question.

private slots:
    void on_radioNextButton_clicked();
    void on_radioFinishButton_clicked();
    void on_radioCancelButton_clicked();
    void setButtonLabel();
    void clearForNext();

private:
    Ui::QCRB_Detailed *ui;
    int currentButton = 0;
    bool isNumeric = false;
};

#endif // QCRB_DETAILED_H
