TEMPLATE = lib
TARGET = QMLImageFx
QT += qml quick concurrent   quickwidgets
#CONFIG += plugin qmltypes c++11
CONFIG += plugin +qmltypes c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = QMLImageFx

# Input
SOURCES += \
        filters.cpp \
        imagechunk.cpp \
        iterableimagerepresentation.cpp \
        qmlimagefx_plugin.cpp \
        imagefx.cpp

HEADERS += \
        filters.h \
        imagechunk.h \
        iterableimagerepresentation.h \
        qmlimagefx_plugin.h \
        imagefx.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
