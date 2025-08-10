/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labCPU1;
    QProgressBar *barCPU1;
    QLabel *freqCPU1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labCPU2;
    QProgressBar *barCPU2;
    QLabel *freqCPU2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labCPU3;
    QProgressBar *barCPU3;
    QLabel *freqCPU3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labCPU4;
    QProgressBar *barCPU4;
    QLabel *freqCPU4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labCPU5;
    QProgressBar *barCPU5;
    QLabel *freqCPU5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labCPU6;
    QProgressBar *barCPU6;
    QLabel *freqCPU6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labCPU7;
    QProgressBar *barCPU7;
    QLabel *freqCPU7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labCPU8;
    QProgressBar *barCPU8;
    QLabel *freqCPU8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labNPU1;
    QProgressBar *barNPU1;
    QLabel *freqNPU1;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labNPU2;
    QProgressBar *barNPU2;
    QLabel *freqNPU2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labNPU3;
    QProgressBar *barNPU3;
    QLabel *freqNPU3;
    QHBoxLayout *horizontalLayout_17;
    QLabel *labRGA1;
    QProgressBar *barRGA1;
    QLabel *freqRGA1;
    QHBoxLayout *horizontalLayout_18;
    QLabel *labRGA2;
    QProgressBar *barRGA2;
    QLabel *freqRGA2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *labRGA3;
    QProgressBar *barRGA3;
    QLabel *freqRGA3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *labGPU;
    QProgressBar *barGPU;
    QLabel *freqGPU;
    QHBoxLayout *horizontalLayout_13;
    QLabel *labMem;
    QProgressBar *barMem;
    QLabel *freqMem;
    QHBoxLayout *horizontalLayout_14;
    QLabel *labSwap;
    QProgressBar *barSwap;
    QLabel *freqSwap;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_5;
    QProgressBar *barTemp;
    QLabel *freqTemp;
    QHBoxLayout *horizontalLayout_16;
    QLabel *labFan;
    QProgressBar *barFan;
    QLabel *freqFan;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(313, 468);
        Dialog->setMinimumSize(QSize(300, 0));
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labCPU1 = new QLabel(Dialog);
        labCPU1->setObjectName(QString::fromUtf8("labCPU1"));
        labCPU1->setMinimumSize(QSize(38, 0));
        labCPU1->setMaximumSize(QSize(38, 16777215));
        QFont font;
        font.setPointSize(10);
        labCPU1->setFont(font);

        horizontalLayout->addWidget(labCPU1);

        barCPU1 = new QProgressBar(Dialog);
        barCPU1->setObjectName(QString::fromUtf8("barCPU1"));
        barCPU1->setMinimumSize(QSize(0, 16));
        barCPU1->setMaximumSize(QSize(16777215, 16));
        QFont font1;
        font1.setPointSize(9);
        barCPU1->setFont(font1);
        barCPU1->setValue(0);

        horizontalLayout->addWidget(barCPU1);

        freqCPU1 = new QLabel(Dialog);
        freqCPU1->setObjectName(QString::fromUtf8("freqCPU1"));
        freqCPU1->setMinimumSize(QSize(59, 0));
        freqCPU1->setMaximumSize(QSize(59, 16777215));
        freqCPU1->setFont(font);

        horizontalLayout->addWidget(freqCPU1);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labCPU2 = new QLabel(Dialog);
        labCPU2->setObjectName(QString::fromUtf8("labCPU2"));
        labCPU2->setMinimumSize(QSize(38, 0));
        labCPU2->setMaximumSize(QSize(38, 16777215));
        labCPU2->setFont(font);

        horizontalLayout_2->addWidget(labCPU2);

        barCPU2 = new QProgressBar(Dialog);
        barCPU2->setObjectName(QString::fromUtf8("barCPU2"));
        barCPU2->setMinimumSize(QSize(0, 16));
        barCPU2->setMaximumSize(QSize(16777215, 16));
        barCPU2->setFont(font1);
        barCPU2->setValue(0);

        horizontalLayout_2->addWidget(barCPU2);

        freqCPU2 = new QLabel(Dialog);
        freqCPU2->setObjectName(QString::fromUtf8("freqCPU2"));
        freqCPU2->setMinimumSize(QSize(59, 0));
        freqCPU2->setMaximumSize(QSize(59, 16777215));
        freqCPU2->setFont(font);

        horizontalLayout_2->addWidget(freqCPU2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labCPU3 = new QLabel(Dialog);
        labCPU3->setObjectName(QString::fromUtf8("labCPU3"));
        labCPU3->setMinimumSize(QSize(38, 0));
        labCPU3->setMaximumSize(QSize(38, 16777215));
        labCPU3->setFont(font);

        horizontalLayout_3->addWidget(labCPU3);

        barCPU3 = new QProgressBar(Dialog);
        barCPU3->setObjectName(QString::fromUtf8("barCPU3"));
        barCPU3->setMinimumSize(QSize(0, 16));
        barCPU3->setMaximumSize(QSize(16777215, 16));
        barCPU3->setFont(font1);
        barCPU3->setValue(0);

        horizontalLayout_3->addWidget(barCPU3);

        freqCPU3 = new QLabel(Dialog);
        freqCPU3->setObjectName(QString::fromUtf8("freqCPU3"));
        freqCPU3->setMinimumSize(QSize(59, 0));
        freqCPU3->setMaximumSize(QSize(59, 16777215));
        freqCPU3->setFont(font);

        horizontalLayout_3->addWidget(freqCPU3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labCPU4 = new QLabel(Dialog);
        labCPU4->setObjectName(QString::fromUtf8("labCPU4"));
        labCPU4->setMinimumSize(QSize(38, 0));
        labCPU4->setMaximumSize(QSize(38, 16777215));
        labCPU4->setFont(font);

        horizontalLayout_4->addWidget(labCPU4);

        barCPU4 = new QProgressBar(Dialog);
        barCPU4->setObjectName(QString::fromUtf8("barCPU4"));
        barCPU4->setMinimumSize(QSize(0, 16));
        barCPU4->setMaximumSize(QSize(16777215, 16));
        barCPU4->setFont(font1);
        barCPU4->setValue(0);

        horizontalLayout_4->addWidget(barCPU4);

        freqCPU4 = new QLabel(Dialog);
        freqCPU4->setObjectName(QString::fromUtf8("freqCPU4"));
        freqCPU4->setMinimumSize(QSize(59, 0));
        freqCPU4->setMaximumSize(QSize(59, 16777215));
        freqCPU4->setFont(font);

        horizontalLayout_4->addWidget(freqCPU4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labCPU5 = new QLabel(Dialog);
        labCPU5->setObjectName(QString::fromUtf8("labCPU5"));
        labCPU5->setMinimumSize(QSize(38, 0));
        labCPU5->setMaximumSize(QSize(38, 16777215));
        labCPU5->setFont(font);

        horizontalLayout_5->addWidget(labCPU5);

        barCPU5 = new QProgressBar(Dialog);
        barCPU5->setObjectName(QString::fromUtf8("barCPU5"));
        barCPU5->setMinimumSize(QSize(0, 16));
        barCPU5->setMaximumSize(QSize(16777215, 16));
        barCPU5->setFont(font1);
        barCPU5->setValue(0);

        horizontalLayout_5->addWidget(barCPU5);

        freqCPU5 = new QLabel(Dialog);
        freqCPU5->setObjectName(QString::fromUtf8("freqCPU5"));
        freqCPU5->setMinimumSize(QSize(59, 0));
        freqCPU5->setMaximumSize(QSize(59, 16777215));
        freqCPU5->setFont(font);

        horizontalLayout_5->addWidget(freqCPU5);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labCPU6 = new QLabel(Dialog);
        labCPU6->setObjectName(QString::fromUtf8("labCPU6"));
        labCPU6->setMinimumSize(QSize(38, 0));
        labCPU6->setMaximumSize(QSize(38, 16777215));
        labCPU6->setFont(font);

        horizontalLayout_6->addWidget(labCPU6);

        barCPU6 = new QProgressBar(Dialog);
        barCPU6->setObjectName(QString::fromUtf8("barCPU6"));
        barCPU6->setMinimumSize(QSize(0, 16));
        barCPU6->setMaximumSize(QSize(16777215, 16));
        barCPU6->setFont(font1);
        barCPU6->setValue(0);

        horizontalLayout_6->addWidget(barCPU6);

        freqCPU6 = new QLabel(Dialog);
        freqCPU6->setObjectName(QString::fromUtf8("freqCPU6"));
        freqCPU6->setMinimumSize(QSize(59, 0));
        freqCPU6->setMaximumSize(QSize(59, 16777215));
        freqCPU6->setFont(font);

        horizontalLayout_6->addWidget(freqCPU6);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labCPU7 = new QLabel(Dialog);
        labCPU7->setObjectName(QString::fromUtf8("labCPU7"));
        labCPU7->setMinimumSize(QSize(38, 0));
        labCPU7->setMaximumSize(QSize(38, 16777215));
        labCPU7->setFont(font);

        horizontalLayout_7->addWidget(labCPU7);

        barCPU7 = new QProgressBar(Dialog);
        barCPU7->setObjectName(QString::fromUtf8("barCPU7"));
        barCPU7->setMinimumSize(QSize(0, 16));
        barCPU7->setMaximumSize(QSize(16777215, 16));
        barCPU7->setFont(font1);
        barCPU7->setValue(0);

        horizontalLayout_7->addWidget(barCPU7);

        freqCPU7 = new QLabel(Dialog);
        freqCPU7->setObjectName(QString::fromUtf8("freqCPU7"));
        freqCPU7->setMinimumSize(QSize(59, 0));
        freqCPU7->setMaximumSize(QSize(59, 16777215));
        freqCPU7->setFont(font);

        horizontalLayout_7->addWidget(freqCPU7);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labCPU8 = new QLabel(Dialog);
        labCPU8->setObjectName(QString::fromUtf8("labCPU8"));
        labCPU8->setMinimumSize(QSize(38, 0));
        labCPU8->setMaximumSize(QSize(38, 16777215));
        labCPU8->setFont(font);

        horizontalLayout_8->addWidget(labCPU8);

        barCPU8 = new QProgressBar(Dialog);
        barCPU8->setObjectName(QString::fromUtf8("barCPU8"));
        barCPU8->setMinimumSize(QSize(0, 16));
        barCPU8->setMaximumSize(QSize(16777215, 16));
        barCPU8->setFont(font1);
        barCPU8->setValue(0);

        horizontalLayout_8->addWidget(barCPU8);

        freqCPU8 = new QLabel(Dialog);
        freqCPU8->setObjectName(QString::fromUtf8("freqCPU8"));
        freqCPU8->setMinimumSize(QSize(59, 0));
        freqCPU8->setMaximumSize(QSize(59, 16777215));
        freqCPU8->setFont(font);

        horizontalLayout_8->addWidget(freqCPU8);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        labNPU1 = new QLabel(Dialog);
        labNPU1->setObjectName(QString::fromUtf8("labNPU1"));
        labNPU1->setMinimumSize(QSize(38, 0));
        labNPU1->setMaximumSize(QSize(38, 16777215));
        labNPU1->setFont(font);

        horizontalLayout_9->addWidget(labNPU1);

        barNPU1 = new QProgressBar(Dialog);
        barNPU1->setObjectName(QString::fromUtf8("barNPU1"));
        barNPU1->setMinimumSize(QSize(0, 16));
        barNPU1->setMaximumSize(QSize(16777215, 16));
        barNPU1->setFont(font1);
        barNPU1->setValue(0);

        horizontalLayout_9->addWidget(barNPU1);

        freqNPU1 = new QLabel(Dialog);
        freqNPU1->setObjectName(QString::fromUtf8("freqNPU1"));
        freqNPU1->setMinimumSize(QSize(59, 0));
        freqNPU1->setMaximumSize(QSize(59, 16777215));
        freqNPU1->setFont(font);

        horizontalLayout_9->addWidget(freqNPU1);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labNPU2 = new QLabel(Dialog);
        labNPU2->setObjectName(QString::fromUtf8("labNPU2"));
        labNPU2->setMinimumSize(QSize(38, 0));
        labNPU2->setMaximumSize(QSize(38, 16777215));
        labNPU2->setFont(font);

        horizontalLayout_10->addWidget(labNPU2);

        barNPU2 = new QProgressBar(Dialog);
        barNPU2->setObjectName(QString::fromUtf8("barNPU2"));
        barNPU2->setMinimumSize(QSize(0, 16));
        barNPU2->setMaximumSize(QSize(16777215, 16));
        barNPU2->setFont(font1);
        barNPU2->setValue(0);

        horizontalLayout_10->addWidget(barNPU2);

        freqNPU2 = new QLabel(Dialog);
        freqNPU2->setObjectName(QString::fromUtf8("freqNPU2"));
        freqNPU2->setMinimumSize(QSize(59, 0));
        freqNPU2->setMaximumSize(QSize(59, 16777215));
        freqNPU2->setFont(font);

        horizontalLayout_10->addWidget(freqNPU2);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        labNPU3 = new QLabel(Dialog);
        labNPU3->setObjectName(QString::fromUtf8("labNPU3"));
        labNPU3->setMinimumSize(QSize(38, 0));
        labNPU3->setMaximumSize(QSize(38, 16777215));
        labNPU3->setFont(font);

        horizontalLayout_11->addWidget(labNPU3);

        barNPU3 = new QProgressBar(Dialog);
        barNPU3->setObjectName(QString::fromUtf8("barNPU3"));
        barNPU3->setMinimumSize(QSize(0, 16));
        barNPU3->setMaximumSize(QSize(16777215, 16));
        barNPU3->setFont(font1);
        barNPU3->setValue(0);

        horizontalLayout_11->addWidget(barNPU3);

        freqNPU3 = new QLabel(Dialog);
        freqNPU3->setObjectName(QString::fromUtf8("freqNPU3"));
        freqNPU3->setMinimumSize(QSize(59, 0));
        freqNPU3->setMaximumSize(QSize(59, 16777215));
        freqNPU3->setFont(font);

        horizontalLayout_11->addWidget(freqNPU3);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        labRGA1 = new QLabel(Dialog);
        labRGA1->setObjectName(QString::fromUtf8("labRGA1"));
        labRGA1->setMinimumSize(QSize(38, 0));
        labRGA1->setMaximumSize(QSize(38, 16777215));
        labRGA1->setFont(font);

        horizontalLayout_17->addWidget(labRGA1);

        barRGA1 = new QProgressBar(Dialog);
        barRGA1->setObjectName(QString::fromUtf8("barRGA1"));
        barRGA1->setMinimumSize(QSize(0, 16));
        barRGA1->setMaximumSize(QSize(16777215, 16));
        barRGA1->setFont(font1);
        barRGA1->setValue(0);

        horizontalLayout_17->addWidget(barRGA1);

        freqRGA1 = new QLabel(Dialog);
        freqRGA1->setObjectName(QString::fromUtf8("freqRGA1"));
        freqRGA1->setMinimumSize(QSize(59, 0));
        freqRGA1->setMaximumSize(QSize(59, 16777215));
        freqRGA1->setFont(font);

        horizontalLayout_17->addWidget(freqRGA1);


        verticalLayout->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        labRGA2 = new QLabel(Dialog);
        labRGA2->setObjectName(QString::fromUtf8("labRGA2"));
        labRGA2->setMinimumSize(QSize(38, 0));
        labRGA2->setMaximumSize(QSize(38, 16777215));
        labRGA2->setFont(font);

        horizontalLayout_18->addWidget(labRGA2);

        barRGA2 = new QProgressBar(Dialog);
        barRGA2->setObjectName(QString::fromUtf8("barRGA2"));
        barRGA2->setMinimumSize(QSize(0, 16));
        barRGA2->setMaximumSize(QSize(16777215, 16));
        barRGA2->setFont(font1);
        barRGA2->setValue(0);

        horizontalLayout_18->addWidget(barRGA2);

        freqRGA2 = new QLabel(Dialog);
        freqRGA2->setObjectName(QString::fromUtf8("freqRGA2"));
        freqRGA2->setMinimumSize(QSize(59, 0));
        freqRGA2->setMaximumSize(QSize(59, 16777215));
        freqRGA2->setFont(font);

        horizontalLayout_18->addWidget(freqRGA2);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        labRGA3 = new QLabel(Dialog);
        labRGA3->setObjectName(QString::fromUtf8("labRGA3"));
        labRGA3->setMinimumSize(QSize(38, 0));
        labRGA3->setMaximumSize(QSize(38, 16777215));
        labRGA3->setFont(font);

        horizontalLayout_19->addWidget(labRGA3);

        barRGA3 = new QProgressBar(Dialog);
        barRGA3->setObjectName(QString::fromUtf8("barRGA3"));
        barRGA3->setMinimumSize(QSize(0, 16));
        barRGA3->setMaximumSize(QSize(16777215, 16));
        barRGA3->setFont(font1);
        barRGA3->setValue(0);

        horizontalLayout_19->addWidget(barRGA3);

        freqRGA3 = new QLabel(Dialog);
        freqRGA3->setObjectName(QString::fromUtf8("freqRGA3"));
        freqRGA3->setMinimumSize(QSize(59, 0));
        freqRGA3->setMaximumSize(QSize(59, 16777215));
        freqRGA3->setFont(font);

        horizontalLayout_19->addWidget(freqRGA3);


        verticalLayout->addLayout(horizontalLayout_19);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        labGPU = new QLabel(Dialog);
        labGPU->setObjectName(QString::fromUtf8("labGPU"));
        labGPU->setMinimumSize(QSize(38, 0));
        labGPU->setMaximumSize(QSize(38, 16777215));
        labGPU->setFont(font);

        horizontalLayout_12->addWidget(labGPU);

        barGPU = new QProgressBar(Dialog);
        barGPU->setObjectName(QString::fromUtf8("barGPU"));
        barGPU->setMinimumSize(QSize(0, 16));
        barGPU->setMaximumSize(QSize(16777215, 16));
        barGPU->setFont(font1);
        barGPU->setValue(0);

        horizontalLayout_12->addWidget(barGPU);

        freqGPU = new QLabel(Dialog);
        freqGPU->setObjectName(QString::fromUtf8("freqGPU"));
        freqGPU->setMinimumSize(QSize(59, 0));
        freqGPU->setMaximumSize(QSize(59, 16777215));
        freqGPU->setFont(font);

        horizontalLayout_12->addWidget(freqGPU);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        labMem = new QLabel(Dialog);
        labMem->setObjectName(QString::fromUtf8("labMem"));
        labMem->setMinimumSize(QSize(38, 0));
        labMem->setMaximumSize(QSize(38, 16777215));
        labMem->setFont(font);

        horizontalLayout_13->addWidget(labMem);

        barMem = new QProgressBar(Dialog);
        barMem->setObjectName(QString::fromUtf8("barMem"));
        barMem->setMinimumSize(QSize(0, 16));
        barMem->setMaximumSize(QSize(16777215, 16));
        barMem->setFont(font1);
        barMem->setValue(0);

        horizontalLayout_13->addWidget(barMem);

        freqMem = new QLabel(Dialog);
        freqMem->setObjectName(QString::fromUtf8("freqMem"));
        freqMem->setMinimumSize(QSize(59, 0));
        freqMem->setMaximumSize(QSize(59, 16777215));
        freqMem->setFont(font);

        horizontalLayout_13->addWidget(freqMem);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        labSwap = new QLabel(Dialog);
        labSwap->setObjectName(QString::fromUtf8("labSwap"));
        labSwap->setMinimumSize(QSize(38, 0));
        labSwap->setMaximumSize(QSize(38, 16777215));
        labSwap->setFont(font);

        horizontalLayout_14->addWidget(labSwap);

        barSwap = new QProgressBar(Dialog);
        barSwap->setObjectName(QString::fromUtf8("barSwap"));
        barSwap->setMinimumSize(QSize(0, 16));
        barSwap->setMaximumSize(QSize(16777215, 16));
        barSwap->setFont(font1);
        barSwap->setValue(0);

        horizontalLayout_14->addWidget(barSwap);

        freqSwap = new QLabel(Dialog);
        freqSwap->setObjectName(QString::fromUtf8("freqSwap"));
        freqSwap->setMinimumSize(QSize(59, 0));
        freqSwap->setMaximumSize(QSize(59, 16777215));
        freqSwap->setFont(font);

        horizontalLayout_14->addWidget(freqSwap);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(38, 0));
        label_5->setMaximumSize(QSize(38, 16777215));
        label_5->setFont(font);

        horizontalLayout_15->addWidget(label_5);

        barTemp = new QProgressBar(Dialog);
        barTemp->setObjectName(QString::fromUtf8("barTemp"));
        barTemp->setMinimumSize(QSize(0, 16));
        barTemp->setMaximumSize(QSize(16777215, 16));
        barTemp->setFont(font1);
        barTemp->setMinimum(20);
        barTemp->setMaximum(120);
        barTemp->setValue(24);

        horizontalLayout_15->addWidget(barTemp);

        freqTemp = new QLabel(Dialog);
        freqTemp->setObjectName(QString::fromUtf8("freqTemp"));
        freqTemp->setMinimumSize(QSize(59, 0));
        freqTemp->setMaximumSize(QSize(59, 16777215));
        freqTemp->setFont(font);

        horizontalLayout_15->addWidget(freqTemp);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(-1, -1, 0, 0);
        labFan = new QLabel(Dialog);
        labFan->setObjectName(QString::fromUtf8("labFan"));
        labFan->setMinimumSize(QSize(38, 0));
        labFan->setMaximumSize(QSize(38, 16777215));
        labFan->setFont(font);

        horizontalLayout_16->addWidget(labFan);

        barFan = new QProgressBar(Dialog);
        barFan->setObjectName(QString::fromUtf8("barFan"));
        barFan->setMinimumSize(QSize(0, 16));
        barFan->setMaximumSize(QSize(16777215, 16));
        barFan->setFont(font1);
        barFan->setValue(0);

        horizontalLayout_16->addWidget(barFan);

        freqFan = new QLabel(Dialog);
        freqFan->setObjectName(QString::fromUtf8("freqFan"));
        freqFan->setMinimumSize(QSize(59, 0));
        freqFan->setMaximumSize(QSize(59, 16777215));
        freqFan->setFont(font);

        horizontalLayout_16->addWidget(freqFan);


        verticalLayout->addLayout(horizontalLayout_16);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "rtop", nullptr));
        labCPU1->setText(QCoreApplication::translate("Dialog", "CPU 1", nullptr));
        barCPU1->setFormat(QCoreApplication::translate("Dialog", "%p%", nullptr));
        freqCPU1->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labCPU2->setText(QCoreApplication::translate("Dialog", "CPU 2", nullptr));
        barCPU2->setFormat(QCoreApplication::translate("Dialog", "%p%", nullptr));
        freqCPU2->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labCPU3->setText(QCoreApplication::translate("Dialog", "CPU 3", nullptr));
        barCPU3->setFormat(QCoreApplication::translate("Dialog", "%p%", nullptr));
        freqCPU3->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labCPU4->setText(QCoreApplication::translate("Dialog", "CPU 4", nullptr));
        barCPU4->setFormat(QCoreApplication::translate("Dialog", "%p%", nullptr));
        freqCPU4->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labCPU5->setText(QCoreApplication::translate("Dialog", "CPU 5", nullptr));
        barCPU5->setFormat(QCoreApplication::translate("Dialog", "%p%", nullptr));
        freqCPU5->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labCPU6->setText(QCoreApplication::translate("Dialog", "CPU 6", nullptr));
        barCPU6->setFormat(QCoreApplication::translate("Dialog", "%p%", nullptr));
        freqCPU6->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labCPU7->setText(QCoreApplication::translate("Dialog", "CPU 7", nullptr));
        freqCPU7->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labCPU8->setText(QCoreApplication::translate("Dialog", "CPU 8", nullptr));
        freqCPU8->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labNPU1->setText(QCoreApplication::translate("Dialog", "NPU 1", nullptr));
        freqNPU1->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labNPU2->setText(QCoreApplication::translate("Dialog", "NPU 2", nullptr));
        freqNPU2->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labNPU3->setText(QCoreApplication::translate("Dialog", "NPU 3", nullptr));
        freqNPU3->setText(QCoreApplication::translate("Dialog", "2.45 GHz", nullptr));
        labRGA1->setText(QCoreApplication::translate("Dialog", "RGA 1", nullptr));
        freqRGA1->setText(QCoreApplication::translate("Dialog", "0.72 GHz", nullptr));
        labRGA2->setText(QCoreApplication::translate("Dialog", "RGA 2", nullptr));
        freqRGA2->setText(QCoreApplication::translate("Dialog", "0.72 GHz", nullptr));
        labRGA3->setText(QCoreApplication::translate("Dialog", "RGA 3", nullptr));
        freqRGA3->setText(QCoreApplication::translate("Dialog", "0.72 GHz", nullptr));
        labGPU->setText(QCoreApplication::translate("Dialog", "GPU", nullptr));
        freqGPU->setText(QCoreApplication::translate("Dialog", "1.00 GHz", nullptr));
        labMem->setText(QCoreApplication::translate("Dialog", "Mem", nullptr));
        freqMem->setText(QCoreApplication::translate("Dialog", "4.10 GB", nullptr));
        labSwap->setText(QCoreApplication::translate("Dialog", "Swap", nullptr));
        freqSwap->setText(QCoreApplication::translate("Dialog", "3.12 GB", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "Temp", nullptr));
        barTemp->setFormat(QCoreApplication::translate("Dialog", "%v \302\260C", nullptr));
        freqTemp->setText(QCoreApplication::translate("Dialog", "123 \302\260F", nullptr));
        labFan->setText(QCoreApplication::translate("Dialog", "Fan", nullptr));
        freqFan->setText(QCoreApplication::translate("Dialog", "RPM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
