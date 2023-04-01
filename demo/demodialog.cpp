#include "demodialog.h"
#include "ui_demodialog.h"
#include<QMessageBox>


DemoDialog::DemoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DemoDialog)
{
    ui->setupUi(this);


}

DemoDialog::~DemoDialog()
{
    delete ui;
}

void DemoDialog::closeEvent(QCloseEvent * event)
{
    if(QMessageBox::question(this,"提示","是否关闭？")==QMessageBox::Yes){
        //关闭
        Q_EMIT SIG_close();
    }else{
        //忽略
        event->ignore();
    }
}
