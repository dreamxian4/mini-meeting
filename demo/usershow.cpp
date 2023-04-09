#include "usershow.h"
#include "ui_usershow.h"

#include<QPainter>

UserShow::UserShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserShow),m_id(0)
{
    ui->setupUi(this);
}

UserShow::~UserShow()
{
    delete ui;
}

void UserShow::slot_setInfo(int id, QString name)
{
    m_id=id;
    m_name=name;

    ui->lb_name->setText(QString("用户：%1").arg(m_name));
}

void UserShow::paintEvent(QPaintEvent *event)
{
    //画背景
    QPainter painter(this);//在这个控件上绘画，需要这个对象指针
    painter.setBrush((Qt::black));//设置黑色画刷
    //画一个矩形，会按照画刷的颜色填充
    painter.drawRect(-1,0,this->width()+1,this->height());
    //画图（人物或桌面）
    event->accept();
}
