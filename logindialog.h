#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"TcpClientMediator.h"
#include"TcpServerMediator.h"
#include<QCloseEvent>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

public slots:
    void slot_serverReadData( unsigned int socket, char* buf, int nlen);
    void slot_clientReadData( unsigned int socket, char* buf, int nlen);

signals:
    void SIG_close();
public:
    void closeEvent(QCloseEvent * event);
private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginDialog *ui;
    INetMediator *m_server;
    INetMediator *m_client;
};

#endif // LOGINDIALOG_H
