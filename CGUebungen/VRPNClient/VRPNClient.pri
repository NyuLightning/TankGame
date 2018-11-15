headersDataFiles.files += $$PWD/../VRPNClient/*.h
headersDataFiles.files += $$PWD/../VRPNClient/include/*.h

libraryFiles.files = $${VRPN_LIB_PATH}/*.a $${VRPN_LIB_PATH}/*.lib

INCLUDEPATH += \
    $$PWD \
    $$PWD/include/

SOURCES += \
    $$PWD/vrpndevicedtrack.cpp \

HEADERS += \
    $$PWD/vrpndevicedtrack.h
