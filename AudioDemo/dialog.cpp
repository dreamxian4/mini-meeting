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

    m_videoRead=new VideoRead;
//    connect(m_videoRead,SIGNAL(SIG_videoFrame(QImage)),
//            this,SLOT(slot_showImage(QImage)));
    connect(m_videoRead,SIGNAL(SIG_videoFrame(QImage)),
                ui->wdg_videoShow,SLOT(slot_setImage(QImage)));
//    connect(m_videoRead,SIGNAL(SIG_videoFrameData(QByteArray)),
//            this,SLOT(slot_showImageFromData(QByteArray)));

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
    qDebug()<<"pause";
    m_audioRead->pause();
}


void Dialog::on_pushButton_2_clicked()
{
    qDebug()<<"pause";
    m_audioRead->pause();
}


void Dialog::on_pb_start_2_clicked()
{
    m_videoRead->start();
}

void Dialog::slot_showImage(QImage img)
{
    //显示到label
    ui->lb_video->setPixmap(QPixmap::fromImage(img));
}

void Dialog::slot_showImageFromData(QByteArray ba)
{
    QImage img;
    img.loadFromData( ba );
    //可以使用 img 来显示图片
    //显示到label
    ui->lb_video->setPixmap(QPixmap::fromImage(img));
}


void Dialog::on_pb_pause_2_clicked()
{
    m_videoRead->pause();
}

