/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <meshviewerwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QPushButton *pushButton_chargement;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QProgressBar *saliencyProgressBar;
    QLabel *label_6;
    QComboBox *decimationComboBox;
    QLabel *rangeLabel;
    QLabel *label_2;
    QDoubleSpinBox *thresholdSpinBox;
    QLabel *label_7;
    QPushButton *pushButton_3;
    QProgressBar *decimationProgressBar;
    QLabel *label_8;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox;
    MeshViewerWidget *displayWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(840, 539);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(150);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(150, 0));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setItalic(true);
        font.setUnderline(false);
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        pushButton_chargement = new QPushButton(widget_2);
        pushButton_chargement->setObjectName(QStringLiteral("pushButton_chargement"));
        pushButton_chargement->setMinimumSize(QSize(200, 0));

        verticalLayout->addWidget(pushButton_chargement);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font1;
        font1.setItalic(true);
        label_4->setFont(font1);

        verticalLayout->addWidget(label_4);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        saliencyProgressBar = new QProgressBar(widget_2);
        saliencyProgressBar->setObjectName(QStringLiteral("saliencyProgressBar"));
        saliencyProgressBar->setAutoFillBackground(false);
        saliencyProgressBar->setValue(0);

        verticalLayout->addWidget(saliencyProgressBar);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        verticalLayout->addWidget(label_6);

        decimationComboBox = new QComboBox(widget_2);
        decimationComboBox->setObjectName(QStringLiteral("decimationComboBox"));

        verticalLayout->addWidget(decimationComboBox);

        rangeLabel = new QLabel(widget_2);
        rangeLabel->setObjectName(QStringLiteral("rangeLabel"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        rangeLabel->setFont(font2);

        verticalLayout->addWidget(rangeLabel);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        thresholdSpinBox = new QDoubleSpinBox(widget_2);
        thresholdSpinBox->setObjectName(QStringLiteral("thresholdSpinBox"));
        thresholdSpinBox->setDecimals(10);

        verticalLayout->addWidget(thresholdSpinBox);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        verticalLayout->addWidget(label_7);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        decimationProgressBar = new QProgressBar(widget_2);
        decimationProgressBar->setObjectName(QStringLiteral("decimationProgressBar"));
        decimationProgressBar->setValue(0);

        verticalLayout->addWidget(decimationProgressBar);

        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font1);

        verticalLayout->addWidget(label_8);

        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        checkBox = new QCheckBox(widget_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);


        horizontalLayout->addWidget(widget_2);

        displayWidget = new MeshViewerWidget(centralWidget);
        displayWidget->setObjectName(QStringLiteral("displayWidget"));

        horizontalLayout->addWidget(displayWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 840, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Load a mesh", Q_NULLPTR));
        pushButton_chargement->setText(QApplication::translate("MainWindow", "Load Mesh", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Launch the calculation", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Saliency", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Choose a decimation method", Q_NULLPTR));
        rangeLabel->setText(QApplication::translate("MainWindow", "Range = WAITING FOR SALIENCY", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Choose a threshold", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Launch decimation", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Decimate (NON FUNCTIONNAL)", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Save the result.", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Export (NON FUNCTIONNAL)", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "Live Display (Can slow the process)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
