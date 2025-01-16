QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QMiniAHCIDevice.cpp \
    QMiniAHCIDeviceID.cpp \
    QMiniAHCIPortATAStatus.cpp \
    QMiniAHCIPortNumber.cpp \
    QMiniAHCIPortLinkStatus.cpp \
    QMiniAHCIPortStatus.cpp \
    QMiniAHCISMARTAttribute.cpp

HEADERS += \
    QMiniAHCICommon.h \
    QMiniAHCIDevice.h \
    QMiniAHCIDeviceID.h \
    QMiniAHCIPortATAStatus.h \
    QMiniAHCIPortNumber.h \
    QMiniAHCIPortLinkStatus.h \
    QMiniAHCIPortStatus.h \
    QMiniAHCISMARTAttribute.h

INCLUDEPATH += \
    ../../QMiniPCIDevice/src

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
