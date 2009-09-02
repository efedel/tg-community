/* console_kbd.cpp : Platform-specific keyboard routine implementations 
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>

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
	// TODO
	return code == 27;
}

void kbd_keyevent_from_code( KeyEvent *, int code, int mod_code ) {
	// TODO
}

