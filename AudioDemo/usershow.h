#ifndef USERSHOW_H
#define USERSHOW_H

#include <QWidget>
#include<QPaintEvent>

namespace Ui {
class UserShow;
}

class UserShow : public QWidget
{
    Q_OBJECT

public:
    explicit UserShow(QWidget *parent = nullptr);
    ~UserShow();
public slots:
    void slot_setInfo(int id,QString name);
    void slot_setImage(QImage img);
    //重写重绘事件
    void paintEvent(QPaintEvent *event);
private:
    Ui::UserShow *ui;
    int m_id;
    QString m_name;
    QImage m_img;
};

#endif // USERSHOW_H
