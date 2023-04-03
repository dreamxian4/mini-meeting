#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"TcpClientMediator.h"
#include"TcpServerMediator.h"
#include<QCloseEvent>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void SIG_close();
    //定义登录、注册提交信号
    void SIG_loginCommit(QString tel,QString passwd);
    void SIG_registerCommit(QString tel,QString passwd);

public:
    void closeEvent(QCloseEvent * event);




private slots:
    void on_pb_clear_register_clicked();

    void on_pb_clear_clicked();

    void on_pb_commit_clicked();

    void on_pb_commit_register_clicked();



private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
