#ifndef USERSHOW_H
#define USERSHOW_H

#include <QWidget>
#include<QPaintEvent>
#include<QMouseEvent>
#include<QTimer>
#include<QTime>

class CKernel;
class RoomDialog;

namespace Ui {
class UserShow;
}

class UserShow : public QWidget
{
    Q_OBJECT

signals:
    void SIG_userClicked(int id,QString name);

public:
    explicit UserShow(QWidget *parent = nullptr);
    ~UserShow();
public slots:
    void slot_setInfo(int id,QString name);
    void slot_setImage(QImage &img);
    //重写重绘事件
    void paintEvent(QPaintEvent *event);
    //重写鼠标点击事件
    void mousePressEvent(QMouseEvent *event);

    void slot_checkTimeOut();
private:
    Ui::UserShow *ui;
    int m_id;
    QString m_name;
    friend class CKernel;
    friend class RoomDialog;
    QImage m_img;
    QImage m_defaultImg;
    QTime m_lastTime;
    QTimer m_timer;
};

//添加点击事件，点击发送信号 发送内容 id,name
//一段时间接收不到图片，就将图片设置成默认
//定时器检测 最后一次收到画面的时间，与当前时间比较超过5秒，设置成默认
#endif // USERSHOW_H
