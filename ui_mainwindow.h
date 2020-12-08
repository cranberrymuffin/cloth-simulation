/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QCheckBox>


#include "view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    View *view;
    QMenuBar *menuBar;
    QMenu *menuFile;

    // cloth modeling
    QDockWidget *clothDock;
    QWidget *clothDockContents;
    QWidget *clothControls;
    QGridLayout *gridLayout;
    QGroupBox *clothParameters;
    QVBoxLayout *verticalLayoutCloth;

    // particle mass
    QLabel *particleMassLabel;
    QSlider *particleMassSlider;
    QLineEdit *particleMassTextbox;

    // structural stiffness
    QLabel *structuralLabel;
    QSlider *structuralSlider;
    QLineEdit *structuralTextbox;

    // shear stiffness
    QLabel *shearLabel;
    QSlider *shearSlider;
    QLineEdit *shearTextbox;

    // shear stiffness
    QLabel *bendLabel;
    QSlider *bendSlider;
    QLineEdit *bendTextbox;

    // damping
    QLabel *dampingLabel;
    QSlider *dampingSlider;
    QLineEdit *dampingTextbox;

    // viscous
    QLabel *viscousLabel;
    QSlider *viscousSlider;
    QLineEdit *viscousTextbox;

    // gravity
    QLabel *gravityLabel;
    QCheckBox *gravityCheckbox;


    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        view = new View(centralWidget);
        view->setObjectName(QString::fromUtf8("view"));

        horizontalLayout->addWidget(view);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);


        // CLOTH SIDEBAR

        // create dock for cloth
        clothDock = new QDockWidget(MainWindow);
        clothDock->setObjectName(QString::fromUtf8("clothDock"));
        clothDockContents = new QWidget();
        clothDockContents->setObjectName(QString::fromUtf8("clothDockContents"));

        // vertical layout within the dock for the different controls
        verticalLayoutCloth = new QVBoxLayout(clothDockContents);
        verticalLayoutCloth->setSpacing(6);
        verticalLayoutCloth->setContentsMargins(11, 11, 11, 11);
        verticalLayoutCloth->setObjectName(QString::fromUtf8("verticalLayoutCloth"));

        // control box
        clothParameters = new QGroupBox(clothDockContents);
        clothParameters->setObjectName(QString::fromUtf8("clothParameters"));
        gridLayout = new QGridLayout(clothParameters);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(-1, 5, -1, 5);

        // --------------- LABELS ----------------------------------- //
        // particle mass label
        particleMassLabel = new QLabel(clothParameters);
        particleMassLabel->setObjectName(QString::fromUtf8("particleMassLabel"));
        particleMassLabel->setText(QCoreApplication::translate("MainWindow", "particle mass", nullptr));

        gridLayout->addWidget(particleMassLabel, 0, 0, 1, 1);

        // structural label
        structuralLabel = new QLabel(clothParameters);
        structuralLabel->setObjectName(QString::fromUtf8("structuralLabel"));
        structuralLabel->setText(QCoreApplication::translate("MainWindow", "structural stiffness", nullptr));

        gridLayout->addWidget(structuralLabel, 1, 0, 1, 1);

        // shear label
        shearLabel = new QLabel(clothParameters);
        shearLabel->setObjectName(QString::fromUtf8("shearLabel"));
        shearLabel->setText(QCoreApplication::translate("MainWindow", "shear stiffness", nullptr));

        gridLayout->addWidget(shearLabel, 2, 0, 1, 1);

        // bend label
        bendLabel = new QLabel(clothParameters);
        bendLabel->setObjectName(QString::fromUtf8("bendLabel"));
        bendLabel->setText(QCoreApplication::translate("MainWindow", "bend stiffness", nullptr));

        gridLayout->addWidget(bendLabel, 3, 0, 1, 1);

        // damping label
        dampingLabel = new QLabel(clothParameters);
        dampingLabel->setObjectName(QString::fromUtf8("dampingLabel"));
        dampingLabel->setText(QCoreApplication::translate("MainWindow", "damping", nullptr));

        gridLayout->addWidget(dampingLabel, 4, 0, 1, 1);

        // viscous label
        viscousLabel = new QLabel(clothParameters);
        viscousLabel->setObjectName(QString::fromUtf8("viscousLabel"));
        viscousLabel->setText(QCoreApplication::translate("MainWindow", "viscous", nullptr));

        gridLayout->addWidget(viscousLabel, 5, 0, 1, 1);

        // viscous label
        gravityLabel = new QLabel(clothParameters);
        gravityLabel->setObjectName(QString::fromUtf8("gravityLabel"));
        gravityLabel->setText(QCoreApplication::translate("MainWindow", "has gravity", nullptr));

        gridLayout->addWidget(gravityLabel, 6, 0, 1, 1);

        // --------------- SLIDERS // CHECKBOX ----------------------------------- //
        // particle mass slider
        particleMassSlider = new QSlider(clothParameters);
        particleMassSlider->setObjectName(QString::fromUtf8("particleMassSlider"));
        particleMassSlider->setMinimumSize(QSize(100, 0));
        particleMassSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(particleMassSlider, 0, 1, 1, 1);

        // structural stiffness slider
        structuralSlider = new QSlider(clothParameters);
        structuralSlider->setObjectName(QString::fromUtf8("structuralSlider"));
        structuralSlider->setMinimumSize(QSize(100, 0));
        structuralSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(structuralSlider, 1, 1, 1, 1);

        // shear stiffness slider
        shearSlider = new QSlider(clothParameters);
        shearSlider->setObjectName(QString::fromUtf8("shearSlider"));
        shearSlider->setMinimumSize(QSize(100, 0));
        shearSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(shearSlider, 2, 1, 1, 1);

        // bend stiffness slider
        bendSlider = new QSlider(clothParameters);
        bendSlider->setObjectName(QString::fromUtf8("bendSlider"));
        bendSlider->setMinimumSize(QSize(100, 0));
        bendSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(bendSlider, 3, 1, 1, 1);

        // damping slider
        dampingSlider = new QSlider(clothParameters);
        dampingSlider->setObjectName(QString::fromUtf8("dampingSlider"));
        dampingSlider->setMinimumSize(QSize(100, 0));
        dampingSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(dampingSlider, 4, 1, 1, 1);

        // viscous slider
        viscousSlider = new QSlider(clothParameters);
        viscousSlider->setObjectName(QString::fromUtf8("viscousSlider"));
        viscousSlider->setMinimumSize(QSize(100, 0));
        viscousSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(viscousSlider, 5, 1, 1, 1);

        // gravity checkbox
        gravityCheckbox = new QCheckBox(clothParameters);
        gravityCheckbox->setObjectName(QString::fromUtf8("gravityCheckbox"));

        gridLayout->addWidget(gravityCheckbox);


        // --------------- TEXTBOXES ----------------------------------- //
        // particle mass textbox
        particleMassTextbox = new QLineEdit(clothParameters);
        particleMassTextbox->setObjectName(QString::fromUtf8("particleMassTextbox"));
        particleMassTextbox->setMinimumSize(QSize(40, 0));
        particleMassTextbox->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(particleMassTextbox, 0, 2, 1, 1);

        // structural stiffness textbox
        structuralTextbox = new QLineEdit(clothParameters);
        structuralTextbox->setObjectName(QString::fromUtf8("structuralTextbox"));
        structuralTextbox->setMinimumSize(QSize(40, 0));
        structuralTextbox->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(structuralTextbox, 1, 2, 1, 1);

        // structural stiffness textbox
        shearTextbox = new QLineEdit(clothParameters);
        shearTextbox->setObjectName(QString::fromUtf8("shearTextbox"));
        shearTextbox->setMinimumSize(QSize(40, 0));
        shearTextbox->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(shearTextbox, 2, 2, 1, 1);

        // bend stiffness textbox
        bendTextbox = new QLineEdit(clothParameters);
        bendTextbox->setObjectName(QString::fromUtf8("bendTextbox"));
        bendTextbox->setMinimumSize(QSize(40, 0));
        bendTextbox->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(bendTextbox, 3, 2, 1, 1);

        // damping textbox
        dampingTextbox = new QLineEdit(clothParameters);
        dampingTextbox->setObjectName(QString::fromUtf8("dampingTextbox"));
        dampingTextbox->setMinimumSize(QSize(40, 0));
        dampingTextbox->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(dampingTextbox, 4, 2, 1, 1);

        // viscous textbox
        viscousTextbox = new QLineEdit(clothParameters);
        viscousTextbox->setObjectName(QString::fromUtf8("viscousTextbox"));
        viscousTextbox->setMinimumSize(QSize(40, 0));
        viscousTextbox->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(viscousTextbox, 5, 2, 1, 1);


        // ----------------------------------------------------------------- //



        verticalLayoutCloth->addWidget(clothParameters);
        clothDock->setWidget(clothDockContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, clothDock);

        retranslateUi(MainWindow);
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(openFileScene()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "A CS123 Final", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open..", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
