#ifndef MYFACEDEFECT_H
#define MYFACEDEFECT_H

#include"video_common.h"

class MyFaceDefect : public QObject
{
    Q_OBJECT
public:
    explicit MyFaceDefect(QObject *parent = nullptr);

signals:

public slots:
    // 0.人脸识别的初始化
    static void FaceDetectInit();
    // 1.获取摄像头图片后 识别出人脸的位置, 返回位置对应的矩形框
    static void detectAndDisplay(Mat &frame , std::vector<Rect> &faces);

};

#endif // MYFACEDEFECT_H
