#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include"demodialog.h"
#include"logindialog.h"
#include"TcpClientMediator.h"

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
    void slot_destroy();
    void slot_ReadyData(unsigned int socket,char* buf,int nlen);

private:
    DemoDialog* m_main;
    LoginDialog* m_login;
    TcpClientMediator* m_client;
};

#endif // CKERNEL_H
