//JournalFrame controls the application starting page.

#ifndef JOURNALFRAME_H
#define JOURNALFRAME_H

#include <QWidget>

class JournalModel;
class EntryModel;
class AnswerModel;

namespace Ui {
class JournalFrame;
}

class JournalFrame : public QWidget
{
    Q_OBJECT

public:
    explicit JournalFrame(QWidget *parent = 0);
    ~JournalFrame();

    QString getDBName();
    int getEntry();

private:
    Ui::JournalFrame *ui;
    JournalModel *jModel = nullptr;
    EntryModel *eModel = nullptr;
    AnswerModel *aModel = nullptr;

public slots:
    void innerFrames(int stage);
    void receiveJournalFromAbove(QString na); //Receive name from MainWindow, then submit to DB.

private slots:
    void on_journalQuitButton_clicked();
    void on_journalListView_clicked(const QModelIndex &index);
    void on_entryListView_clicked(const QModelIndex &index);
};

#endif // JOURNALFRAME_H
