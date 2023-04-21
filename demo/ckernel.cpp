#include "ckernel.h"
#include<qDebug>
#include<QSettings>
#include<QApplication>
#include<QFileInfo>
#include<string>
#include<QInputDialog>
#include"md5.h"

using namespace std;

#define netMap(a) m_netMap[a-_DEF_PACK_BASE]
#define MD5_KEY 1234

/// 拼凑规则：
/// passwd_1234
/// \brief GetMD5
/// \param str
/// \return

static std::string GetMD5(QString str){
    std::string tmp=QString("%1_%2").arg(str).arg(MD5_KEY).toStdString();
    MD5 md5(tmp);
    return md5.toString();
}

CKernel::CKernel(QObject *parent) : QObject(parent),m_userid(0),m_roomid(0)
  ,m_sendVideo(new SendThread)
{
    qDebug()<<"main:"<<QThread::currentThreadId();
    initConfig();
    setNetMap();

    m_client=new TcpClientMediator;
    //av初始化 连接
    for(int i=0;i<2;i++){
        m_tcpAV[i]=new TcpClientMediator;
        connect(m_tcpAV[i],SIGNAL(SIG_ReadyData(unsigned int,char*,int)),
                this,SLOT(slot_DealData(unsigned int,char*,int)));

        if(!m_tcpAV[i]->OpenNet(m_serverIp.toStdString().c_str(),8080)){
            QMessageBox::about(this->m_login,"提示","服务器连接失败~~~");
            exit(0);
        }
    }

    m_login=new LoginDialog;
    m_login->show();
    m_main=new DemoDialog;
    m_room=new RoomDialog;
    m_setUser=new SetUserDialog;
    m_audioRead=new AudioRead;
    m_videoRead=new VideoRead;
    m_deskRead=new DeskRead;
    //打开网络
    if(!m_client->OpenNet(m_serverIp.toStdString().c_str(),8080)){
        QMessageBox::about(this->m_login,"提示","服务器连接失败~~~");
        exit(0);
    }
    //连接收到信息和处理槽
    connect(m_client,SIGNAL(SIG_ReadyData(unsigned int,char*,int)),
            this,SLOT(slot_DealData(unsigned int,char*,int)));

    //连接关闭信号和销毁槽
    connect(m_login,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));
    connect(m_login,SIGNAL(SIG_loginCommit(QString,QString)),
            this,SLOT(slot_loginCommit(QString,QString)));
    connect(m_login,SIGNAL(SIG_registerCommit(QString,QString)),
            this,SLOT(slot_registerCommit(QString,QString)));

    //连接关闭信号和销毁槽
    connect(m_main,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));
    connect(m_main,SIGNAL(SIG_joinRoom()),
            this,SLOT(slot_joinRoom()));
    connect(m_main,SIGNAL(SIG_createRoom()),
            this,SLOT(slot_createRoom()));
    connect(m_main,SIGNAL(SIG_setUser()),
            this,SLOT(slot_setUser()));



    connect(m_room,SIGNAL(SIG_quitRoom()),
            this,SLOT(slot_quitRoom()));


    connect(m_setUser,SIGNAL(SIG_userSetCommit(int,QString,QString)),
            this,SLOT(slot_userSetCommit(int,QString,QString)));

    connect(m_audioRead,SIGNAL(SIG_audioFrame(QByteArray&)),
            this,SLOT(slot_sendAudioFrame(QByteArray&)));
    connect(m_videoRead,SIGNAL(SIG_videoFrame(QImage&)),
            this,SLOT(slot_refreshVideoImage(QImage&)));
    connect(m_videoRead,SIGNAL(SIG_videoFrameData(QByteArray&)),
            this,SLOT(slot_sendVideoFrameData(QByteArray&)));
    connect(m_deskRead,SIGNAL(SIG_screenFrame(QImage&)),
            this,SLOT(slot_refreshVideoImage(QImage&)));
    connect(m_deskRead,SIGNAL(SIG_screenFrameData(QByteArray&)),
            this,SLOT(slot_sendVideoFrameData(QByteArray&)));
    connect(m_room,SIGNAL(SIG_audioOpen()),
            this,SLOT(slot_audioOpen()));
    connect(m_room,SIGNAL(SIG_audioClose()),
            this,SLOT(slot_audioClose()));
    connect(m_room,SIGNAL(SIG_videoOpen()),
            this,SLOT(slot_videoOpen()));
    connect(m_room,SIGNAL(SIG_videoClose()),
            this,SLOT(slot_videoClose()));
    connect(m_room,SIGNAL(SIG_deskOpen()),
            this,SLOT(slot_deskOpen()));
    connect(m_room,SIGNAL(SIG_deskClose()),
            this,SLOT(slot_deskClose()));
    connect(m_room,SIGNAL(SIG_setFunnyPic(int)),
            this,SLOT(slot_setFunnyPic(int)));

    connect(this,SIGNAL(SIG_sendVideoFrame(uint,char*,int)),
            m_sendVideo.get(),SLOT(slot_threadSendData(uint,char*,int)));
}

