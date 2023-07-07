/********************************************************************************
** Form generated from reading UI file 'FiveInARow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIVEINAROW_H
#define UI_FIVEINAROW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FiveInARow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FiveInARow)
    {
        if (FiveInARow->objectName().isEmpty())
            FiveInARow->setObjectName("FiveInARow");
        FiveInARow->resize(800, 600);
        centralwidget = new QWidget(FiveInARow);
        centralwidget->setObjectName("centralwidget");
        FiveInARow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FiveInARow);
        menubar->setObjectName("menubar");
        FiveInARow->setMenuBar(menubar);
        statusbar = new QStatusBar(FiveInARow);
        statusbar->setObjectName("statusbar");
        FiveInARow->setStatusBar(statusbar);

        retranslateUi(FiveInARow);

        QMetaObject::connectSlotsByName(FiveInARow);
    } // setupUi

    void retranslateUi(QMainWindow *FiveInARow)
    {
        FiveInARow->setWindowTitle(QCoreApplication::translate("FiveInARow", "FiveInARow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FiveInARow: public Ui_FiveInARow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIVEINAROW_H
