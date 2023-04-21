#ifndef AUDIO_COMMON_H
#define AUDIO_COMMON_H

#include<QAudioInput>
#include<QAudioOutput>
#include<QAudioFormat>
#include<QAudioDeviceInfo>
#include<QMessageBox>
#include<qDebug>
extern "C"{
#include"WebRtc_Vad/webrtc_vad.h"
}


//使用speex
#include <speex/include/speex.h>

#define USE_SPEEX 1
#define USE_VAD 1

//设置压缩质量
#define SPEEX_QUALITY (8)

#endif // AUDIO_COMMON_H
