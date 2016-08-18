CONFIG(release, debug|release):DEFINES *= NDEBUG

DEFINES += SQLITE_HAS_CODEC

INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD

HEADERS += \
    $$PWD/sqlite3.h \
    $$PWD/codec.h \
    $$PWD/rijndael.h \
    $$PWD/sha2.h

SOURCES += \
    $$PWD/sqlite3.c \
    $$PWD/sqlite3secure.c \
    $$PWD/codec.c \
    $$PWD/rijndael.c \
    $$PWD/codecext.c \
    $$PWD/sha2.c
