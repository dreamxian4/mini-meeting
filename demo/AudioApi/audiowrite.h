#ifndef AUDIOWRITE_H
#define AUDIOWRITE_H

#include <QObject>
#include"audio_common.h"
class AudioWrite : public QObject
{
    Q_OBJECT
public:
    explicit AudioWrite(QObject *parent = nullptr);
    ~AudioWrite();

signals:

public slots:
    void slot_net_rx(QByteArray ba);

private:
    QAudioFormat format;
    QAudioOutput* audio_out;
    QIODevice* myBuffer_out;
    //SPEEX 相关全局变量
    SpeexBits bits_dec;
    void *Dec_State;
};

#endif // AUDIOWRITE_H
