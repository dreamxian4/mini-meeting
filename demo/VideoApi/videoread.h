#ifndef VIDEOREAD_H
#define VIDEOREAD_H

#include <QObject>

#include"video_common.h"
#include<QMessageBox>
#include<QTimer>
#include<QBuffer>

class VideoRead : public QObject
{
    Q_OBJECT
public:
    explicit VideoRead(QObject *parent = nullptr);
    ~VideoRead();

signals:
    void SIG_videoFrame(QImage &img);
    void SIG_videoFrameData(QByteArray &bt);
public slots:
    void start();
    void pause();
    void slot_readMore();

private:
    //摄像头对象
    cv::VideoCapture cap;
    QTimer* m_timer;


};

#endif // VIDEOREAD_H
