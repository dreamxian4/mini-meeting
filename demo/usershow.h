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

    void slot_setInfo(int id,QString name);
    //重写重绘事件
    void paintEvent(QPaintEvent *event);
private:
    Ui::UserShow *ui;
    int m_id;
    QString m_name;
};

#endif // USERSHOW_H
