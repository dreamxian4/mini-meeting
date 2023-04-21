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
#include"audioread.h"
#include"audiowrite.h"
#include"videoread.h"
#include"deskread.h"
#include"usershow.h"
#include"workthread.h"

class CKernel;
typedef void (CKernel::*PFUN)(unsigned int,char*,int);

//为了优化发送导致的卡顿，可以采用多线程，发送在工作者线程执行
class SendThread:public WorkThread{
    Q_OBJECT
public:

public slots:
    void slot_threadSendData(unsigned int socket,char* buf,int nlen);
};

class CKernel : public QObject
{
    Q_OBJECT
private:
    explicit CKernel(QObject *parent = nullptr);
    ~CKernel();
    CKernel(const CKernel& c){}

signals:
    void SIG_sendVideoFrame(unsigned int socket,char* buf,int nlen);
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
    //音频请求
    void slot_DealAudioFrameRq(unsigned int socket,char* buf,int nlen);
    //视频请求
    void slot_DealVideoFrameRq(unsigned int socket,char* buf,int nlen);

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
    //房间内麦克风、视频、桌面勾选框
    void slot_audioOpen();
    void slot_audioClose();
    void slot_videoOpen();
    void slot_videoClose();
    void slot_deskOpen();
    void slot_deskClose();

    void slot_sendAudioFrame(QByteArray &ba);
    void slot_refreshVideoImage(QImage &img);
    void slot_refreshUserImage(int id,QImage &img);
    void slot_sendVideoFrameData(QByteArray &ba);
    void slot_setFunnyPic(int index);

    //发送数据包
    void SendData(unsigned int lSendIP , char* buf , int nlen);
    //视频发送
    void SendAudioData(unsigned int lSendIP , char* buf , int nlen);
    //音频发送
    void SendVideoData(unsigned int lSendIP , char* buf , int nlen);
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
    //视频
    VideoRead* m_videoRead;
    std::map<int,UserShow*> m_mapIDToUserShow;//id--用户信息（每个用户的视频显示）
    //音频
    AudioRead* m_audioRead;
    std::map<int,AudioWrite*> m_mapIDToAudioWrite;
    //桌面deskread
    DeskRead* m_deskRead;
    QSharedPointer<SendThread>m_sendVideo;

    //视频和音频单独的tcp
    INetMediator* m_tcpAV[2];//0音频 1视频
};

//当视频和音频同时传输时，音频会卡顿，视频会由较大延迟
//优化方案：
//视频帧的协议包里面有时间戳，与当前时间（绝对时间）进行比对，如果发送发现延迟大（大于200ms），就丢弃
//延迟大的原因：发送是在单独线程里面用槽函数写的，时排队进行的，前一个包有一定延迟，就会影响到下一个包
//让其延迟执行槽函数
//这样音频和视频都和当前的绝对时间偏差小于200ms，那么就同步了

//因为视频流量较大，音频就卡顿，考虑视频和音频用两个不同的tcp传输
//什么时候与服务器建立视频和音频的tcp连接？
//登录之后，发数据包，完成tcp的连接和记录
#endif // CKERNEL_H
