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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
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

    // CLOTH
    QDockWidget *clothDock;
    QWidget *clothDockContents;
    QVBoxLayout *verticalLayout;

    // spring forces
    QGroupBox *springForces;
    QGridLayout *springGrid;
    // constants
    QGroupBox *constants;
    QGridLayout *constantsGrid;
    // empty
    QWidget *emptySpace;

    // particle mass
    QSlider *particleMassSlider;
    QLabel *particleMassLabel;
    QLineEdit *particleMassTextbox;

    // structural
    QSlider *structuralSlider;
    QLabel *structuralLabel;
    QLineEdit *structuralTextbox;

    // shear
    QSlider *shearSlider;
    QLabel *shearLabel;
    QLineEdit *shearTextbox;

    // bend
    QSlider *bendSlider;
    QLabel *bendLabel;
    QLineEdit *bendTextbox;

    // damping
    QSlider *dampingSlider;
    QLabel *dampingLabel;
    QLineEdit *dampingTextbox;

    // structural
    QSlider *viscousSlider;
    QLabel *viscousLabel;
    QLineEdit *viscousTextbox;

    // gravity checkbox
    QCheckBox *gravityCheckbox;
    QLabel *gravityLabel;

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
        menuFile->addAction(actionOpen);\

// -------------------------------- CLOTH -------------------------------------- //

        // cloth dock
        clothDock = new QDockWidget(MainWindow);
        clothDock->setObjectName(QString::fromUtf8("clothDock"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(clothDock->sizePolicy().hasHeightForWidth());
        clothDock->setSizePolicy(sizePolicy);
        clothDock->setFloating(false);
        clothDock->setAllowedAreas(Qt::AllDockWidgetAreas);

        // cloth dock contents
        clothDockContents = new QWidget();
        clothDockContents->setObjectName(QString::fromUtf8("clothDockContents"));
        sizePolicy.setHeightForWidth(clothDockContents->sizePolicy().hasHeightForWidth());
        clothDockContents->setSizePolicy(sizePolicy);

        // vertical layout
        verticalLayout = new QVBoxLayout(clothDockContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

// -------------------------------- SPRING FORCES -------------------------------------- //

        // spring forces sub layout
        springForces = new QGroupBox(clothDockContents);
        springForces->setObjectName(QString::fromUtf8("springForces"));
        springGrid = new QGridLayout(springForces);
        springGrid->setSpacing(6);
        springGrid->setContentsMargins(11, 11, 11, 11);
        springGrid->setObjectName(QString::fromUtf8("springGrid"));
        springGrid->setVerticalSpacing(5);
        springGrid->setContentsMargins(-1, 5, -1, 5);

        // -------------------------------- TEXTBOX ------------------------------------ //

        // structural
        structuralTextbox = new QLineEdit(springForces);
        structuralTextbox->setObjectName(QString::fromUtf8("structuralTextbox"));
        structuralTextbox->setMinimumSize(QSize(50, 0));
        structuralTextbox->setMaximumSize(QSize(50, 16777215));

        springGrid->addWidget(structuralTextbox, 0, 3, 1, 1);

        // shear
        shearTextbox = new QLineEdit(springForces);
        shearTextbox->setObjectName(QString::fromUtf8("shearTextbox"));
        shearTextbox->setMinimumSize(QSize(50, 0));
        shearTextbox->setMaximumSize(QSize(50, 16777215));

        springGrid->addWidget(shearTextbox, 1, 3, 1, 1);

        // bend
        bendTextbox = new QLineEdit(springForces);
        bendTextbox->setObjectName(QString::fromUtf8("bendTextbox"));
        bendTextbox->setMinimumSize(QSize(50, 0));
        bendTextbox->setMaximumSize(QSize(50, 16777215));

        springGrid->addWidget(bendTextbox, 2, 3, 1, 1);

        // --------------------------- SLIDERS ------------------------------------- //
        // structural
        structuralSlider = new QSlider(springForces);
        structuralSlider->setObjectName(QString::fromUtf8("structuralSlider"));
        structuralSlider->setMinimumSize(QSize(100, 0));
        structuralSlider->setOrientation(Qt::Horizontal);

        springGrid->addWidget(structuralSlider, 0, 2, 1, 1);

        // shear
        shearSlider = new QSlider(springForces);
        shearSlider->setObjectName(QString::fromUtf8("shearSlider"));
        shearSlider->setMinimumSize(QSize(100, 0));
        shearSlider->setOrientation(Qt::Horizontal);

        springGrid->addWidget(shearSlider, 1, 2, 1, 1);

        // bend
        bendSlider = new QSlider(springForces);
        bendSlider->setObjectName(QString::fromUtf8("bendSlider"));
        bendSlider->setMinimumSize(QSize(100, 0));
        bendSlider->setOrientation(Qt::Horizontal);

        springGrid->addWidget(bendSlider, 2, 2, 1, 1);

        // --------------------------------- LABEL ------------------------------------- //
        // structural
        structuralLabel = new QLabel(springForces);
        structuralLabel->setObjectName(QString::fromUtf8("structuralLabel"));

        springGrid->addWidget(structuralLabel, 0, 0, 1, 1);

        // shear
        shearLabel = new QLabel(springForces);
        shearLabel->setObjectName(QString::fromUtf8("shearLabel"));

        springGrid->addWidget(shearLabel, 1, 0, 1, 1);

        // bend
        bendLabel = new QLabel(springForces);
        bendLabel->setObjectName(QString::fromUtf8("bendLabel"));

        springGrid->addWidget(bendLabel, 2, 0, 1, 1);

        // labeling
        springForces->setTitle(QCoreApplication::translate("MainWindow", "Spring Forces", nullptr));
        structuralLabel->setText(QCoreApplication::translate("MainWindow", "structural", nullptr));
        shearLabel->setText(QCoreApplication::translate("MainWindow", "shear", nullptr));
        bendLabel->setText(QCoreApplication::translate("MainWindow", "bend", nullptr));

//------------------------------- CONSTANTS SUB LAYOUT -----------------------------//
        constants = new QGroupBox(clothDockContents);
        constants->setObjectName(QString::fromUtf8("constants"));
        constantsGrid = new QGridLayout(constants);
        constantsGrid->setSpacing(6);
        constantsGrid->setContentsMargins(11, 11, 11, 11);
        constantsGrid->setObjectName(QString::fromUtf8("constantsGrid"));
        constantsGrid->setVerticalSpacing(5);
        constantsGrid->setContentsMargins(-1, 5, -1, 5);

        // -------------------------------- TEXTBOX ------------------------------------ //

        // particle mass
        particleMassTextbox = new QLineEdit(constants);
        particleMassTextbox->setObjectName(QString::fromUtf8("particleMassTextbox"));
        particleMassTextbox->setMinimumSize(QSize(50, 0));
        particleMassTextbox->setMaximumSize(QSize(50, 16777215));

        constantsGrid->addWidget(particleMassTextbox, 0, 3, 1, 1);

        // damping
        dampingTextbox = new QLineEdit(constants);
        dampingTextbox->setObjectName(QString::fromUtf8("dampingTextbox"));
        dampingTextbox->setMinimumSize(QSize(50, 0));
        dampingTextbox->setMaximumSize(QSize(50, 16777215));

        constantsGrid->addWidget(dampingTextbox, 1, 3, 1, 1);

        // viscous
        viscousTextbox = new QLineEdit(constants);
        viscousTextbox->setObjectName(QString::fromUtf8("viscousTextbox"));
        viscousTextbox->setMinimumSize(QSize(50, 0));
        viscousTextbox->setMaximumSize(QSize(50, 16777215));

        constantsGrid->addWidget(viscousTextbox, 2, 3, 1, 1);

        // --------------------------- SLIDERS ------------------------------------- //
        // particle mass
        particleMassSlider = new QSlider(constants);
        particleMassSlider->setObjectName(QString::fromUtf8("particleMassSlider"));
        particleMassSlider->setMinimumSize(QSize(100, 0));
        particleMassSlider->setOrientation(Qt::Horizontal);

        constantsGrid->addWidget(particleMassSlider, 0, 2, 1, 1);

        // damping
        dampingSlider = new QSlider(constants);
        dampingSlider->setObjectName(QString::fromUtf8("dampingSlider"));
        dampingSlider->setMinimumSize(QSize(100, 0));
        dampingSlider->setOrientation(Qt::Horizontal);

        constantsGrid->addWidget(dampingSlider, 1, 2, 1, 1);

        // viscous
        viscousSlider = new QSlider(constants);
        viscousSlider->setObjectName(QString::fromUtf8("viscousSlider"));
        viscousSlider->setMinimumSize(QSize(100, 0));
        viscousSlider->setOrientation(Qt::Horizontal);

        constantsGrid->addWidget(viscousSlider, 2, 2, 1, 1);

        // --------------------------------- LABEL ------------------------------------- //
        // particle mass
        particleMassLabel = new QLabel(constants);
        particleMassLabel->setObjectName(QString::fromUtf8("particleMassLabel"));

        constantsGrid->addWidget(particleMassLabel, 0, 0, 1, 1);

        // damping
        dampingLabel = new QLabel(constants);
        dampingLabel->setObjectName(QString::fromUtf8("dampingLabel"));

        constantsGrid->addWidget(dampingLabel, 1, 0, 1, 1);

        // viscous
        viscousLabel = new QLabel(constants);
        viscousLabel->setObjectName(QString::fromUtf8("viscousLabel"));

        constantsGrid->addWidget(viscousLabel, 2, 0, 1, 1);

        // labeling
        constants->setTitle(QCoreApplication::translate("MainWindow", "Constants", nullptr));
        particleMassLabel->setText(QCoreApplication::translate("MainWindow", "particle mass", nullptr));
        dampingLabel->setText(QCoreApplication::translate("MainWindow", "damping", nullptr));
        viscousLabel->setText(QCoreApplication::translate("MainWindow", "viscous", nullptr));


// ------------------------------- CHECKBOX ------------------------------------- //
        gravityCheckbox = new QCheckBox(clothDockContents);
        gravityCheckbox->setObjectName(QString::fromUtf8("gravityCheckbox"));
        gravityCheckbox->setChecked(true);
        gravityCheckbox->setText(QCoreApplication::translate("MainWindow", "has gravity", nullptr));

// ------------------------------- EMPTY SPACE ------------------------------------- //

        emptySpace = new QWidget(clothDockContents);
        emptySpace->setObjectName(QString::fromUtf8("emptySpace"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(emptySpace->sizePolicy().hasHeightForWidth());
        emptySpace->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(springForces);
        verticalLayout->addWidget(constants);
        verticalLayout->addWidget(gravityCheckbox);
        verticalLayout->addWidget(emptySpace);

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
