TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17

TARGET = hello

DESTDIR = ../../bin

win32 {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {

    }

    INCLUDEPATH += $(GLFW_DIR)/include

    LIBS += -L$(GLFW_DIR)/lib -lglfw3dll

}

unix {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {

    }

}

INCLUDEPATH += ./include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
SOURCES += $$files(./src/*.c)