CKernel::~CKernel()
{

}

void CKernel::slot_destroy()
{
    if(m_main){
        m_main->hide();
        delete m_main;
        m_main=NULL;
    }
    if(m_login){
        m_login->hide();
        delete m_login;
        m_login=NULL;
    }
    if(m_room){
        m_room->hide();
        delete m_room;
        m_room=NULL;
    }
    if(m_setUser){
        m_setUser->hide();
        delete m_setUser;
        m_setUser=NULL;
    }
    if(m_audioRead){
        delete m_audioRead;
        m_audioRead=nullptr;
    }
    if(m_videoRead){
        delete m_videoRead;
        m_videoRead=nullptr;
    }
    if(m_client){
        m_client->CloseNet();
        delete m_client;
        m_client=NULL;
    }
}

//初始化配置
void CKernel::initConfig()
{
    m_serverIp=_DEF_SERVER_IP;
    //路径设置 exe同级目录下->applicationDiePath(获取.exe所在文件夹的绝对路径绝对路径) config.ini
    QString path=QApplication::applicationDirPath()+"/config.ini";
    //判断配置文件是否存在
    QFileInfo info(path);
    //打开配置文件:存在打开，不存在创建
    QSettings settings(path,QSettings::IniFormat,NULL);
    if(info.exists()){
        //文件存在 加载配置文件 获取其中的ip
        //移动到Net组
        settings.beginGroup("Net");
        //读取ip->addr-->赋值
        QVariant ip=settings.value("ip");
        QString strIP=ip.toString();
        //结束
        settings.endGroup();
        if(!strIP.isEmpty()){
            m_serverIp=strIP;
        }
    }else{
        //没有配置文件，写入默认的ip
        settings.beginGroup("Net");
        settings.setValue("ip",m_serverIp);
        settings.endGroup();
    }
    qDebug()<<m_serverIp;
}

//设置协议
void CKernel::setNetMap()
{
    memset(m_netMap,0,sizeof(PFUN));
    netMap(_DEF_PACK_LOGIN_RS)=&CKernel::slot_DealLoginRs;
    netMap(_DEF_PACK_REGISTER_RS)=&CKernel::slot_DealRegisterRs;
    netMap(DEF_PACK_CREATEROOM_RS)=&CKernel::slot_DealCreateRoomRs;
    netMap(DEF_PACK_JOINROOM_RS)=&CKernel::slot_DealJoinRoomRs;
    netMap(DEF_PACK_ROOM_MEMBER)=&CKernel::slot_DealroomMemberRq;
    netMap(DEF_PACK_USER_INFO)=&CKernel::slot_DealUserInfoRq;
    netMap(DEF_PACK_LEAVEROOM_RQ)=&CKernel::slot_DealLeaveRoomRq;
    netMap(DEF_PACK_AUDIO_FRAME)=&CKernel::slot_DealAudioFrameRq;
    netMap(DEF_PACK_VIDEO_FRAME)=&CKernel::slot_DealVideoFrameRq;
}

//网络数据
//处理数据
void CKernel::slot_DealData(unsigned int socket, char *buf, int nlen){
    int type=*(int*)buf;
    if(type>=_DEF_PACK_BASE&&type<_DEF_PACK_BASE+_DEF_PROTOCOL_COUNT){
        PFUN p=netMap(type);
        if(p) (this->*p)(socket,buf,nlen);
    }
    delete []buf;
}

