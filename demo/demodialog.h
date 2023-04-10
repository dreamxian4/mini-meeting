#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include <QDialog>
#include"TcpClientMediator.h"
#include"TcpServerMediator.h"
#include<QCloseEvent>
#include"customwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DemoDialog; }
QT_END_NAMESPACE

class DemoDialog : public CustomMoveDialog
{
    Q_OBJECT

public:
    DemoDialog(QWidget *parent = nullptr);
    ~DemoDialog();

signals:
    void SIG_close();
    void SIG_createRoom();
    void SIG_joinRoom();
    void SIG_setUser();

public:
    void closeEvent(QCloseEvent * event);

private slots:
    void on_pb_min_clicked();

    void on_pb_close_clicked();

    void on_pb_join_clicked();

    void on_pb_create_clicked();

    void on_pb_icon_clicked();

public slots:
        void slot_setInfo(int id,QString name);

private:
    Ui::DemoDialog *ui;
    int m_iconid;
    QString m_name;

};
#endif // DEMODIALOG_H
