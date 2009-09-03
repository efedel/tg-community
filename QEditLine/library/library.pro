# ------------------------------------------------------------------------------
# library project file

TEMPLATE        = lib
LANGUAGE        = C++

CONFIG          += qt

TARGET          = qeditline
VERSION         = 0.1.0
DESCR           = "qeditline library"

# Project Settings
BASE            = ../..

# ------------------------------------------------------------------------------
# Header files

#HEADERS += \
#        include/qeditline/config.h \
#        include/qeditline/chared.h \
#        include/qeditline/el.h \
#        include/qeditline/el_term.h \
#        include/qeditline/filecomplete.h \
#        include/qeditline/histedit.h \
#        include/qeditline/hist.h \
#        include/qeditline/key.h \
#        include/qeditline/map.h \
#        include/qeditline/parse.h \
#	include/qeditline/prompt.h \
#	include/qeditline/read.h \
#	include/qeditline/refresh.h \
#	include/qeditline/search.h \
#	include/qeditline/sig.h \
#	include/qeditline/sys.h \
#	include/qeditline/tty.h \
#	include/qeditline/vis.h \

HEADERS += \
        src/config.h \
        src/chared.h \
        src/el.h \
        src/el_term.h \
        src/filecomplete.h \
        src/histedit.h \
        src/hist.h \
        src/key.h \
        src/map.h \
        src/parse.h \
	src/prompt.h \
	src/read.h \
	src/refresh.h \
	src/search.h \
	src/sig.h \
	src/sys.h \
	src/tty.h \
	src/vis.h \

# ------------------------------------------------------------------------------
# Source files

SOURCES += \
        src/chared.c \
        src/common.c \
        src/el.c \
        src/emacs.c \
        src/fgetln.c \
        src/filecomplete.c \
        src/hist.c \
        src/history.c \
        src/key.c \
        src/map.c \
        src/parse.c \
        src/prompt.c \
        src/read.c \
        src/readline.c \
        src/refresh.c \
        src/search.c \
        src/sig.c \
        src/strlcat.c \
        src/strlcpy.c \
        src/term.c \
        src/tokenizer.c \
        src/tty.c \
        src/unvis.c \
        src/vi.c \
        src/vis.c \

# ------------------------------------------------------------------------------
# Build Flags

INCLUDEPATH     += ./src



