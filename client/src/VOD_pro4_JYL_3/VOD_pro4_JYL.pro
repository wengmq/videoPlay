#-------------------------------------------------
#
# Project created by QtCreator 2019-06-16T09:43:06
#
#-------------------------------------------------

QT       += core gui network multimedia

TARGET = VOD_pro4_JYL
TEMPLATE = app


SOURCES += main.cpp\
        ServerConnectWidget.cpp \
    homepage/MainWidget.cpp \
    homepage/TiTleBar.cpp \
    homepage/LoginWidget.cpp \
    homepage/content/ContentWidget.cpp \
    homepage/content/ContentWidgetTiTleBar.cpp \
    homepage/content/CW_VideoWidget.cpp \
    homepage/content/CW_VideoWidgetUpper.cpp \
    homepage/content/CW_VideoWidgetLower.cpp \
    homepage/content/ContentBottomWidget.cpp \
    homepage/content/ContentBottomWidgetTitleBar.cpp \
    homepage/content/CW_VideoLibWidget.cpp \
    homepage/content/CW_VideoLibWidgetLeft.cpp \
    homepage/content/CW_VideoLibWidgetRight.cpp \
    packet/BasePacket.cpp \
    packet/VideoPacket.cpp \
    homepage/content/m_Button.cpp \
    videoPlay/m_ffmpeg.cpp \
    videoPlay/m_audio.cpp \
    videoPlay/m_thread.cpp \
    videoPlay/m_label.cpp \
    videoPlay/ffvideoplayer.cpp \
    homepage/content/m_ToolButton.cpp

HEADERS  += ServerConnectWidget.h \
    homepage/MainWidget.h \
    homepage/TiTleBar.h \
    homepage/LoginWidget.h \
    homepage/content/ContentWidget.h \
    homepage/content/ContentWidgetTiTleBar.h \
    homepage/content/CW_VideoWidget.h \
    homepage/content/CW_VideoWidgetUpper.h \
    homepage/content/CW_VideoWidgetLower.h \
    homepage/content/ContentBottomWidget.h \
    homepage/content/ContentBottomWidgetTitleBar.h \
    homepage/content/CW_VideoLibWidget.h \
    homepage/content/CW_VideoLibWidgetLeft.h \
    homepage/content/CW_VideoLibWidgetRight.h \
    packet/BasePacket.h \
    packet/PublicPacket.h \
    packet/VideoPacket.h \
    packet/myhelper.h \
    homepage/content/m_Button.h \
    videoPlay/m_ffmpeg.h \
    videoPlay/m_audio.h \
    videoPlay/m_thread.h \
    videoPlay/m_label.h \
    videoPlay/ffvideoplayer.h \
    videoPlay/ui_ffvideoplayer.h \
    homepage/content/m_ToolButton.h


INCLUDEPATH += $$PWD/ffmpeg/include \
                $$PWD/sdl/include

LIBS    += $$PWD/ffmpeg/lib/avcodec.lib \
            $$PWD/ffmpeg/lib/avdevice.lib \
            $$PWD/ffmpeg/lib/avfilter.lib \
            $$PWD/ffmpeg/lib/avformat.lib \
            $$PWD/ffmpeg/lib/avutil.lib \
            $$PWD/ffmpeg/lib/postproc.lib \
            $$PWD/ffmpeg/lib/swresample.lib \
            $$PWD/ffmpeg/lib/swscale.lib \
            $$PWD/sdl/lib/libSDL2.a
DESTDIR=bin

FORMS += \
    ffvideoplayer.ui





















































