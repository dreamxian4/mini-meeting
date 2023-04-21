/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *lb_icon;
    QTabWidget *tabWidget;
    QWidget *page_login;
    QLineEdit *le_passwd;
    QPushButton *pb_clear;
    QLabel *lb_tel;
    QPushButton *pb_commit;
    QLabel *lb_passwd;
    QLineEdit *le_tel;
    QWidget *tab_3;
    QLineEdit *le_passwd_register;
    QLabel *lb_tel_register;
    QLabel *lb_passwd_register;
    QPushButton *pb_clear_register;
    QLineEdit *le_tel_register;
    QPushButton *pb_commit_register;
    QLineEdit *le_confirm_passwd;
    QLabel *lb_comfirm_passwd;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(584, 239);
        LoginDialog->setMinimumSize(QSize(584, 239));
        LoginDialog->setMaximumSize(QSize(584, 239));
        lb_icon = new QLabel(LoginDialog);
        lb_icon->setObjectName(QString::fromUtf8("lb_icon"));
        lb_icon->setGeometry(QRect(20, 20, 211, 201));
        lb_icon->setAutoFillBackground(false);
        lb_icon->setPixmap(QPixmap(QString::fromUtf8(":/images/hat.png")));
        lb_icon->setScaledContents(false);
        tabWidget = new QTabWidget(LoginDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(240, 10, 341, 221));
        page_login = new QWidget();
        page_login->setObjectName(QString::fromUtf8("page_login"));
        le_passwd = new QLineEdit(page_login);
        le_passwd->setObjectName(QString::fromUtf8("le_passwd"));
        le_passwd->setGeometry(QRect(80, 90, 231, 31));
        le_passwd->setEchoMode(QLineEdit::Password);
        pb_clear = new QPushButton(page_login);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(80, 130, 93, 28));
        lb_tel = new QLabel(page_login);
        lb_tel->setObjectName(QString::fromUtf8("lb_tel"));
        lb_tel->setGeometry(QRect(20, 60, 51, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\345\275\251\344\272\221"));
        font.setPointSize(10);
        lb_tel->setFont(font);
        pb_commit = new QPushButton(page_login);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(220, 130, 93, 28));
        lb_passwd = new QLabel(page_login);
        lb_passwd->setObjectName(QString::fromUtf8("lb_passwd"));
        lb_passwd->setGeometry(QRect(30, 100, 41, 16));
        lb_passwd->setFont(font);
        le_tel = new QLineEdit(page_login);
        le_tel->setObjectName(QString::fromUtf8("le_tel"));
        le_tel->setGeometry(QRect(80, 50, 231, 31));
        le_tel->setEchoMode(QLineEdit::Normal);
        tabWidget->addTab(page_login, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        le_passwd_register = new QLineEdit(tab_3);
        le_passwd_register->setObjectName(QString::fromUtf8("le_passwd_register"));
        le_passwd_register->setGeometry(QRect(80, 60, 231, 31));
        le_passwd_register->setEchoMode(QLineEdit::Password);
        lb_tel_register = new QLabel(tab_3);
        lb_tel_register->setObjectName(QString::fromUtf8("lb_tel_register"));
        lb_tel_register->setGeometry(QRect(20, 30, 51, 16));
        lb_tel_register->setFont(font);
        lb_passwd_register = new QLabel(tab_3);
        lb_passwd_register->setObjectName(QString::fromUtf8("lb_passwd_register"));
        lb_passwd_register->setGeometry(QRect(30, 70, 41, 16));
        lb_passwd_register->setFont(font);
        pb_clear_register = new QPushButton(tab_3);
        pb_clear_register->setObjectName(QString::fromUtf8("pb_clear_register"));
        pb_clear_register->setGeometry(QRect(80, 140, 93, 28));
        le_tel_register = new QLineEdit(tab_3);
        le_tel_register->setObjectName(QString::fromUtf8("le_tel_register"));
        le_tel_register->setGeometry(QRect(80, 20, 231, 31));
        le_tel_register->setEchoMode(QLineEdit::Normal);
        pb_commit_register = new QPushButton(tab_3);
        pb_commit_register->setObjectName(QString::fromUtf8("pb_commit_register"));
        pb_commit_register->setGeometry(QRect(220, 140, 93, 28));
        le_confirm_passwd = new QLineEdit(tab_3);
        le_confirm_passwd->setObjectName(QString::fromUtf8("le_confirm_passwd"));
        le_confirm_passwd->setGeometry(QRect(80, 100, 231, 31));
        le_confirm_passwd->setEchoMode(QLineEdit::Password);
        lb_comfirm_passwd = new QLabel(tab_3);
        lb_comfirm_passwd->setObjectName(QString::fromUtf8("lb_comfirm_passwd"));
        lb_comfirm_passwd->setGeometry(QRect(30, 110, 41, 16));
        lb_comfirm_passwd->setFont(font);
        tabWidget->addTab(tab_3, QString());
        QWidget::setTabOrder(tabWidget, le_tel);
        QWidget::setTabOrder(le_tel, le_passwd);
        QWidget::setTabOrder(le_passwd, pb_commit);
        QWidget::setTabOrder(pb_commit, pb_clear);
        QWidget::setTabOrder(pb_clear, le_tel_register);
        QWidget::setTabOrder(le_tel_register, le_passwd_register);
        QWidget::setTabOrder(le_passwd_register, le_confirm_passwd);
        QWidget::setTabOrder(le_confirm_passwd, pb_commit_register);
        QWidget::setTabOrder(pb_commit_register, pb_clear_register);

        retranslateUi(LoginDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", nullptr));
        lb_icon->setText(QString());
        le_passwd->setText(QApplication::translate("LoginDialog", "1", nullptr));
        pb_clear->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        lb_tel->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", nullptr));
        pb_commit->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
        lb_passwd->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        le_tel->setText(QApplication::translate("LoginDialog", "13412341234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(page_login), QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        lb_tel_register->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", nullptr));
        lb_passwd_register->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        pb_clear_register->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        pb_commit_register->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
#ifndef QT_NO_TOOLTIP
        le_confirm_passwd->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\345\206\215\346\254\241\347\241\256\350\256\244\345\257\206\347\240\201</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        le_confirm_passwd->setText(QString());
        lb_comfirm_passwd->setText(QApplication::translate("LoginDialog", "\347\241\256\350\256\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