//处理登录回复
void CKernel::slot_DealLoginRs(unsigned int socket, char *buf, int nlen)
{
    //拆包
    STRU_LOGIN_RS* rs=(STRU_LOGIN_RS*)buf;
    //根据结果，弹窗提示
    switch(rs->result){
    case user_not_exist:
        QMessageBox::about(m_login,"提示","用户不存在T.T");
        break;
    case password_error:
        QMessageBox::about(m_login,"提示","密码错误@_@");
        break;
    case login_success:
        qDebug()<<"登录成功";
        m_userid=rs->userid;
        m_login->hide();
        m_main->showNormal();

        //注册视频和音频
        STRU_AUDIO_REGISTER audiorq;
        audiorq.m_userid=m_userid;
        SendAudioData(0,(char*)&audiorq,sizeof(audiorq));

        STRU_VIDEO_REGISTER videorq;
        videorq.m_userid=m_userid;
        SendVideoData(0,(char*)&videorq,sizeof(videorq));
        break;
    }
}

//处理注册回复
void CKernel::slot_DealRegisterRs(unsigned int socket, char *buf, int nlen)
{
    //拆包
    STRU_REGISTER_RS* rs=(STRU_REGISTER_RS*)buf;
    //根据结果，弹窗提示
    switch(rs->result){
    case tel_is_exist:
        QMessageBox::about(m_login,"提示","用户已存在,注册失败QAQ");
        break;
    case register_success:
        QMessageBox::about(m_login,"提示","注册成功^_^");
        break;
    }
}

//处理创建房间回复
void CKernel::slot_DealCreateRoomRs(unsigned int socket, char *buf, int nlen)
{
    //一定成功
    STRU_CREATEROOM_RS* rs=(STRU_CREATEROOM_RS*)buf;
    slot_setJoinedRoom(rs->m_RoomId);
}

//处理加入房间回复
void CKernel::slot_DealJoinRoomRs(unsigned int socket, char *buf, int nlen)
{
    STRU_JOINROOM_RS* rs=(STRU_JOINROOM_RS*)buf;
    if(rs->m_lResult!=join_success){
        QMessageBox::about(this->m_main,"提示","加入房间失败，房间不存在");
        return;
    }

    slot_setJoinedRoom(rs->m_RoomID);
}

//处理房间成员请求
void CKernel::slot_DealroomMemberRq(unsigned int socket, char *buf, int nlen)
{
    //拆包
    //查重
    STRU_ROOM_MEMBER_RQ* rq=(STRU_ROOM_MEMBER_RQ*)buf;
    UserShow* user=new UserShow;
    user->slot_setInfo(rq->m_UserID,QString::fromStdString(rq->m_szUser));
    connect(user,SIGNAL(SIG_userClicked(int,QString)),
            m_room,SLOT(slot_setBigImageInfo(int,QString)));

    if(m_mapIDToUserShow.count(rq->m_UserID)>0){
        UserShow* old=m_mapIDToUserShow[rq->m_UserID];
        m_mapIDToUserShow.erase(rq->m_UserID);
        m_room->slot_removeUser(old);

    }
    m_mapIDToUserShow[rq->m_UserID]=user;
    m_room->slot_addUser(user);

    //创建音频对象
    if(m_mapIDToAudioWrite.count(rq->m_UserID)>0){
        AudioWrite* aw= m_mapIDToAudioWrite[rq->m_UserID];
        m_mapIDToAudioWrite.erase(rq->m_UserID);
        delete aw;
    }
    AudioWrite* aw=new AudioWrite;
    m_mapIDToAudioWrite[rq->m_UserID]=aw;
}

//个人信息
void CKernel::slot_DealUserInfoRq(unsigned int socket, char *buf, int nlen)
{
    //拆包
    STRU_USER_INFO_RQ* rq=(STRU_USER_INFO_RQ*)buf;
    //更新ui
    m_name=QString::fromStdString(rq->m_szUser);
    m_main->slot_setInfo(rq->m_iconid,m_name);
    //更新设置ui
    m_setUser->slot_setInfo(rq->m_iconid,m_name,
                            QString::fromStdString(rq->m_userFeeling));
}

