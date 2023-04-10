#include "setuserdialog.h"
#include "ui_setuserdialog.h"
#include<QIcon>
#include<QMessageBox>

SetUserDialog::SetUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetUserDialog),m_iconid(0)
{
    ui->setupUi(this);

    for(int i=0;i<36;i++){
        ui->cbx_icon->addItem(QIcon(QString(":/tx/%1.png").arg(i)),"");
    }
}

SetUserDialog::~SetUserDialog()
{
    delete ui;
}

void SetUserDialog::on_pb_commit_clicked()
{
    int iconid=ui->cbx_icon->currentIndex();
    QString name=ui->le_name->text();
    QString feeling=ui->le_feeling->text();

    //重复判断：如果之前的结果和现在一样，不发送包
    if(m_iconid==iconid && m_name==name && m_feeling==feeling)return;
    if(name.length()==0||name.length()>20){
        QMessageBox::about(this,"提示","昵称非法");
        return;
    }

    if(feeling.length()==0||feeling.length()>20){
        QMessageBox::about(this,"提示","签名非法");
        return;
    }
    this->hide();
    Q_EMIT SIG_userSetCommit( iconid, name,feeling);
    slot_setInfo(iconid,name,feeling);
}


void SetUserDialog::on_pb_clear_clicked()
{
    ui->le_feeling->setText("");
    ui->le_name->setText("");
}


void SetUserDialog::slot_setInfo(int iconid, QString name, QString feeling)
{
    m_iconid=iconid;
    m_name=name;
    m_feeling=feeling;

    ui->cbx_icon->setCurrentIndex(m_iconid);
    ui->le_name->setText(m_name);
    ui->le_feeling->setText(m_feeling);
}

