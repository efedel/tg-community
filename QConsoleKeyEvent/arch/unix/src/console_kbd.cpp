/* console_kbd.cpp : Platform-specific keyboard routine implementations 
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>

#include <console_kbd.h>

int kbd_input_available() {
	static bool init=false;
	static int fd;

	if (! init ) {
		fd = 0;	/* stdin */

		/* set up terminal */
		termios term;
		tcgetattr( fd, &term );
		term.c_lflag &= ~ICANON;
		tcsetattr(fd, TCSANOW, &term);

		/* set stdin stream to unbuffered */
		setbuf(stdin, NULL);

		init=true;
	}

	int bytes;	/* # bytes available */
	if ( ioctl( fd, FIONREAD, &bytes ) < 0 ) {
		return 0;
	}
	return bytes;
}

bool kbd_is_modifier( int code ) {
	// TODO: other modifiers?
	return code == 27;
}

QKeyEvent * kbd_keyevent_from_code( int code, int mod_code ) {
	// TODO: do this properly
	
	Qt::KeyboardModifiers modifiers = Qt::NoModifier;
	if ( mod_code == 27 ) {
		modifiers = Qt::AltModifier;
	}
	Qt::Key key = (Qt::Key) code;
	// TODO: convert key to KeyEvent, e.g. get modifiers

	QKeyEvent * ke = new QKeyEvent( QEvent::KeyPress, key,
					modifiers, QString(QChar(code)) );
	return ke;
}