//退出房间
void CKernel::slot_DealLeaveRoomRq(unsigned int socket, char *buf, int nlen)
{
    //拆包
    STRU_LEAVEROOM_RQ* rq=(STRU_LEAVEROOM_RQ*)buf;
    //删除特定的人
    if(m_mapIDToUserShow.count(rq->m_nUserId)==0)return;
    UserShow* user=m_mapIDToUserShow[rq->m_nUserId];

    m_mapIDToUserShow.erase(user->m_id);
    m_room->slot_removeUser(user);

    //map去掉这个人
    m_mapIDToAudioWrite.erase(user->m_id);
}

//加入房间
void CKernel::slot_setJoinedRoom(int m_RoomID){
    m_roomid=m_RoomID;
//    m_main->hide();按键变灰代表窗口隐藏
    m_main->slot_setPushButton_enable(false);
    m_room->showNormal();
    //初始化状态 清空等操作 可复用
    m_room->slot_setRoomID(m_roomid);

    //添加自己到房间
    UserShow* user=new UserShow;
    user->slot_setInfo(m_userid,m_name);
    connect(user,SIGNAL(SIG_userClicked(int,QString)),
            m_room,SLOT(slot_setBigImageInfo(int,QString)));
    m_mapIDToUserShow[m_userid]=user;
    m_room->slot_addUser(user);
}


//ui
//登录提交
void CKernel::slot_loginCommit(QString tel, QString passwd)
{
    //提取手机号、密码
    std::string strTel=tel.toStdString();
    std::string strPass=GetMD5(passwd);

    //写入协议包，网络发送
    STRU_LOGIN_RQ rq;//不能用指针
    strcpy(rq.tel,strTel.c_str());
    strcpy(rq.password,strPass.c_str());
    qDebug()<<strPass.c_str();
    //发送
    SendData(0,(char*)&rq,sizeof(rq));
}

//注册提交
void CKernel::slot_registerCommit(QString tel, QString passwd)
{
    //提取手机号、密码
    std::string strTel=tel.toStdString();
    std::string strPass=GetMD5(passwd);
    //写入协议包，网络发送
    STRU_REGISTER_RQ rq;//不能用指针
    strcpy(rq.tel,strTel.c_str());
    strcpy(rq.password,strPass.c_str());
    qDebug()<<strPass.c_str();
    //发送
    SendData(0,(char*)&rq,sizeof(rq));
}


//加入房间
void CKernel::slot_joinRoom()
{
    if(m_roomid!=0){
        QMessageBox::about(this->m_main,"提示","已在房间中，加入失败");
        return;
    }
    //加入什么房间
    int roomid=QInputDialog::getInt(this->m_main,"加入房间","房间号：");
    //格式：房间号100000-999999 6位房间号
    if(roomid!=0&&roomid<=100000||roomid>999999){
        QMessageBox::about(this->m_main,"提示","房间不存在");
        return;
    }
    if(roomid==0)return;
    //发送请求
    STRU_JOINROOM_RQ rq;
    rq.m_RoomID=roomid;
    rq.m_UserID=m_userid;

    SendData(0,(char*)&rq,sizeof(rq));
}

//创建房间
void CKernel::slot_createRoom()
{
    //发送请求
    STRU_CREATEROOM_RQ rq;
    rq.m_UserID=m_userid;

    SendData(0,(char*)&rq,sizeof(rq));
}

//设置个人信息:弹出框
void CKernel::slot_setUser()
{
    m_setUser->show();
}

//设置个人信息：信息提交
void CKernel::slot_userSetCommit(int iconid, QString name, QString feeling)
{
    //发包
    //中文兼容：utf8
    std::string strName=name.toStdString();
    std::string strFeeling=feeling.toStdString();
    STRU_USER_INFO_RQ rq;
    rq.m_iconid=iconid;
    rq.m_UserID=m_userid;
    strcpy(rq.m_szUser,strName.c_str());
    strcpy(rq.m_userFeeling,strFeeling.c_str());
    SendData(0,(char*)&rq,sizeof(rq));
    QMessageBox::about(m_main,"提示","个人信息设置成功！");
}

