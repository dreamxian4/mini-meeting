#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    m_server=new TcpServerMediator;
    m_server->OpenNet("0.0.0.0",8080);
    connect(m_server,SIGNAL(SIG_ReadyData( unsigned int, char*, int)),
            this,SLOT(slot_serverReadData( unsigned int, char*, int)));

    m_client=new TcpClientMediator;
    m_client->OpenNet("10.50.83.193",8080);
    connect(m_client,SIGNAL(SIG_ReadyData( unsigned int, char*, int)),
            this,SLOT(slot_clientReadData( unsigned int, char*, int)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::slot_serverReadData(unsigned int socket, char *buf, int nlen)
{
    std::string st=buf;
    QString str=QString::fromStdString(st);
    str="来自client:"+str;
    QMessageBox::about(this,"提示",str);
    m_server->SendData(socket,buf,nlen);
    delete []buf;
}

void LoginDialog::slot_clientReadData(unsigned int socket, char *buf, int nlen)
{
    std::string st=buf;
    QString str=QString::fromStdString(st);
    str="来自server:"+str;
    QMessageBox::about(this,"提示",str);
    delete []buf;
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


#include<QString>
void LoginDialog::on_pushButton_clicked()
{
    QMessageBox::about(this,"提示","安乐");
}
