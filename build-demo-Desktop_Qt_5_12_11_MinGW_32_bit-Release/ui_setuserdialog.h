/********************************************************************************
** Form generated from reading UI file 'setuserdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUSERDIALOG_H
#define UI_SETUSERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetUserDialog
{
public:
    QPushButton *pb_clear;
    QPushButton *pb_commit;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *lb_icon;
    QComboBox *cbx_icon;
    QLabel *lb_name;
    QLineEdit *le_name;
    QLabel *lb_feeling;
    QLineEdit *le_feeling;

    void setupUi(QDialog *SetUserDialog)
    {
        if (SetUserDialog->objectName().isEmpty())
            SetUserDialog->setObjectName(QString::fromUtf8("SetUserDialog"));
        SetUserDialog->resize(403, 292);
        SetUserDialog->setMinimumSize(QSize(403, 292));
        SetUserDialog->setMaximumSize(QSize(403, 292));
        pb_clear = new QPushButton(SetUserDialog);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(30, 250, 93, 28));
        pb_commit = new QPushButton(SetUserDialog);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(300, 250, 93, 28));
        layoutWidget = new QWidget(SetUserDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 361, 211));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lb_icon = new QLabel(layoutWidget);
        lb_icon->setObjectName(QString::fromUtf8("lb_icon"));
        lb_icon->setMinimumSize(QSize(0, 31));
        lb_icon->setMaximumSize(QSize(16777215, 31));

        gridLayout->addWidget(lb_icon, 0, 0, 1, 1);

        cbx_icon = new QComboBox(layoutWidget);
        cbx_icon->setObjectName(QString::fromUtf8("cbx_icon"));
        cbx_icon->setMinimumSize(QSize(81, 71));
        cbx_icon->setMaximumSize(QSize(81, 71));
        cbx_icon->setIconSize(QSize(60, 60));

        gridLayout->addWidget(cbx_icon, 0, 1, 1, 1);

        lb_name = new QLabel(layoutWidget);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setMinimumSize(QSize(0, 31));
        lb_name->setMaximumSize(QSize(16777215, 31));

        gridLayout->addWidget(lb_name, 1, 0, 1, 1);

        le_name = new QLineEdit(layoutWidget);
        le_name->setObjectName(QString::fromUtf8("le_name"));
        le_name->setMinimumSize(QSize(0, 30));
        le_name->setMaximumSize(QSize(16777215, 30));
        le_name->setClearButtonEnabled(true);

        gridLayout->addWidget(le_name, 1, 1, 1, 1);

        lb_feeling = new QLabel(layoutWidget);
        lb_feeling->setObjectName(QString::fromUtf8("lb_feeling"));
        lb_feeling->setMinimumSize(QSize(0, 31));
        lb_feeling->setMaximumSize(QSize(16777215, 31));

        gridLayout->addWidget(lb_feeling, 2, 0, 1, 1);

        le_feeling = new QLineEdit(layoutWidget);
        le_feeling->setObjectName(QString::fromUtf8("le_feeling"));
        le_feeling->setMinimumSize(QSize(0, 30));
        le_feeling->setMaximumSize(QSize(16777215, 30));
        le_feeling->setClearButtonEnabled(true);

        gridLayout->addWidget(le_feeling, 2, 1, 1, 1);


        retranslateUi(SetUserDialog);

        QMetaObject::connectSlotsByName(SetUserDialog);
    } // setupUi

    void retranslateUi(QDialog *SetUserDialog)
    {
        SetUserDialog->setWindowTitle(QApplication::translate("SetUserDialog", "Dialog", nullptr));
        pb_clear->setText(QApplication::translate("SetUserDialog", "\346\270\205\347\251\272", nullptr));
        pb_commit->setText(QApplication::translate("SetUserDialog", "\346\217\220\344\272\244", nullptr));
        lb_icon->setText(QApplication::translate("SetUserDialog", "\345\244\264\345\203\217", nullptr));
        lb_name->setText(QApplication::translate("SetUserDialog", "\346\230\265\347\247\260", nullptr));
        lb_feeling->setText(QApplication::translate("SetUserDialog", "\347\255\276\345\220\215", nullptr));
        le_feeling->setText(QApplication::translate("SetUserDialog", "\346\257\224\350\276\203\346\207\222\357\274\214\344\273\200\344\271\210\344\271\237\346\262\241\345\206\231\343\200\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetUserDialog: public Ui_SetUserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUSERDIALOG_H
