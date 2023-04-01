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

signals:
    void SIG_close();
public:
    void closeEvent(QCloseEvent * event);


private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
