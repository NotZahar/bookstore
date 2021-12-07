QT       += core gui sql

RC_FILE += resources.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientsignup.cpp \
    clientsworkbench.cpp \
    entrance.cpp \
    main.cpp \
    signin.cpp \
    state.cpp \
    statemanager.cpp \
    userchoice.cpp

HEADERS += \
    bookstore.h \
    clientsignup.h \
    clientsworkbench.h \
    entrance.h \
    signin.h \
    state.h \
    statemanager.h \
    userchoice.h

FORMS += \
    clientsignup.ui \
    signin.ui \
    userchoice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
