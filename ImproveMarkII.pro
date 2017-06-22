#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T10:52:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImproveMarkII
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    FormSource/journalframe.cpp \
    FormSource/creation.cpp \
    FormSource/qcrb_detailed.cpp \
    FormSource/entryframe.cpp \
    database.cpp \
    ModelSource/answermodel.cpp \
    ModelSource/entrymodel.cpp \
    ModelSource/journalmodel.cpp \
    ModelSource/linkedmodel.cpp \
    ListSource/listofanswers.cpp \
    ListSource/listofentries.cpp \
    ListSource/listofjournals.cpp \
    ListSource/listofquestions.cpp \
    ItemSource/question.cpp

HEADERS  += mainwindow.h \
    FormHeaders/journalframe.h \
    FormHeaders/creation.h \
    FormHeaders/qcrb_detailed.h \
    FormHeaders/entryframe.h \
    database.h \
    ModelHeaders/answermodel.h \
    ModelHeaders/entrymodel.h \
    ModelHeaders/journalmodel.h \
    ModelHeaders/linkedmodel.h \
    ListHeaders/listofanswers.h \
    ListHeaders/listofentries.h \
    ListHeaders/listofjournals.h \
    ListHeaders/listofquestions.h \
    ItemHeaders/question.h \
    ItemHeaders/journal.h \
    ItemHeaders/entry.h \
    ItemHeaders/answer.h

FORMS    += mainwindow.ui \
    journalframe.ui \
    creation.ui \
    qcrb_detailed.ui \
    entryframe.ui

DISTFILES += \
    FormHeaders/holder.txt