//退出房间
void CKernel::slot_quitRoom()
{
    //发包
    STRU_LEAVEROOM_RQ rq;
    rq.m_nUserId=m_userid;
    rq.m_RoomId=m_roomid;

    SendData(0,(char*)&rq,sizeof(rq));

    m_roomid=0;
    m_main->slot_setPushButton_enable(true);

    //声音关闭ui 后台
    m_room->slot_setRoomClear();

    //视频回收
    for(auto ite=m_mapIDToUserShow.begin();ite!=m_mapIDToUserShow.end();){
        UserShow* user=ite->second;
        ite=m_mapIDToUserShow.erase(ite);//迭代器失效
        m_room->slot_removeUser(user);
    }

    //音频播放的回收
    for(auto ite=m_mapIDToAudioWrite.begin();ite!=m_mapIDToAudioWrite.end();){
        AudioWrite* user=ite->second;
        ite=m_mapIDToAudioWrite.erase(ite);
        delete user;
    }
}

void CKernel::slot_audioOpen()
{
    m_audioRead->start();
}

void CKernel::slot_audioClose()
{
    m_audioRead->pause();
}

void CKernel::slot_videoOpen()
{
    m_videoRead->start();
}

void CKernel::slot_videoClose()
{
    m_videoRead->pause();
}

void CKernel::slot_deskOpen()
{
    m_deskRead->start();
}

void CKernel::slot_deskClose()
{
    m_deskRead->pause();
}

#include<QTime>
void CKernel::slot_sendAudioFrame(QByteArray &ba)
{
    //确定协议（服务器加个小时）
    //协议头
    //发送者id:服务器直到是谁发的，不给他转发
    //房间号：找到转发给谁
    //时间 小时 分钟 秒 毫秒 send延迟-》考虑丢弃帧，需要记录时间
    //音频长度
    //音频数据
    int type=DEF_PACK_AUDIO_FRAME;
    int userid=m_userid;
    int roomid=m_roomid;
    QTime tm=QTime::currentTime();
    int hour=tm.hour();
    int min=tm.minute();
    int sec=tm.second();
    int msec=tm.msec();
    char* audioData=ba.data();
    int len=ba.size();

    //序列化数据
    char* buf=new char[sizeof(int)*7+len];
    char* tmp=buf;
    *(int*)tmp=type;
    tmp+=sizeof(int);
    *(int*)tmp=userid;
    tmp+=sizeof(int);
    *(int*)tmp=roomid;
    tmp+=sizeof(int);
    *(int*)tmp=hour;
    tmp+=sizeof(int);
    *(int*)tmp=min;
    tmp+=sizeof(int);
    *(int*)tmp=sec;
    tmp+=sizeof(int);
    *(int*)tmp=msec;
    tmp+=sizeof(int);
    memcpy(tmp,audioData,len);
//    SendData(0,buf,sizeof(int)*7+len);
    SendAudioData(0,buf,sizeof(int)*7+len);
    delete[] buf;
}

//刷新画面 主要使用在采集
void CKernel::slot_refreshVideoImage(QImage &img)
{

    slot_refreshUserImage(m_userid,img);
}

//显示某个用户
void CKernel::slot_refreshUserImage(int id,QImage &img)
{
    //预览图 大图 显示
    m_room->slot_setBigImage(id,img);
    //列表图显示
    if(m_mapIDToUserShow.count(id)>0){
        UserShow* user=m_mapIDToUserShow[id];
        user->slot_setImage(img);
    }
}

