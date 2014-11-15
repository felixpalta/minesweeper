TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Wconversion -Wsign-conversion -Wunreachable-code -Wshadow \
                    -Wold-style-cast -Wnon-virtual-dtor -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wenum-compare

SOURCES += \
    main.cpp \
    Mine_field.cpp

HEADERS += \
    Mine_field.h \
    matrix.h \
    mine_cell.h \
    input_loop.h

