#include "ckernel.h"

CKernel::CKernel(QObject *parent) : QObject(parent)
{
    m_login=new LoginDialog;
    m_login->show();
    connect(m_login,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));

    m_main=new DemoDialog;
    connect(m_main,SIGNAL(SIG_close()),
            this,SLOT(slot_destroy()));

    m_client=new TcpClientMediator;
    //m_client->OpenNet(_DEF_SERVER_IP,8080);
    connect(m_client,SIGNAL(SIG_ReadyData(unsigned int,char*,int)),
            this,SLOT(slot_ReadyData(unsigned int,char*,int)));
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

void CKernel::slot_ReadyData(unsigned int socket, char *buf, int nlen)
{

}
