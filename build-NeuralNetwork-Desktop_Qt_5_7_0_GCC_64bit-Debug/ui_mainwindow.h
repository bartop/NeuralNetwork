/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionOpenNetwork;
    QAction *actionSaveNetwork;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *gridWidget_2;
    QGridLayout *gridLayout_3;
    QSpinBox *neuronsCountSpinBox;
    QDoubleSpinBox *inertionSpinBox;
    QSpinBox *previousSpinBox;
    QSpinBox *predictedSpinBox;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_7;
    QDoubleSpinBox *learningRateSpinBox;
    QSpinBox *iterationsSpinBox;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QPushButton *learnButton;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QMenu *menuPlik;
    QMenu *menuSie;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(892, 648);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionOpenNetwork = new QAction(MainWindow);
        actionOpenNetwork->setObjectName(QStringLiteral("actionOpenNetwork"));
        actionSaveNetwork = new QAction(MainWindow);
        actionSaveNetwork->setObjectName(QStringLiteral("actionSaveNetwork"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 4, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(256, 0));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridWidget_2 = new QWidget(tab);
        gridWidget_2->setObjectName(QStringLiteral("gridWidget_2"));
        gridWidget_2->setGeometry(QRect(0, 0, 251, 541));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gridWidget_2->sizePolicy().hasHeightForWidth());
        gridWidget_2->setSizePolicy(sizePolicy2);
        gridLayout_3 = new QGridLayout(gridWidget_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        neuronsCountSpinBox = new QSpinBox(gridWidget_2);
        neuronsCountSpinBox->setObjectName(QStringLiteral("neuronsCountSpinBox"));
        neuronsCountSpinBox->setMaximum(1000);
        neuronsCountSpinBox->setValue(30);

        gridLayout_3->addWidget(neuronsCountSpinBox, 3, 1, 1, 1);

        inertionSpinBox = new QDoubleSpinBox(gridWidget_2);
        inertionSpinBox->setObjectName(QStringLiteral("inertionSpinBox"));
        inertionSpinBox->setMaximum(1);
        inertionSpinBox->setSingleStep(0.05);
        inertionSpinBox->setValue(0.9);

        gridLayout_3->addWidget(inertionSpinBox, 2, 1, 1, 1);

        previousSpinBox = new QSpinBox(gridWidget_2);
        previousSpinBox->setObjectName(QStringLiteral("previousSpinBox"));
        previousSpinBox->setValue(3);

        gridLayout_3->addWidget(previousSpinBox, 0, 1, 1, 1);

        predictedSpinBox = new QSpinBox(gridWidget_2);
        predictedSpinBox->setObjectName(QStringLiteral("predictedSpinBox"));
        predictedSpinBox->setValue(1);

        gridLayout_3->addWidget(predictedSpinBox, 1, 1, 1, 1);

        label_4 = new QLabel(gridWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(gridWidget_2);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(gridWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(gridWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer, 6, 0, 1, 1);

        label_7 = new QLabel(gridWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_7, 4, 0, 1, 1);

        learningRateSpinBox = new QDoubleSpinBox(gridWidget_2);
        learningRateSpinBox->setObjectName(QStringLiteral("learningRateSpinBox"));
        learningRateSpinBox->setMaximum(1);
        learningRateSpinBox->setSingleStep(0.05);
        learningRateSpinBox->setValue(0.5);

        gridLayout_3->addWidget(learningRateSpinBox, 4, 1, 1, 1);

        iterationsSpinBox = new QSpinBox(gridWidget_2);
        iterationsSpinBox->setObjectName(QStringLiteral("iterationsSpinBox"));
        iterationsSpinBox->setMaximum(1000000);
        iterationsSpinBox->setValue(100);

        gridLayout_3->addWidget(iterationsSpinBox, 5, 1, 1, 1);

        label_6 = new QLabel(gridWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_6, 5, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 6, 1, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 4, 1, 1, 1);

        learnButton = new QPushButton(centralwidget);
        learnButton->setObjectName(QStringLiteral("learnButton"));

        gridLayout->addWidget(learnButton, 5, 1, 1, 1);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 5, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 892, 26));
        menuPlik = new QMenu(menubar);
        menuPlik->setObjectName(QStringLiteral("menuPlik"));
        menuSie = new QMenu(menubar);
        menuSie->setObjectName(QStringLiteral("menuSie"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPlik->menuAction());
        menubar->addAction(menuSie->menuAction());
        menuPlik->addAction(actionOpen);
        menuPlik->addAction(actionSave);
        menuSie->addAction(actionOpenNetwork);
        menuSie->addAction(actionSaveNetwork);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Prognozowanie pogody", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Otw\303\263rz", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Otw\303\263rz plik CSV", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "Wygeneruj wynikowe", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionOpenNetwork->setText(QApplication::translate("MainWindow", "Wczytaj", 0));
        actionSaveNetwork->setText(QApplication::translate("MainWindow", "Zapisz", 0));
        label_4->setText(QApplication::translate("MainWindow", "Liczba neuron\303\263w", 0));
        label->setText(QApplication::translate("MainWindow", "Poprzednie", 0));
        label_3->setText(QApplication::translate("MainWindow", "Inercja", 0));
        label_2->setText(QApplication::translate("MainWindow", "Przewidziane", 0));
        label_7->setText(QApplication::translate("MainWindow", "Wsp. uczenia", 0));
        label_6->setText(QApplication::translate("MainWindow", "Liczba iteracji", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Parametry sieci", 0));
        learnButton->setText(QApplication::translate("MainWindow", "Ucz", 0));
        menuPlik->setTitle(QApplication::translate("MainWindow", "Dane", 0));
        menuSie->setTitle(QApplication::translate("MainWindow", "Sie\304\207", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
