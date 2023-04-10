#ifndef SETUSERDIALOG_H
#define SETUSERDIALOG_H

#include <QDialog>

namespace Ui {
class SetUserDialog;
}

class SetUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetUserDialog(QWidget *parent = nullptr);
    ~SetUserDialog();

signals:
    void SIG_userSetCommit(int iconid,QString name,QString feeling);


private slots:
    void on_pb_commit_clicked();

    void on_pb_clear_clicked();
public slots:
    void slot_setInfo(int iconid,QString name,QString feeling="比较懒，什么都没写。");

private:
    Ui::SetUserDialog *ui;
    int m_iconid       ;
    QString m_name     ;
    QString m_feeling  ;
};

#endif // SETUSERDIALOG_H
