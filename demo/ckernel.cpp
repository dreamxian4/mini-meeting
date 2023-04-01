#include "ckernel.h"
#include<qDebug>
#include<QSettings>
#include<QApplication>
#include<QFileInfo>

#define netMap(a) m_netMap[a-_DEF_PROTOCOL_BASE]

CKernel::CKernel(QObject *parent) : QObject(parent)
{
    initConfig();
    setNetMap();
    m_login=new LoginDialog;
    m_login->show();
    connect(m_login,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));

    m_main=new DemoDialog;
    connect(m_main,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));
    m_client=new TcpClientMediator;
    m_client->OpenNet(m_serverIp.toStdString().c_str(),8080);
//    m_client->OpenNet(_DEF_SERVER_IP,8080);
//    m_client->OpenNet("192.168.244.135",8080);
    connect(m_client,SIGNAL(SIG_ReadyData(unsigned int,char*,int)),
            this,SLOT(slot_ReadyData(unsigned int,char*,int)));

    //测试 登录验证与服务器的连接
    STRU_LOGIN_RQ rq;
    strcpy(rq.tel,"123");
    strcpy(rq.password,"123");
    m_client->SendData(0,(char*)&rq,sizeof(rq));
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

//处理数据
void CKernel::slot_ReadyData(unsigned int socket, char *buf, int nlen)
{
    QMessageBox::about(m_login,"提示","收到信息");
    int type=*(int*)buf;
    if(type>=_DEF_PROTOCOL_BASE&&type<_DEF_PROTOCOL_BASE+_DEF_PROTOCOL_COUNT){
        PFUN p=netMap(type);
        if(p) (this->*p)(socket,buf,nlen);
    }
    delete []buf;
}

//设置协议
void CKernel::setNetMap()
{
    memset(m_netMap,0,sizeof(PFUN));
    netMap(_DEF_PACK_LOGIN_RS)=&CKernel::slot_DealLoginRs;
}

//处理登录请求回复
void CKernel::slot_DealLoginRs(unsigned int socket, char *buf, int nlen)
{
    qDebug()<<__func__;
}
