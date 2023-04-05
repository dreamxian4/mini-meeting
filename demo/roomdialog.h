#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>

namespace Ui {
class RoomDialog;
}

class RoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoomDialog(QWidget *parent = nullptr);
    ~RoomDialog();

private:
    Ui::RoomDialog *ui;
};

#endif // ROOMDIALOG_H
