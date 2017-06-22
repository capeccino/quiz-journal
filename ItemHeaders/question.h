//Question builds and controls the Question being created or entered.

#ifndef QUESTION_H
#define QUESTION_H

#include <QWidget>
#include <QStringList>

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

class ListOfQuestions;

class Question : public QWidget
{
    Q_OBJECT

signals:
    void cancelFromPreview(int stage);
    void submitFromPreview();
    void sendActiveUp(QVariant*);
    void sendActiveUpFINAL(QVariant*);

public slots:
    void passCancel();
    void passSubmit();
    void setActiveValue();
    void prepareToSend();
    void prepareToSendFINAL();

public:
    explicit Question(bool preview, ListOfQuestions *pList, QWidget *parent = 0);
    ~Question();

    int QID       = 0;
    int inputType = 0; //Radio Buttons = 0, Textbox = 1
    int dataType  = 0; //Numbers = 0, Words = 1

    //Index 0 always contains the main question text.
    //Any other indexes are additional texts for radio buttons.
    QStringList *strings = nullptr;

    void buildFrame();

    QVBoxLayout *vLayout = nullptr;

    QPushButton *nextButton   = nullptr;
    QPushButton *finishButton = nullptr;
    QPushButton *cancelButton = nullptr;

private:
    bool isPreview = false;

    QLabel *previewLabel = nullptr;
    QLabel *mainQuestion = nullptr;

    QPushButton *previewSubmit = nullptr;
    QPushButton *previewCancel = nullptr;

    QTextEdit *textBox = nullptr;
    QLineEdit *lineEdit = nullptr;

    QRadioButton *opt1 = nullptr;
    QRadioButton *opt2 = nullptr;
    QRadioButton *opt3 = nullptr;
    QRadioButton *opt4 = nullptr;
    QRadioButton *opt5 = nullptr;
    QRadioButton *opt6 = nullptr;

    QFrame *borderFrame = nullptr;

    QGroupBox *groupBox = nullptr;

    QHBoxLayout *hLayout = nullptr;
    QHBoxLayout *pButtonLayout = nullptr;

    QVBoxLayout *inFrameLayout = nullptr;

    QSpacerItem *spacer = nullptr;

    QVariant *activeValue = nullptr; //The Answer to be entered to the DB when submitted.

};

#endif // QUESTION_H
