
include(wxsqlite3/wxsqlite3.pri)
include(zsqlitecipherdriver/zsqlitecipherdriver.pri)

QT       += core sql
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
