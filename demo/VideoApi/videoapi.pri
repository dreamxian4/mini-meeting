HEADERS += \
    $$PWD/deskread.h \
    $$PWD/myfacedefect.h \
    $$PWD/video_common.h \
    $$PWD/videoread.h

SOURCES += \
    $$PWD/deskread.cpp \
    $$PWD/myfacedefect.cpp \
    $$PWD/videoread.cpp

#使用 opencv4.2.0

INCLUDEPATH+=F:/Qt/opencv-release/include/opencv2\
             F:/Qt/opencv-release/include

LIBS+=F:\Qt\opencv-release\lib\libopencv_calib3d420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_core420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_features2d420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_flann420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_highgui420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_imgproc420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_ml420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_objdetect420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_video420.dll.a\
      F:\Qt\opencv-release\lib\libopencv_videoio420.dll.a
