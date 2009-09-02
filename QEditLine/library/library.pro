# ------------------------------------------------------------------------------
# library project file

TEMPLATE        = lib
LANGUAGE        = C++

CONFIG          += qt

TARGET          = kitsch
VERSION         = 0.1.0
DESCR           = "qeditline library"

# Project Settings
BASE            = ../..

# 
------------------------------------------------------------------------------
# Header files

HEADERS += \
        include/qeditline/test.h \


# 
------------------------------------------------------------------------------
# Source files

SOURCES += \
        src/test.cpp \

# 
------------------------------------------------------------------------------
# Build Flags

INCLUDEPATH     += ./include



