QT       += core gui widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

INCLUDEPATH += ../qtpdf/include \
                ../qtpdf/include/QtPdf \
               ../qtpdf/include/QtPdfWidgets

LIBS += -L../qtpdf/lib

LIBS += -lQt5Pdf \
        -lQt5PdfWidgets

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

android {
##arm64-v8a  armeabi  armeabi-v7a  mips  mips64  x86  x86_64
    contains(ANDROID_TARGET_ARCH, armeabi-v7a) {
        message("Android / Arm v7a / 32 bit")
    }
    contains(ANDROID_TARGET_ARCH, arm64-v8a) {
        message("Android/ Arm v8a / 64 bit")
    }

}

linux:!android {
    contains(QMAKE_HOST.arch, x86_64):{
         message("Host is amd64")
    }
    contains(QMAKE_HOST.arch, arm64-v8a):{
         message("Host is arm64")
    }
    contains(QMAKE_HOST.arch, armeabi-v7a):{
         message("Host is arm32")
    }
}
