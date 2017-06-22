#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "FormHeaders/journalframe.h"
#include "FormHeaders/creation.h"
#include "FormHeaders/entryframe.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FrameManager("INIT");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeToSmall()
{
    //Supposed to set application window to minimum size.
    //Not working correctly.

    QDesktopWidget desktop;

    QRect rec = desktop.availableGeometry(desktop.primaryScreen());
    int height = rec.height();
    int width = rec.width();

    //These positions should only be set like this on startup.
    //FIX THIS
    int hStart = (height / 2) - (SCR_HEIGHT / 2);
    int wStart = (width / 2) - (SCR_WIDTH / 2);

    setGeometry(wStart, hStart, SCR_WIDTH, SCR_HEIGHT);
}

void MainWindow::FrameManager(QString setup)
{
    if (setup == "New Journal From Main")
    {
        jFrame->deleteLater();
        cFrame = new Creation(this);
        resizeToSmall();
        cFrame->setGeometry(0, 0, this->width(), this->height());
        setCentralWidget(cFrame);
        return;
    }

    if (setup == "EntryMode")
    {
        eFrame = new EntryFrame(jFrame->getDBName(), this);
        resizeToSmall();
        eFrame->setGeometry(0, 0, this->width(), this->height());
        setCentralWidget(eFrame);
        jFrame->deleteLater();
        return;
    }

    if (setup == "INIT" || setup == "Main from QC" || setup == "Main from Entry")
    {
        if(setup == "Main from QC")
            cFrame->deleteLater();

        if(setup == "Main from Entry")
            eFrame->deleteLater();

        jFrame = new JournalFrame(this);
        resizeToSmall();
        jFrame->setGeometry(0, 0, this->width(), this->height());
        setCentralWidget(jFrame);
        jFrame->innerFrames(0);

        return;
    }
    else //If none of the above, 'setup' is the string to be used as new journal name.
    {
        jFrame = new JournalFrame(this);

        jFrame->receiveJournalFromAbove(setup); //passes name to the journal frame.

        resizeToSmall();
        jFrame->setGeometry(0, 0, this->width(), this->height());
        setCentralWidget(jFrame);
        jFrame->innerFrames(0);
        cFrame->deleteLater();
        return;
    }
}

void MainWindow::switchQC()
{
    FrameManager("New Journal From Main");
}

void MainWindow::switchMainQC()
{
    FrameManager("Main from QC");
}

void MainWindow::switchMainEnt()
{
    FrameManager("Main from Entry");
}

void MainWindow::switchEnt()
{
    FrameManager("EntryMode");
}
