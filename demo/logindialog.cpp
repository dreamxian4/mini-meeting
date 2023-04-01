#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

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

