#include "dialog.h"

#include <QApplication>
#include"video_common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();



    return a.exec();
}
