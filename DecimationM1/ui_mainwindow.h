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
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_6;
    QComboBox *decimationComboBox;
    QLabel *label;
    QDoubleSpinBox *decimationRatioSpinbox;
    QLabel *label_7;
    QPushButton *pushButton_3;
    QLabel *label_8;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    MeshViewerWidget *displayWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1020, 642);
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

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        verticalLayout->addWidget(label_6);

        decimationComboBox = new QComboBox(widget_2);
        decimationComboBox->setObjectName(QStringLiteral("decimationComboBox"));

        verticalLayout->addWidget(decimationComboBox);

        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        verticalLayout->addWidget(label);

        decimationRatioSpinbox = new QDoubleSpinBox(widget_2);
        decimationRatioSpinbox->setObjectName(QStringLiteral("decimationRatioSpinbox"));

        verticalLayout->addWidget(decimationRatioSpinbox);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        verticalLayout->addWidget(label_7);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

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

        checkBox_2 = new QCheckBox(widget_2);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);


        horizontalLayout->addWidget(widget_2);

        displayWidget = new MeshViewerWidget(centralWidget);
        displayWidget->setObjectName(QStringLiteral("displayWidget"));

        horizontalLayout->addWidget(displayWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1020, 22));
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
        label_4->setText(QApplication::translate("MainWindow", "Launch the calculation or load an existing heatfile", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Saliency", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "(Optional) Save the heatmap", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Export heatmap", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Choose a decimation method", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Choose the decimation ratio ( 0 - 100 )", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Launch decimation", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Decimate", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Save the result", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Export", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "Live Saliency (Can slow the process)", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "Heatmap on Decimate", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
