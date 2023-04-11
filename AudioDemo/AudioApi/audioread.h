#ifndef AUDIOREAD_H
#define AUDIOREAD_H

#include <QObject>
#include<QTimer>
#include"audio_common.h"

class AudioRead : public QObject
{
    Q_OBJECT
public:
    explicit AudioRead(QObject *parent = nullptr);
    ~AudioRead();

    //方便控制开始暂停，添加状态
    enum audio_state{_Stop,_Record,_Pause};

signals:
    //定时采集的数据,以信号的形式发送
    void SIG_audioFrame(QByteArray ba);

public slots:
    //开始采集
    void start();
    //暂停采集
    void pause();
    //定时超时槽函数
    void slot_readMore();

private:
    QAudioFormat format;
    QTimer* m_timer;
    QAudioInput* audio_in;
    QIODevice* myBuffer_in;
    int m_recordState;
    //SPEEX 相关变量
    SpeexBits bits_enc;
    void *Enc_State;
};

#endif // AUDIOREAD_H
