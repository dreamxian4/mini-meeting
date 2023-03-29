#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include <QDialog>
#include"TcpClientMediator.h"
#include"TcpServerMediator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DemoDialog; }
QT_END_NAMESPACE

class DemoDialog : public QDialog
{
    Q_OBJECT

public:
    DemoDialog(QWidget *parent = nullptr);
    ~DemoDialog();

public slots:
    void slot_serverReadData( unsigned int socket, char* buf, int nlen);
    void slot_clientReadData( unsigned int socket, char* buf, int nlen);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DemoDialog *ui;
    INetMediator *m_server;
    INetMediator *m_client;
};
#endif // DEMODIALOG_H
