/* test_key_event.cpp 
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#include <QCoreApplication>
#include <QKeyEvent>

#include <QConsoleKeyPressThread.h>
#include <console_kbd.h>

/* ---------------------------------------------------------------------- */

static void gen_kbd_event( int code, int mod_key ) {
	qApp->postEvent( qApp, kbd_keyevent_from_code(code, mod_key) );
}

/* ---------------------------------------------------------------------- */

QConsoleKeyPressThread::QConsoleKeyPressThread( QObject * parent ) 
	: QThread(parent), p_cont(false) {
}

void QConsoleKeyPressThread::run() {
	p_mutex.lock();
	p_cont = true;
	p_mutex.unlock();

	while ( cont() ) {

		int mod_key=0;
		for ( int i=0; i < kbd_input_available(); ++i ) {
			int code = getchar();
			if ( kbd_is_modifier(code) ) {
				mod_key = code;
			} else {
				gen_kbd_event( code, mod_key );
			}

			if ( mod_key != code ) {
				mod_key = 0;
			}
		}

		QThread::msleep(50);
	}
}

void QConsoleKeyPressThread::stop() {
	p_mutex.lock();
	p_cont = false;
	p_mutex.unlock();
}


bool QConsoleKeyPressThread::cont() {
	p_mutex.lock();
	bool rv = p_cont;
	p_mutex.unlock();
	return rv;
}
