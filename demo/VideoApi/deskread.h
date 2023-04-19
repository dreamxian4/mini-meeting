#ifndef DESKREAD_H
#define DESKREAD_H

#include <QObject>
#include<QTimer>
#include<QApplication>
#include<QDesktopWidget>
#include<QBuffer>
#include<QScreen>
#include<QImage>
#include"video_common.h"

class DeskRead : public QObject
{
    Q_OBJECT
public:
    explicit DeskRead(QObject *parent = nullptr);
    ~DeskRead();
signals:
    void SIG_screenFrame(QImage& img);
    void SIG_screenFrameData(QByteArray& ba);
public slots:
    void start();
    void pause();
    void slot_getScreenFrame();
private:
    QTimer* m_timer;
};

//需要输出 截屏 ->信号形式输出
//需要 开启 关闭
//定时器 超时 -> 槽函数 执行截屏 发送信号
#endif // DESKREAD_H
