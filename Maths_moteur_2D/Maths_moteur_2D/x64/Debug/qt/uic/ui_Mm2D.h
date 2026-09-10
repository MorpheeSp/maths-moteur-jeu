/********************************************************************************
** Form generated from reading UI file 'Mm2D.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MM2D_H
#define UI_MM2D_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mm2DClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Mm2DClass)
    {
        if (Mm2DClass->objectName().isEmpty())
            Mm2DClass->setObjectName("Mm2DClass");
        Mm2DClass->resize(600, 400);
        menuBar = new QMenuBar(Mm2DClass);
        menuBar->setObjectName("menuBar");
        Mm2DClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Mm2DClass);
        mainToolBar->setObjectName("mainToolBar");
        Mm2DClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Mm2DClass);
        centralWidget->setObjectName("centralWidget");
        Mm2DClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Mm2DClass);
        statusBar->setObjectName("statusBar");
        Mm2DClass->setStatusBar(statusBar);

        retranslateUi(Mm2DClass);

        QMetaObject::connectSlotsByName(Mm2DClass);
    } // setupUi

    void retranslateUi(QMainWindow *Mm2DClass)
    {
        Mm2DClass->setWindowTitle(QCoreApplication::translate("Mm2DClass", "Mm2D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mm2DClass: public Ui_Mm2DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MM2D_H
