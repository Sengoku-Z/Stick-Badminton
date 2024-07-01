/********************************************************************************
** Form generated from reading UI file 'Regis.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGIS_H
#define UI_REGIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Regis
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Let_Name;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *Let_Passward_1;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *Btn_Quit;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *Let_Passward_2;
    QLabel *label_4;

    void setupUi(QWidget *Regis)
    {
        if (Regis->objectName().isEmpty())
            Regis->setObjectName("Regis");
        Regis->resize(439, 408);
        horizontalLayoutWidget = new QWidget(Regis);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(90, 80, 251, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        Let_Name = new QLineEdit(horizontalLayoutWidget);
        Let_Name->setObjectName("Let_Name");

        horizontalLayout->addWidget(Let_Name);

        horizontalLayoutWidget_2 = new QWidget(Regis);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(89, 120, 251, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        Let_Passward_1 = new QLineEdit(horizontalLayoutWidget_2);
        Let_Passward_1->setObjectName("Let_Passward_1");

        horizontalLayout_2->addWidget(Let_Passward_1);

        horizontalLayoutWidget_3 = new QWidget(Regis);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(70, 170, 295, 80));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(horizontalLayoutWidget_3);
        pushButton->setObjectName("pushButton");

        horizontalLayout_3->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        Btn_Quit = new QPushButton(horizontalLayoutWidget_3);
        Btn_Quit->setObjectName("Btn_Quit");

        horizontalLayout_3->addWidget(Btn_Quit);

        horizontalLayoutWidget_4 = new QWidget(Regis);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(90, 150, 251, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_4);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        Let_Passward_2 = new QLineEdit(horizontalLayoutWidget_4);
        Let_Passward_2->setObjectName("Let_Passward_2");

        horizontalLayout_4->addWidget(Let_Passward_2);

        label_4 = new QLabel(Regis);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 441, 411));
        label_4->setStyleSheet(QString::fromUtf8("border-image: url(:/imgs/images/Stick.jpg);"));
        label_4->raise();
        horizontalLayoutWidget->raise();
        horizontalLayoutWidget_2->raise();
        horizontalLayoutWidget_3->raise();
        horizontalLayoutWidget_4->raise();

        retranslateUi(Regis);

        QMetaObject::connectSlotsByName(Regis);
    } // setupUi

    void retranslateUi(QWidget *Regis)
    {
        Regis->setWindowTitle(QCoreApplication::translate("Regis", "Form", nullptr));
        label->setText(QCoreApplication::translate("Regis", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("Regis", "\345\257\206    \347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("Regis", "\346\263\250\345\206\214", nullptr));
        Btn_Quit->setText(QCoreApplication::translate("Regis", "\351\200\200\345\207\272", nullptr));
        label_3->setText(QCoreApplication::translate("Regis", "\351\207\215\350\276\223\345\205\245", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Regis: public Ui_Regis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGIS_H
