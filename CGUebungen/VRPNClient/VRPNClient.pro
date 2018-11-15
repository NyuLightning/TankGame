#Create an app
#TEMPLATE = app
#CONFIG += console
#QT += widgets
#CONFIG += qt

#Create a lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += vrpndevicedtrack.cpp \
#    testMain.cpp \

HEADERS += \
    vrpndevicedtrack.h

INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/../SGFrameworkLib

#mac 64
unix:macx{
LIBS += -L$$PWD/lib/mac/ -lvrpn -lgpsnmea -lquat -lvrpn_timecode_generator -lvrpnserver
}

#linux 64
unix:!macx{
LIBS += -L$$PWD/lib/linux/ -lvrpn -lgpsnmea -lquat -lvrpn_timecode_generator -lvrpnserver
}

#mingw 32
win32-g++{
LIBS += -L$$PWD/lib/mingw/ -lvrpn -lgpsnmea -lquat -lvrpn_timecode_generator -lvrpnserver -lws2_32
}

#msvc2010
win32-msvc2010{
#release
CONFIG(release, debug|release){
LIBS += -L$$PWD/lib/msvc/ -lvrpn -lquat -lvrpn_timecode_generator -lgpsnmea -lvrpnserver
}
#debug
CONFIG(debug, debug|release){
LIBS += -L$$PWD/../lib/msvc/ -lvrpnd -lquatd -lvrpn_timecode_generatord -lgpsnmead -lvrpnserverd
}
}

DISTFILES +=
