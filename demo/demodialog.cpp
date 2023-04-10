#include "demodialog.h"
#include "ui_demodialog.h"
#include<QMessageBox>
#include<QDebug>


DemoDialog::DemoDialog(QWidget *parent)
    : CustomMoveDialog(parent)
    , ui(new Ui::DemoDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
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

//最小化
void DemoDialog::on_pb_min_clicked()
{
    this->showMinimized();
}

//关闭窗口
void DemoDialog::on_pb_close_clicked()
{
    this->close();
}

//加入会议
void DemoDialog::on_pb_join_clicked()
{
    Q_EMIT SIG_joinRoom();
}

//创建会议
void DemoDialog::on_pb_create_clicked()
{
    Q_EMIT SIG_createRoom();
}

//设置属性 成员+ui
void DemoDialog::slot_setInfo(int id, QString name)
{
    //成员
    m_name=name;
    m_iconid=id;
    //ui
    ui->lb_name->setText(m_name);
    ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(id)));
}


//设置个人信息
void DemoDialog::on_pb_icon_clicked()
{
    //发送信号
    Q_EMIT SIG_setUser();
}

