//text
#include "demodialog.h"
#include "logindialog.h"
#include "ckernel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    DemoDialog w;
//    w.show();
//    LoginDialog l;
//    l.show();
//    TcpServerMediator s;
//    s.OpenNet("0.0.0.0",8080);
    CKernel* kernel=CKernel::getCkernel();
    return a.exec();
}
