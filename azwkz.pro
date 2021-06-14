QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dialoge/dialog_azimport.cpp \
    Dialoge/dialog_kostenstelle.cpp \
    Dialoge/dialog_mitarb_einzeln.cpp \
    Dialoge/dialog_mitarbeiter.cpp \
    Funktionen/dateien.cpp \
    Funktionen/text.cpp \
    Funktionen/umwandeln.cpp \
    Funktionen/zeit_datum.cpp \
    Klassen/arbeitszeiten.cpp \
    Klassen/kostenstellen.cpp \
    Klassen/liste_qstring.cpp \
    Klassen/mitarbeiter.cpp \
    Klassen/prgpfade.cpp \
    Klassen/tabelle_qstring.cpp \
    Klassen/text_zeilenweise.cpp \
    Dialoge/dialog_kostenstellen.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Dialoge/dialog_azimport.h \
    Dialoge/dialog_kostenstelle.h \
    Dialoge/dialog_mitarb_einzeln.h \
    Dialoge/dialog_mitarbeiter.h \
    Funktionen/dateien.h \
    Funktionen/text.h \
    Funktionen/umwandeln.h \
    Funktionen/zeit_datum.h \
    Klassen/arbeitszeiten.h \
    Klassen/kostenstellen.h \
    Klassen/liste_qstring.h \
    Klassen/mitarbeiter.h \
    Klassen/prgpfade.h \
    Klassen/tabelle_qstring.h \
    Klassen/text_zeilenweise.h \
    ToDo.h \
    Dialoge/dialog_kostenstellen.h \
    mainwindow.h

FORMS += \
    Dialoge/dialog_azimport.ui \
    Dialoge/dialog_kostenstelle.ui \
    Dialoge/dialog_kostenstellen.ui \
    Dialoge/dialog_mitarb_einzeln.ui \
    Dialoge/dialog_mitarbeiter.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
