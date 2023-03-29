#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include <QDialog>
#include"TcpClientMediator.h"
#include"TcpServerMediator.h"
#include<QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class DemoDialog; }
QT_END_NAMESPACE

class DemoDialog : public QDialog
{
    Q_OBJECT

public:
    DemoDialog(QWidget *parent = nullptr);
    ~DemoDialog();

signals:
    void SIG_close();
public:
    void closeEvent(QCloseEvent * event);

private:
    Ui::DemoDialog *ui;

};
#endif // DEMODIALOG_H
