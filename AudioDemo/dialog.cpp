#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_audioRead=new AudioRead;
    m_audioWrite=new AudioWrite;

    connect(m_audioRead,SIGNAL(SIG_audioFrame(QByteArray)),
            m_audioWrite,SLOT(slot_net_rx(QByteArray)));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pb_start_clicked()
{
    m_audioRead->start();
}


void Dialog::on_pb_pause_clicked()
{
    m_audioRead->pause();
}

