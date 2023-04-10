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
{
    initConfig();
    setNetMap();

    m_client=new TcpClientMediator;
    //打开网络
    if(!m_client->OpenNet(m_serverIp.toStdString().c_str(),8080)){
        QMessageBox::about(this->m_login,"提示","服务器连接失败~~~");
        exit(0);
    }
    //连接收到信息和处理槽
    connect(m_client,SIGNAL(SIG_ReadyData(unsigned int,char*,int)),
            this,SLOT(slot_DealData(unsigned int,char*,int)));


    m_login=new LoginDialog;

    m_login->show();
    //连接关闭信号和销毁槽
    connect(m_login,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));
    connect(m_login,SIGNAL(SIG_loginCommit(QString,QString)),
            this,SLOT(slot_loginCommit(QString,QString)));
    connect(m_login,SIGNAL(SIG_registerCommit(QString,QString)),
            this,SLOT(slot_registerCommit(QString,QString)));



    m_main=new DemoDialog;
    //连接关闭信号和销毁槽
    connect(m_main,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));
    connect(m_main,SIGNAL(SIG_joinRoom()),
            this,SLOT(slot_joinRoom()));
    connect(m_main,SIGNAL(SIG_createRoom()),
            this,SLOT(slot_createRoom()));
    connect(m_main,SIGNAL(SIG_setUser()),
            this,SLOT(slot_setUser()));


    m_room=new RoomDialog;

    m_setUser=new SetUserDialog;
    connect(m_setUser,SIGNAL(SIG_userSetCommit(int,QString,QString)),
            this,SLOT(slot_userSetCommit(int,QString,QString)));
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
    if(m_client){
        m_client->CloseNet();
        delete m_client;
        m_client=NULL;
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
}

//网络数据
//处理数据
void CKernel::slot_DealData(unsigned int socket, char *buf, int nlen)
{
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

    m_room->slot_addUser(user);
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


void CKernel::slot_setJoinedRoom(int m_RoomID){
    m_roomid=m_RoomID;
    m_main->hide();
    m_room->showNormal();
    //初始化状态 清空等操作 可复用
    m_room->slot_setRoomID(m_roomid);

    //添加自己到房间
    UserShow* user=new UserShow;
    user->slot_setInfo(m_userid,"自己");

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

//发送数据
bool CKernel::SendData(unsigned int lSendIP, char *buf, int nlen)
{
    return m_client->SendData(lSendIP,buf,nlen);
}
