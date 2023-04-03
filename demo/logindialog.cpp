#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
#include<QRegExp>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    on_pb_clear_register_clicked();
    on_pb_clear_clicked();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::closeEvent(QCloseEvent * event)
{
    if(QMessageBox::question(this,"提示","是否关闭？")==QMessageBox::Yes){
        //关闭
        Q_EMIT SIG_close();
    }else{
        //忽略
        event->ignore();
    }
}

//注册清空
void LoginDialog::on_pb_clear_register_clicked()
{
    ui->le_confirm_passwd->setText("");
    ui->le_passwd_register->setText("");
    ui->le_tel_register->setText("");
}

//登录清空
void LoginDialog::on_pb_clear_clicked()
{
    ui->le_tel->setText("");
    ui->le_passwd->setText("");
}

//登录提交
void LoginDialog::on_pb_commit_clicked()
{
    QString strTel=ui->le_tel->text();
    QString strPasswd=ui->le_passwd->text();
    //合法化的过滤
    //非空
    if(strTel.isEmpty()||strPasswd.isEmpty()){
        QMessageBox::about(this,"提示","输入不能为空^_^");
        return;
    }
    //手机号验证1[3-8][0-9]9位 正则
    QRegExp reg("^1[3-8][0-9]{9}$");
    bool res=reg.exactMatch(strTel);
    if(!res){
        QMessageBox::about(this,"提示","手机号不合法QAQ");
        return;
    }
    //密码合法化：长度不超过20
    if(strPasswd.length()>20){
        QMessageBox::about(this,"提示","密码太长啦，不能超过二十~");
        return;
    }
    //得到最终的tel passwd

    //发送信号
    Q_EMIT SIG_loginCommit(strTel,strPasswd);
}

//注册提交
void LoginDialog::on_pb_commit_register_clicked()
{
    QString strTel=ui->le_tel_register->text();
    QString strPasswd=ui->le_passwd_register->text();
    QString strConfirm=ui->le_confirm_passwd->text();
    //合法化的过滤
    //非空
    if(strTel.isEmpty()||strPasswd.isEmpty()||strConfirm.isEmpty()){
        QMessageBox::about(this,"提示","输入不能为空^_^");
        return;
    }
    //手机号验证1[3-8][0-9]9位 正则
    QRegExp reg("^1[3-8][0-9]{9}$");
    bool res=reg.exactMatch(strTel);
    if(!res){
        QMessageBox::about(this,"提示","手机号不合法QAQ");
        return;
    }
    //密码合法化：长度不超过20
    if(strPasswd.length()>20){
        QMessageBox::about(this,"提示","密码太长啦，不能超过二十~");
        return;
    }
    //两次确认，要一致
    if(strPasswd!=strConfirm){
        QMessageBox::about(this,"提示","两次密码不一致");
        return;
    }
    //得到最终的tel passwd

    //发送信号
    Q_EMIT SIG_registerCommit(strTel,strPasswd);
}

