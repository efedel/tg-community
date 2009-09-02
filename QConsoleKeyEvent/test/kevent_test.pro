# key_event
# (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)

TEMPLATE	=	app
LANGUAGE	=	C++

CONFIG		+=	qt thread warn_on debug

TARGET		=	test_key_event
VERSION		=	1.0

HEADERS		+=	test_key_event.h

SOURCES		+=	test_key_event.cpp


unix {
	UI_DIR          = .ui
	MOC_DIR         = .moc
	OBJECTS_DIR     = .obj

	LIBS            +=      -L..
	LIBS            +=      -lQConsoleKeyEvent

	INCLUDEPATH     +=      ../include
}

