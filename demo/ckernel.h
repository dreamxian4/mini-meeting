#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include <QMessageBox>
#include"demodialog.h"
#include"logindialog.h"
#include"TcpClientMediator.h"
#include"packdef.h"

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
    //网络数据处理
    void slot_ReadyData(unsigned int socket,char* buf,int nlen);
    //设置协议
    void setNetMap();
    //网络数据处理:登录请求回复
    void slot_DealLoginRs(unsigned int socket,char* buf,int nlen);

private:
    PFUN m_netMap[_DEF_PROTOCOL_COUNT];//协议映射表
    DemoDialog* m_main;//主窗口
    LoginDialog* m_login;//登录窗口
    TcpClientMediator* m_client;//客户端
    QString m_serverIp;//服务端ip地址
};


#endif // CKERNEL_H
