# QConsoleKeyEvent : Project for generating Qt QKeyEvents fro the console
# (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)

TEMPLATE	=	lib
LANGUAGE	=	C++

CONFIG		+=	qt thread warn_on debug

TARGET		=	QConsoleKeyEvent
VERSION		=	1.0

# ---------------------------------------------------------------------- 
HEADERS		+=	\
		include/QConsoleKeyPressNotifier.h  \
		include/QConsoleKeyPressThread.h

SOURCES		+=	\
		src/QConsoleKeyPressNotifier.cpp  \
		src/QConsoleKeyPressThread.cpp


# ---------------------------------------------------------------------- 
# Architecture-dependent source

unix|macx {
	# TODO: check for termios.h

	HEADERS +=	\
		arch/unix/include/console_kbd.h

	SOURCES	+=	\
		arch/unix/src/console_kbd.cpp

}

# ---------------------------------------------------------------------- 
# Build flags

INCLUDEPATH	+=	./include

unix|macx {
	UI_DIR          = .ui
	MOC_DIR         = .moc
	OBJECTS_DIR     = .obj

	INCLUDEPATH	+=	./arch/unix/include
}