void CKernel::slot_sendVideoFrameData(QByteArray &ba)
{
    //确定协议（服务器加个小时）
    //协议头
    //发送者id:服务器直到是谁发的，不给他转发
    //房间号：找到转发给谁
    //时间 小时 分钟 秒 毫秒 send延迟-》考虑丢弃帧，需要记录时间
    //音频长度
    //音频数据
    int type=DEF_PACK_VIDEO_FRAME;
    int userid=m_userid;
    int roomid=m_roomid;
    QTime tm=QTime::currentTime();
    int hour=tm.hour();
    int min=tm.minute();
    int sec=tm.second();
    int msec=tm.msec();
    char* audioData=ba.data();
    int len=ba.size();

    //序列化数据
    char* buf=new char[sizeof(int)*7+len];
    char* tmp=buf;
    *(int*)tmp=type;
    tmp+=sizeof(int);
    *(int*)tmp=userid;
    tmp+=sizeof(int);
    *(int*)tmp=roomid;
    tmp+=sizeof(int);
    *(int*)tmp=hour;
    tmp+=sizeof(int);
    *(int*)tmp=min;
    tmp+=sizeof(int);
    *(int*)tmp=sec;
    tmp+=sizeof(int);
    *(int*)tmp=msec;
    tmp+=sizeof(int);
    memcpy(tmp,audioData,len);
//    SendData(0,buf,sizeof(int)*7+len);
//    delete[] buf;
    //替换为发送信号
    Q_EMIT SIG_sendVideoFrame(0,buf,sizeof(int)*7+len);
}

void CKernel::slot_setFunnyPic(int index)
{
    m_videoRead->setFunnyPic(index);
}

void CKernel::slot_DealAudioFrameRq(unsigned int socket, char *buf, int nlen)
{
    //反序列化
    int type;
    int userid;
    int roomid;
    int hour;
    int min;
    int sec;
    int msec;

    //反序列化数据
    char* tmp=buf;
    type=*(int*)tmp;
    tmp+=sizeof(int);
    userid=*(int*)tmp;
    tmp+=sizeof(int);
    roomid=*(int*)tmp;
    tmp+=sizeof(int);
    tmp+=sizeof(int);
    tmp+=sizeof(int);
    tmp+=sizeof(int);
    tmp+=sizeof(int);

    int audiolen=nlen-7*sizeof(int);
    //音频数据
    QByteArray ba(tmp,audiolen);
    if(m_mapIDToAudioWrite.count(userid)>0){
        AudioWrite* aw=m_mapIDToAudioWrite[userid];
        aw->slot_net_rx(ba);
    }
}

void CKernel::slot_DealVideoFrameRq(unsigned int socket, char *buf, int nlen)
{
    //反序列化
    int type;
    int userid;
    int roomid;
    int hour;
    int min;
    int sec;
    int msec;

    //反序列化数据
    char* tmp=buf;
    type=*(int*)tmp;
    tmp+=sizeof(int);
    userid=*(int*)tmp;
    tmp+=sizeof(int);
    roomid=*(int*)tmp;
    tmp+=sizeof(int);
    tmp+=sizeof(int);
    tmp+=sizeof(int);
    tmp+=sizeof(int);
    tmp+=sizeof(int);

    int imagelen=nlen-7*sizeof(int);
    //视频数据
    QImage img;
    img.loadFromData((uchar*)tmp,imagelen);
    slot_refreshUserImage(userid,img);
}

//发送数据
void CKernel::SendData(unsigned int lSendIP, char *buf, int nlen)
{
    m_client->SendData(lSendIP,buf,nlen);
}

void CKernel::SendAudioData(unsigned int lSendIP, char *buf, int nlen)
{
    m_tcpAV[0]->SendData(lSendIP,buf,nlen);
}

void CKernel::SendVideoData(unsigned int lSendIP, char *buf, int nlen)
{
    m_tcpAV[1]->SendData(lSendIP,buf,nlen);
}

void SendThread::slot_threadSendData(unsigned int socket, char *buf, int nlen)
{
//    qDebug()<<"send:"<<QThread::currentThreadId();
    //判断是否延迟 丢包

    char* tmp=buf;
    //类型
    tmp+=sizeof(int);
    //用户id
    tmp+=sizeof(int);
    //房间id
    tmp+=sizeof(int);
    int hour=*(int*)tmp;
    tmp+=sizeof(int);
    int min=*(int*)tmp;
    tmp+=sizeof(int);
    int sec=*(int*)tmp;
    tmp+=sizeof(int);
    int msec=*(int*)tmp;
    tmp+=sizeof(int);
    QTime tm(hour,min,sec,msec);

    //判断延迟超过200ms，丢弃包
    if(tm.msecsTo(QTime::currentTime())<=200)
//        CKernel::getCkernel()->SendData(socket,buf,nlen);
        CKernel::getCkernel()->SendVideoData(socket,buf,nlen);
    delete[] buf;
}
