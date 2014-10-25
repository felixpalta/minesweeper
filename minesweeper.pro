TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
SOURCES += \
    main.cpp \
    Mine_field.cpp

HEADERS += \
    Mine_field.h

