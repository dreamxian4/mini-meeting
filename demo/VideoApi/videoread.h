#ifndef VIDEOREAD_H
#define VIDEOREAD_H

#include <QObject>

#include"video_common.h"
#include<QMessageBox>
#include<QTimer>
#include<QBuffer>
#include"myfacedefect.h"


class VideoRead : public QObject
{
    Q_OBJECT
public:
    explicit VideoRead(QObject *parent = nullptr);
    ~VideoRead();
    enum funnyPic_type{ fp_tuer = 1 , fp_hat };

    void setFunnyPic(int newFunnyPic);

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
    int m_funnyPic; // 用于存储当前的萌拍效果 1 兔耳朵 2 帽子
    QImage m_tuer;
    QImage m_hat;
    std::vector<Rect> m_vecLastFace;//用来存储上一次的人脸

};

#endif // VIDEOREAD_H
