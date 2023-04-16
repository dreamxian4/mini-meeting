#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include <QMessageBox>
#include"demodialog.h"
#include"logindialog.h"
#include"TcpClientMediator.h"
#include"packdef.h"
#include"roomdialog.h"
#include<setuserdialog.h>
#include<map>

class CKernel;
typedef void (CKernel::*PFUN)(unsigned int,char*,int);

class CKernel : public QObject
{
    Q_OBJECT
private:
    explicit CKernel(QObject *parent = nullptr);
    ~CKernel();
    CKernel(const CKernel& c){}

signals:

public:
    static CKernel* getCkernel(){
        static CKernel c;
        return &c;
    }

public slots:
    //回收
    void slot_destroy();
    //初始化配置
    void initConfig();
    //设置协议
    void setNetMap();

    //网络槽
    //网络数据处理
    void slot_DealData(unsigned int socket,char* buf,int nlen);
    //登录回复
    void slot_DealLoginRs(unsigned int socket,char* buf,int nlen);
    //注册回复
    void slot_DealRegisterRs(unsigned int socket,char* buf,int nlen);
    //创建房间回复
    void slot_DealCreateRoomRs(unsigned int socket,char* buf,int nlen);
    //加入房间回复
    void slot_DealJoinRoomRs(unsigned int socket,char* buf,int nlen);
    //房间成员请求
    void slot_DealroomMemberRq(unsigned int socket,char* buf,int nlen);
    //个人信息请求
    void slot_DealUserInfoRq(unsigned int socket,char* buf,int nlen);
    //退出房间请求
    void slot_DealLeaveRoomRq(unsigned int socket,char* buf,int nlen);

    //设置加入的房间
    void slot_setJoinedRoom(int m_RoomID);

    //ui槽
    //登录 注册提交
    void slot_loginCommit(QString tel,QString passwd);
    void slot_registerCommit(QString tel,QString passwd);
    //加入、创建房间
    void slot_joinRoom();
    void slot_createRoom();
    //设置个人信息
    void slot_setUser();
    //个人信息提交
    void slot_userSetCommit(int iconid,QString name,QString feeling);
    //退出房间
    void slot_quitRoom();

    //发送数据包
    bool SendData(unsigned int lSendIP , char* buf , int nlen);

private:
    PFUN m_netMap[_DEF_PROTOCOL_COUNT];//协议映射表
    DemoDialog* m_main;//主窗口
    LoginDialog* m_login;//登录窗口
    RoomDialog* m_room;//房间窗口
    SetUserDialog* m_setUser;//个人信息窗口
    TcpClientMediator* m_client;//客户端
    QString m_serverIp;//服务端ip地址
    int m_userid;//用户id
    int m_roomid;//房间id
    QString m_name;//用户名
    std::map<int,UserShow*> m_mapIDToUserShow;//id--用户信息
};


#endif // CKERNEL_H
