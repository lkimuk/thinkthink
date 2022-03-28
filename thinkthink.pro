QT += core qml quick network
CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/controller/VideoCategoryController.cpp \
        src/controller/VideoController.cpp \
        src/main.cpp \
        src/model/FileSender.cpp \
        src/model/RequestMessage.cpp \
        src/model/VideoCategoryModel.cpp \
        src/model/VideoModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    src/controller/VideoCategoryController.h \
    src/controller/VideoController.h \
    src/model/FileSender.h \
    src/model/RequestMessage.h \
    src/model/VideoCategoryModel.h \
    src/model/VideoModel.h \
    src/utils/Utils.hpp

INCLUDEPATH += $$PWD/src/model \
    $$PWD/src/controller \
    $$PWD/src/utils

