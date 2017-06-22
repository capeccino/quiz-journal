//The main application window that all other Frames exist within.
//Needs work to fix window sizing and positioning problems.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class JournalFrame;
class Creation;
class EntryFrame;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    JournalFrame *jFrame;
    Creation *cFrame;
    EntryFrame *eFrame;

    const int SCR_WIDTH = 350;
    const int SCR_HEIGHT = 400;

public slots:
    void resizeToSmall();

private slots:
    void switchQC();
    void switchMainQC();
    void switchMainEnt();
    void switchEnt();

    void FrameManager(QString setup);
};

#endif // MAINWINDOW_H
