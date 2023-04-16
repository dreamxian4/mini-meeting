QT += multimedia
LIBS += $$PWD/speex/lib/libspeex.lib\


HEADERS += \
    $$PWD/audio_common.h \
    $$PWD/audioread.h \
    $$PWD/audiowrite.h

SOURCES += \
    $$PWD/audioread.cpp \
    $$PWD/audiowrite.cpp
