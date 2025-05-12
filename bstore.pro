QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    inputitem.cpp \
    inputter.cpp \
    login.cpp \
    reg.cpp \
    featurechanger.cpp \
    productchanger.cpp \
    productfeatures.cpp \
    providerproduct.cpp \
    tableitem.cpp \
    main.cpp \
    bstore.cpp \
    product.cpp \
    sql.cpp \
    storage.cpp \
    supply.cpp

HEADERS += \
    inputitem.h \
    inputter.h \
    login.h \
    reg.h \
    featurechanger.h \
    productchanger.h \
    productfeatures.h \
    providerproduct.h \
    tableitem.h \
    bstore.h \
    product.h \
    sql.h \
    storage.h \
    supply.h

FORMS += \
    inputitem.ui \
    inputter.ui \
    login.ui \
    reg.ui \
    featurechanger.ui \
    productchanger.ui \
    productfeatures.ui \
    providerproduct.ui \
    bstore.ui \
    product.ui \
    storage.ui \
    supply.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    RES.qrc
