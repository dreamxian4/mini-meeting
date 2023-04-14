#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"AudioApi/audioread.h"
#include"AudioApi/audiowrite.h"
#include"videoread.h"
#include"usershow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pb_start_clicked();

    void on_pb_pause_clicked();

    void on_pushButton_2_clicked();

    void on_pb_start_2_clicked();

    void slot_showImage(QImage img);
    void slot_showImageFromData(QByteArray ba);
    void on_pb_pause_2_clicked();

private:
    Ui::Dialog *ui;
    AudioRead* m_audioRead;
    AudioWrite* m_audioWrite;
    VideoRead* m_videoRead;
};
#endif // DIALOG_H
