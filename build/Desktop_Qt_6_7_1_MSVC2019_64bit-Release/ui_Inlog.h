/********************************************************************************
** Form generated from reading UI file 'Inlog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INLOG_H
#define UI_INLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InLog
{
public:
    QCheckBox *checkBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Let_Name;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *Let_Passward;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Btn_In;
    QPushButton *Btn_Regis;
    QPushButton *Btn_Quit;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *InLog)
    {
        if (InLog->objectName().isEmpty())
            InLog->setObjectName("InLog");
        InLog->resize(492, 440);
        checkBox = new QCheckBox(InLog);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(340, 120, 98, 23));
        horizontalLayoutWidget = new QWidget(InLog);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(80, 70, 251, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        Let_Name = new QLineEdit(horizontalLayoutWidget);
        Let_Name->setObjectName("Let_Name");

        horizontalLayout->addWidget(Let_Name);

        horizontalLayoutWidget_2 = new QWidget(InLog);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(79, 110, 251, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        Let_Passward = new QLineEdit(horizontalLayoutWidget_2);
        Let_Passward->setObjectName("Let_Passward");

        horizontalLayout_2->addWidget(Let_Passward);

        horizontalLayoutWidget_3 = new QWidget(InLog);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(60, 140, 371, 80));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        Btn_In = new QPushButton(horizontalLayoutWidget_3);
        Btn_In->setObjectName("Btn_In");

        horizontalLayout_3->addWidget(Btn_In);

        Btn_Regis = new QPushButton(horizontalLayoutWidget_3);
        Btn_Regis->setObjectName("Btn_Regis");

        horizontalLayout_3->addWidget(Btn_Regis);

        Btn_Quit = new QPushButton(horizontalLayoutWidget_3);
        Btn_Quit->setObjectName("Btn_Quit");

        horizontalLayout_3->addWidget(Btn_Quit);

        label_3 = new QLabel(InLog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 330, 69, 19));
        label_4 = new QLabel(InLog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 491, 441));
        label_4->setStyleSheet(QString::fromUtf8("border-image: url(:/imgs/images/Stick.jpg);"));
        label_4->raise();
        checkBox->raise();
        horizontalLayoutWidget->raise();
        horizontalLayoutWidget_2->raise();
        horizontalLayoutWidget_3->raise();
        label_3->raise();

        retranslateUi(InLog);

        QMetaObject::connectSlotsByName(InLog);
    } // setupUi

    void retranslateUi(QWidget *InLog)
    {
        InLog->setWindowTitle(QCoreApplication::translate("InLog", "Form", nullptr));
        checkBox->setText(QCoreApplication::translate("InLog", "\346\230\276\347\244\272", nullptr));
        label->setText(QCoreApplication::translate("InLog", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("InLog", "\345\257\206    \347\240\201", nullptr));
        Btn_In->setText(QCoreApplication::translate("InLog", "\347\231\273\345\275\225", nullptr));
        Btn_Regis->setText(QCoreApplication::translate("InLog", "\346\263\250\345\206\214", nullptr));
        Btn_Quit->setText(QCoreApplication::translate("InLog", "\351\200\200\345\207\272", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InLog: public Ui_InLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INLOG_H
