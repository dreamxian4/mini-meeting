#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include<QVBoxLayout>
#include"customwidget.h"
#include"usershow.h"

namespace Ui {
class RoomDialog;
}

class RoomDialog : public CustomMoveDialog
{
    Q_OBJECT

signals:
    void SIG_quitRoom();
    void SIG_audioOpen();
    void SIG_audioClose();
    void SIG_videoOpen();
    void SIG_videoClose();
    void SIG_deskOpen();
    void SIG_deskClose();


public:
    explicit RoomDialog(QWidget *parent = nullptr);
    ~RoomDialog();

public slots:
    void slot_setRoomID(int roomid);
    void slot_addUser(QWidget* user);
    void slot_removeUser(QWidget* user);
    void slot_setRoomClear();
    void slot_setBigImage(int userid,QImage img);

private slots:
    void on_pb_min_clicked();

    void on_pb_max_clicked();

    void on_pb_close_clicked();

    void on_pb_hide_clicked();

    void on_pb_quit_clicked();

    void on_cb_capture_clicked();

    void on_cb_audio_clicked();

    void on_cb_desk_clicked();

private:
    Ui::RoomDialog *ui;
    //用于用户列表的垂直布局
    QVBoxLayout* m_userLayout;
};

#endif // ROOMDIALOG_H
