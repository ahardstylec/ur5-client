TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    ../libs/ur5lib.c \
    ../libs/interrupt_utils.c \
    ../libs/base_utils.c

OTHER_FILES +=

HEADERS += \
    ../libs/ur5lib.h \
    ../libs/interrupt_utils.h \
    ../libs/base_utils.h

