#include "videoread.h"
#include"QPainter"

//资源路径的拼写：用：表示资源文件 :/images/hat.png
VideoRead::VideoRead(QObject *parent) : QObject(parent)
  ,m_funnyPic(0),m_tuer(":/images/tuer.png"),m_hat(":/images/hat.png")
{
    m_timer=new QTimer;
    connect(m_timer,SIGNAL(timeout()),
            this,SLOT(slot_readMore()));
    MyFaceDefect::FaceDetectInit();
}

VideoRead::~VideoRead()
{
    m_timer->stop();
    delete m_timer;
}

void VideoRead::start()
{
    //打开摄像头
    cap.open(0);//打开默认摄像头
    if(!cap.isOpened()){
        QMessageBox::information(NULL,tr("提示"),tr("视频没有打开"));
        return;
    }
    //打开定时器
    m_timer->start(1000/FRAME_RATE);
}

void VideoRead::pause()
{
    //关闭摄像头
    if(cap.isOpened())
        cap.release();
    //关闭定时器
    m_timer->stop();
}

void VideoRead::slot_readMore()
{
    //获取一张图片
    Mat frame;
    if( !cap.read(frame) )
    {
        return;
    }
    //将 opencv 采集的 BGR 的图片类型转化为 RGB24 的类型
    cvtColor(frame,frame,CV_BGR2RGB);//BGR摄像头采集的格式 RGB控件显示的格式

    //人脸识别 , 如果失败, 使用上一次的人脸矩形
    std::vector<Rect> faces;
    //存储上一次识别人脸的矩形
    //std::vector<Rect> m_vecLastFace;
    if(m_funnyPic!=0)MyFaceDefect::detectAndDisplay(frame,faces);

    //定义 QImage 对象, 用于发送数据以及图片显示
    QImage image ((unsigned const
                   char*)frame.data,
                  frame.cols,frame.rows,QImage::Format_RGB888);

    //贴图
    //加载图片
    QImage* tmpImg = nullptr;
    switch( m_funnyPic )
    {
    case fp_tuer:
        tmpImg = &m_tuer; break;
    case fp_hat:
        tmpImg = &m_hat; break;
    default:
        tmpImg=nullptr;
        break;
    }

    //有识别到，将上一次的结果覆盖掉
    if( faces .size() > 0)
        m_vecLastFace = faces;
    //将道具绘制到图片上
    if( tmpImg )//判断当前是否需要画
        if( m_funnyPic == fp_tuer || m_funnyPic == fp_hat )
        {
            //QPainter 使用
            QPainter paint( &image );
            //遍历所有人脸的矩形, 画道具
            for( int i = 0 ; i < m_vecLastFace.size(); ++i)
            {
                Rect rct = m_vecLastFace[i];
                int x = rct.x + rct.width*0.5 - tmpImg -> width()*0.5 + 20;
                //20 是图片的尺寸偏移
                int y = rct.y - tmpImg -> height();
                QPoint p (x , y);
                paint.drawImage( p , * tmpImg );
            }
        }

    //转化为大小更小的图片 等比例缩放
    image = image.scaled( IMAGE_WIDTH,IMAGE_HEIGHT, Qt::KeepAspectRatio );
    //信号形式发送
    Q_EMIT SIG_videoFrame( image );

    //    image = image.scaled( IMAGE_WIDTH,IMAGE_HEIGHT, Qt::KeepAspectRatio );
    //图片转换为 QByteArray 进行发送
    //压缩图片从 RGB24 格式压缩到 JPEG 格式, 发送出去
    QByteArray ba;
    QBuffer qbuf(&ba); // QBuffer 与 QByteArray 字节数组联立联系
    image.save( &qbuf , "JPEG" , IMAGE_QUALITY ); //将图片的数据写入 ba

    Q_EMIT SIG_videoFrameData(ba);
}

void VideoRead::setFunnyPic(int newFunnyPic)
{
    m_funnyPic = newFunnyPic;
}

