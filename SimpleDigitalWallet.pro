QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    interactionsystem.cpp \
    main.cpp \
    mainwindow.cpp \
    transaction.cpp \
    user.cpp \
    userinterface.cpp

HEADERS += \
    admin.h \
    interactionsystem.h \
    mainwindow.h \
    transaction.h \
    user.h \
    userinterface.h

FORMS += \
    admin.ui \
    interactionsystem.ui \
    mainwindow.ui \
    userinterface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    alltransaction.json \
    donations.json
    users.json
#QT += multimedia
