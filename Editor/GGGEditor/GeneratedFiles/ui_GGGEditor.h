/********************************************************************************
** Form generated from reading UI file 'GGGEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GGGEDITOR_H
#define UI_GGGEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GGGEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GGGEditorClass)
    {
        if (GGGEditorClass->objectName().isEmpty())
            GGGEditorClass->setObjectName(QStringLiteral("GGGEditorClass"));
        GGGEditorClass->resize(600, 400);
        menuBar = new QMenuBar(GGGEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GGGEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GGGEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GGGEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GGGEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GGGEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GGGEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GGGEditorClass->setStatusBar(statusBar);

        retranslateUi(GGGEditorClass);

        QMetaObject::connectSlotsByName(GGGEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *GGGEditorClass)
    {
        GGGEditorClass->setWindowTitle(QApplication::translate("GGGEditorClass", "GGGEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GGGEditorClass: public Ui_GGGEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GGGEDITOR_H
