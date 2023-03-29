#include "demodialog.h"
#include "ui_demodialog.h"
#include<qDebug>

DemoDialog::DemoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DemoDialog)
{
    ui->setupUi(this);

    m_server=new TcpServerMediator;
    m_server->OpenNet("0.0.0.0",8080);
    connect(m_server,SIGNAL(SIG_ReadyData( unsigned int, char*, int)),
            this,SLOT(slot_serverReadData( unsigned int, char*, int)));

    m_client=new TcpClientMediator;
    m_client->OpenNet("10.51.220.155",8080);
    connect(m_client,SIGNAL(SIG_ReadyData( unsigned int, char*, int)),
            this,SLOT(slot_clientReadData( unsigned int, char*, int)));
}

DemoDialog::~DemoDialog()
{
    delete ui;
}

#include<QMessageBox>
void DemoDialog::slot_serverReadData(unsigned int socket, char *buf, int nlen)
{
    std::string st=buf;
    QString str=QString::fromStdString(st);
    str="来自client:"+str;
    QMessageBox::about(this,"提示",str);
    m_server->SendData(socket,buf,nlen);
    delete []buf;
}

void DemoDialog::slot_clientReadData(unsigned int socket, char *buf, int nlen)
{
    std::string st=buf;
    QString str=QString::fromStdString(st);
    str="来自server:"+str;
    QMessageBox::about(this,"提示",str);
    delete []buf;
}


#include<QString>
void DemoDialog::on_pushButton_clicked()
{
    QString str=ui->lineEdit->text();
    //QMessageBox::about(this,"提示",str);
    std::string strstd=str.toStdString();
    char* strbuf=(char*)strstd.c_str();
    m_client->SendData(0,strbuf,strlen(strbuf)+1);
}

