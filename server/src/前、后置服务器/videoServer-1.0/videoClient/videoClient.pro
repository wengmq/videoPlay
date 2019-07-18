#-------------------------------------------------
#
# Project created by QtCreator 2019-06-15T11:51:03
#
#-------------------------------------------------

QT       += core gui network

TARGET = videoClient
TEMPLATE = app


SOURCES += main.cpp\
        videoClient.cpp \
    ClientLogin.cpp \
    CBasePacket.cpp \
    VideoPacket.cpp

HEADERS  += videoClient.h \
    ClientLogin.h \
    myhelper.h \
    public.h \
    CBasePacket.h \
    VideoPacket.h

FORMS    += videoClient.ui








