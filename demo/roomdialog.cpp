#include "roomdialog.h"
#include "ui_roomdialog.h"

RoomDialog::RoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomDialog)
{
    ui->setupUi(this);
}

RoomDialog::~RoomDialog()
{
    delete ui;
}
