#ifndef USERSHOW_H
#define USERSHOW_H

#include <QWidget>
#include<QPaintEvent>
#include<QMouseEvent>

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
private:
    Ui::UserShow *ui;
    int m_id;
    QString m_name;
    friend class CKernel;
    friend class RoomDialog;
    QImage m_img;
};

//添加点击事件，点击发送信号 发送内容 id,name
#endif // USERSHOW_H
