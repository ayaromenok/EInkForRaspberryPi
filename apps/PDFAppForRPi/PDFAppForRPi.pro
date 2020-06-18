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
