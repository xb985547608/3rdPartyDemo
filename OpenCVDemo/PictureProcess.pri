INCLUDEPATH += $$PWD/opencv-3.2.0/include
LIBS += $$PWD/opencv-3.2.0/lib/libopencv_calib3d320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_core320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_features2d320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_flann320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_highgui320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_imgproc320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_imgcodecs320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_ml320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_objdetect320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_photo320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_shape320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_stitching320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_superres320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_video320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_videoio320.dll.a\
        $$PWD/opencv-3.2.0/lib/libopencv_videostab320.dll.a

HEADERS += \
    $$PWD/pictureprocesswidget.h \
    $$PWD/hsladjustdialog.h \
    $$PWD/blackwhiteadjustdialog.h \
    $$PWD/lightnesscontrastadjustdialog.h \
    $$PWD/selectivecoloradjustdialog.h \
    $$PWD/adjustdialog.h \
    $$PWD/curves.h \
    $$PWD/colorspace.h \
    $$PWD/blackwhite.h \
    $$PWD/hsl.h \
    $$PWD/selectivecolor.h

SOURCES += \
    $$PWD/pictureprocesswidget.cpp \
    $$PWD/hsladjustdialog.cpp \
    $$PWD/blackwhiteadjustdialog.cpp \
    $$PWD/lightnesscontrastadjustdialog.cpp \
    $$PWD/selectivecoloradjustdialog.cpp \
    $$PWD/blackwhite.cpp \
    $$PWD/colorspace.cpp \
    $$PWD/curves.cpp \
    $$PWD/hsl.cpp \
    $$PWD/selectivecolor.cpp

FORMS += \
    $$PWD/pictureprocessform.ui \
    $$PWD/hsladjustform.ui \
    $$PWD/blackwhiteadjustform.ui \
    $$PWD/lightnesscontrastadjustform.ui \
    $$PWD/selectivecoloradjustform.ui

RESOURCES += \
    $$PWD/pictureprocess.qrc
