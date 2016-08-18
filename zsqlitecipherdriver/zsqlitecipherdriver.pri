QT      += core sql

# Need wxsqlite3.pri in the same project

HEADERS  += $$PWD/zsqlitecipherdriver.h \
            $$PWD/zsqliteciphercachedresult.h

SOURCES  += $$PWD/zsqlitecipherdriver.cpp \
            $$PWD/zsqliteciphercachedresult.cpp

INCLUDEPATH += $$PWD
