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
    CKernel* kernel=CKernel::getCkernel();
    return a.exec();
}
