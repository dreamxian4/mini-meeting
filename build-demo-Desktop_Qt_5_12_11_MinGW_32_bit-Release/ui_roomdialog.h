/********************************************************************************
** Form generated from reading UI file 'roomdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMDIALOG_H
#define UI_ROOMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "usershow.h"

QT_BEGIN_NAMESPACE

class Ui_RoomDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *wdg_top;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_title;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_hide;
    QPushButton *pb_min;
    QPushButton *pb_max;
    QPushButton *pb_close;
    QWidget *wdg_mid;
    QHBoxLayout *horizontalLayout_3;
    UserShow *wdg_bigShow;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_userlist;
    QSpacerItem *verticalSpacer;
    QWidget *wdg_bottom;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *cb_capture;
    QCheckBox *cb_audio;
    QCheckBox *cb_desk;
    QLabel *lb_moji;
    QComboBox *cbx_moji;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_quit;

    void setupUi(QDialog *RoomDialog)
    {
        if (RoomDialog->objectName().isEmpty())
            RoomDialog->setObjectName(QString::fromUtf8("RoomDialog"));
        RoomDialog->resize(800, 600);
        RoomDialog->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(RoomDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        wdg_top = new QWidget(RoomDialog);
        wdg_top->setObjectName(QString::fromUtf8("wdg_top"));
        wdg_top->setMinimumSize(QSize(100, 50));
        wdg_top->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(wdg_top);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lb_title = new QLabel(wdg_top);
        lb_title->setObjectName(QString::fromUtf8("lb_title"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223"));
        font.setPointSize(12);
        lb_title->setFont(font);

        horizontalLayout->addWidget(lb_title);

        horizontalSpacer = new QSpacerItem(474, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_hide = new QPushButton(wdg_top);
        pb_hide->setObjectName(QString::fromUtf8("pb_hide"));
        pb_hide->setMinimumSize(QSize(30, 30));
        pb_hide->setMaximumSize(QSize(30, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        pb_hide->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_hide->setIcon(icon);
        pb_hide->setFlat(true);

        horizontalLayout->addWidget(pb_hide);

        pb_min = new QPushButton(wdg_top);
        pb_min->setObjectName(QString::fromUtf8("pb_min"));
        pb_min->setMinimumSize(QSize(30, 30));
        pb_min->setMaximumSize(QSize(30, 30));
        pb_min->setFont(font1);
        pb_min->setFlat(true);

        horizontalLayout->addWidget(pb_min);

        pb_max = new QPushButton(wdg_top);
        pb_max->setObjectName(QString::fromUtf8("pb_max"));
        pb_max->setMinimumSize(QSize(30, 30));
        pb_max->setMaximumSize(QSize(30, 30));
        pb_max->setFont(font1);
        pb_max->setFlat(true);

        horizontalLayout->addWidget(pb_max);

        pb_close = new QPushButton(wdg_top);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setMinimumSize(QSize(30, 30));
        pb_close->setMaximumSize(QSize(30, 30));
        pb_close->setFont(font1);
        pb_close->setFlat(true);

        horizontalLayout->addWidget(pb_close);


        verticalLayout->addWidget(wdg_top);

        wdg_mid = new QWidget(RoomDialog);
        wdg_mid->setObjectName(QString::fromUtf8("wdg_mid"));
        horizontalLayout_3 = new QHBoxLayout(wdg_mid);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, 0, -1, 0);
        wdg_bigShow = new UserShow(wdg_mid);
        wdg_bigShow->setObjectName(QString::fromUtf8("wdg_bigShow"));

        horizontalLayout_3->addWidget(wdg_bigShow);

        scrollArea = new QScrollArea(wdg_mid);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(200, 0));
        scrollArea->setMaximumSize(QSize(200, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 198, 498));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        wdg_userlist = new QWidget(scrollAreaWidgetContents);
        wdg_userlist->setObjectName(QString::fromUtf8("wdg_userlist"));

        verticalLayout_2->addWidget(wdg_userlist);

        verticalSpacer = new QSpacerItem(20, 485, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(scrollArea);


        verticalLayout->addWidget(wdg_mid);

        wdg_bottom = new QWidget(RoomDialog);
        wdg_bottom->setObjectName(QString::fromUtf8("wdg_bottom"));
        wdg_bottom->setMinimumSize(QSize(100, 50));
        wdg_bottom->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_2 = new QHBoxLayout(wdg_bottom);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cb_capture = new QCheckBox(wdg_bottom);
        cb_capture->setObjectName(QString::fromUtf8("cb_capture"));

        horizontalLayout_2->addWidget(cb_capture);

        cb_audio = new QCheckBox(wdg_bottom);
        cb_audio->setObjectName(QString::fromUtf8("cb_audio"));

        horizontalLayout_2->addWidget(cb_audio);

        cb_desk = new QCheckBox(wdg_bottom);
        cb_desk->setObjectName(QString::fromUtf8("cb_desk"));

        horizontalLayout_2->addWidget(cb_desk);

        lb_moji = new QLabel(wdg_bottom);
        lb_moji->setObjectName(QString::fromUtf8("lb_moji"));

        horizontalLayout_2->addWidget(lb_moji);

        cbx_moji = new QComboBox(wdg_bottom);
        cbx_moji->addItem(QString());
        cbx_moji->addItem(QString());
        cbx_moji->addItem(QString());
        cbx_moji->setObjectName(QString::fromUtf8("cbx_moji"));

        horizontalLayout_2->addWidget(cbx_moji);

        horizontalSpacer_2 = new QSpacerItem(289, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pb_quit = new QPushButton(wdg_bottom);
        pb_quit->setObjectName(QString::fromUtf8("pb_quit"));

        horizontalLayout_2->addWidget(pb_quit);


        verticalLayout->addWidget(wdg_bottom);


        retranslateUi(RoomDialog);

        QMetaObject::connectSlotsByName(RoomDialog);
    } // setupUi

    void retranslateUi(QDialog *RoomDialog)
    {
        RoomDialog->setWindowTitle(QApplication::translate("RoomDialog", "Dialog", nullptr));
        lb_title->setText(QApplication::translate("RoomDialog", "\346\210\277\351\227\264\345\217\267\357\274\232000000", nullptr));
        pb_hide->setText(QString());
        pb_min->setText(QApplication::translate("RoomDialog", "\344\270\200", nullptr));
        pb_max->setText(QApplication::translate("RoomDialog", "\345\217\243", nullptr));
        pb_close->setText(QApplication::translate("RoomDialog", "X", nullptr));
        cb_capture->setText(QApplication::translate("RoomDialog", "\346\221\204\345\203\217\345\244\264", nullptr));
        cb_audio->setText(QApplication::translate("RoomDialog", "\351\272\246\345\205\213\351\243\216", nullptr));
        cb_desk->setText(QApplication::translate("RoomDialog", "\346\241\214\351\235\242\351\207\207\351\233\206", nullptr));
        lb_moji->setText(QApplication::translate("RoomDialog", "\346\273\244\351\225\234", nullptr));
        cbx_moji->setItemText(0, QApplication::translate("RoomDialog", "\346\227\240", nullptr));
        cbx_moji->setItemText(1, QApplication::translate("RoomDialog", "\345\205\224\345\255\220\350\200\263\346\234\265", nullptr));
        cbx_moji->setItemText(2, QApplication::translate("RoomDialog", "\345\234\243\350\257\236\345\270\275\345\255\220", nullptr));

        pb_quit->setText(QApplication::translate("RoomDialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoomDialog: public Ui_RoomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMDIALOG_H
