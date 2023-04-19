#include "roomdialog.h"
#include "ui_roomdialog.h"

RoomDialog::RoomDialog(QWidget *parent) :
    CustomMoveDialog(parent),
    ui(new Ui::RoomDialog)
{
    ui->setupUi(this);
    m_userLayout=new QVBoxLayout;
    //用户列表垂直布局
    ui->wdg_userlist->setLayout(m_userLayout);

    //设置边距
    m_userLayout->setContentsMargins(0,0,0,0);
    m_userLayout->setSpacing(5);
    //通过addwidget添加控件
//    m_userLayout->addWidget();

//    //添加测试用户
//    UserShow* user1=new UserShow;
//    user1->slot_setInfo(1,"李四");
//    UserShow* user2=new UserShow;
//    user2->slot_setInfo(2,"王五");
//    UserShow* user3=new UserShow;
//    user3->slot_setInfo(3,"查理");
//    UserShow* user4=new UserShow;
//    user4->slot_setInfo(4,"章节");
//    UserShow* user5=new UserShow;
//    user5->slot_setInfo(5,"马克");
//    slot_addUser(user1);
//    slot_addUser(user2);
//    slot_addUser(user3);
//    slot_addUser(user4);
//    slot_addUser(user5);
}

RoomDialog::~RoomDialog()
{
    delete ui;
}

void RoomDialog::slot_setRoomID(int roomid)
{
    ui->lb_title->setText(QString("房间号：%1").arg(roomid));
}

void RoomDialog::slot_addUser(QWidget *user)
{
    m_userLayout->addWidget(user);
}

void RoomDialog::slot_removeUser(QWidget *user)
{
    user->hide();
    m_userLayout->removeWidget(user);
    delete user;
}

void RoomDialog::slot_setRoomClear()
{
    //设置ui
    ui->cb_audio->setChecked(false);
    ui->cb_capture->setChecked(false);
    ui->cb_desk->setChecked(false);
    //发信号
    Q_EMIT SIG_audioClose();
    Q_EMIT SIG_videoClose();
    Q_EMIT SIG_deskClose();
}

void RoomDialog::slot_setBigImage(int userid, QImage &img)
{
    if(ui->wdg_bigShow->m_id==userid){
        ui->wdg_bigShow->slot_setImage(img);
    }
}

void RoomDialog::slot_setBigImageInfo(int userid, QString name)
{
    ui->wdg_bigShow->slot_setInfo(userid,name);
    //也可以不通过信号发送id和名字
//    UserShow* user=(UserShow*)QObject::sender();//可以获取到信号发送者的对象，根据该对象可以获取其成员
}

void RoomDialog::on_pb_min_clicked()
{
    this->slot_showMin();
}


void RoomDialog::on_pb_max_clicked()
{
    this->slot_showMax();
}


void RoomDialog::on_pb_close_clicked()
{
    on_pb_quit_clicked();
}

//列表的显示和隐藏
void RoomDialog::on_pb_hide_clicked()
{
    if(ui->scrollArea->isHidden()){
        ui->scrollArea->show();
    }else{
        ui->scrollArea->hide();
    }
}

#include<QMessageBox>
//退出
void RoomDialog::on_pb_quit_clicked()
{
    if(QMessageBox::question(this,"tips","是否退出房间")==QMessageBox::Yes){
        Q_EMIT SIG_quitRoom();
        this->close();
    }
}

//音频勾选框
void RoomDialog::on_cb_audio_clicked()
{
    if(!ui->cb_audio->isChecked()){//判断是否被勾选
        //发送信号 RoomDialog ->ckernel(audio video) 关闭
        //RoomDialog->sig->ckernel->slot->audio 开关
        Q_EMIT SIG_audioClose();
    }else{
        //发送开启信号
        Q_EMIT SIG_audioOpen();
    }
}


//视频勾选框
void RoomDialog::on_cb_capture_clicked()
{
    if(!ui->cb_capture->isChecked()){
        //发信号
        //摄像头关闭
        Q_EMIT SIG_videoClose();
    }else{
        ui->cb_desk->setChecked(false);
        //发信号
        //摄像头开启 桌面关闭
        Q_EMIT SIG_deskClose();
        Q_EMIT SIG_videoOpen();
    }
}

//桌面采集
void RoomDialog::on_cb_desk_clicked()
{
    if(!ui->cb_desk->isChecked()){
        //发信号
        //桌面采集关闭
        Q_EMIT SIG_deskClose();
    }else{
        ui->cb_desk->setChecked(true);
        //发信号
        //桌面采集开启 摄像头关闭
        Q_EMIT SIG_videoClose();
        Q_EMIT SIG_deskOpen();
    }
}

