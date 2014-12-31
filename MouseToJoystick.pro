#-------------------------------------------------
#
# Project created by QtCreator 2014-12-26T21:15:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MouseToJoystick
TEMPLATE = app

# Linking against 64-bit library currently
LIBS += -L$$PWD/vjoyLib/64 -lvJoyInterface


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h \
    vjoyInc/public.h \
    vjoyInc/vjoyinterface.h

FORMS    += MainWindow.ui

# Function for copying files to output folder
defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        DDIR = $$DESTDIR

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

# Copy vJoy dll out to output folder
copyToDestdir($$PWD/vjoyLib/64/vJoyInterface.dll)
