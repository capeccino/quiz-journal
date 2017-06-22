/* Creation controls the process of creating Questions.
 * When finished, the collection of Questions becomes a Journal.
 */

#ifndef CREATION_H
#define CREATION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

class QCRB_Detailed;
class LinkedModel;
class Question;

namespace Ui {
class Creation;
}

class Creation : public QWidget
{
    Q_OBJECT

public:
    explicit Creation(QWidget *parent = 0);
    ~Creation();

private slots:
    //UI controls
    void on_questionAddButton_clicked();
    void on_questionRemoveButton_clicked();
    void on_questionEditButton_clicked();
    void on_jNameEnterButton_clicked();
    void on_jNameEditButton_clicked();
    void on_qcCancelButton_clicked();
    void on_qcContinueButton_clicked();
    void on_questionFinishButton_clicked();

public slots:
    void innerFrames(int stage); //Controls which widgets are showing, and what is enabled.
    void addString(QString str); //Adds additional question text in the case of radio buttons.
    void buildPreview();         //Constructs a preview by calling buildFrame in Question class.
    void addQuestionToList();    //Submits Question to the overall list of Questions.

signals:
    void passAndSwitch(QString); //Passes Journal name to MainWindow to be passed to Journal Frame for entry into the DB.
    void makeSmall();//Not Working.

private:
    Ui::Creation *ui;
    QCRB_Detailed *radioFrame = nullptr;
    LinkedModel *linked = nullptr;
    Question *quest = nullptr;

    QLabel *jNameDisplayLabel = nullptr;
    QFrame *questionPreviewFrame = nullptr;

};

#endif // CREATION_H
