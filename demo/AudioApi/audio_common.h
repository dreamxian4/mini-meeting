#ifndef AUDIO_COMMON_H
#define AUDIO_COMMON_H

#include<QAudioInput>
#include<QAudioOutput>
#include<QAudioFormat>
#include<QAudioDeviceInfo>
#include<QMessageBox>
#include<qDebug>

//使用speex
#include <speex/include/speex.h>

#define USE_SPEEX 1
//设置压缩质量
#define SPEEX_QUALITY (8)

#endif // AUDIO_COMMON_H
