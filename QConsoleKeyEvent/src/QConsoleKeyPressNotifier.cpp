/* QConsoleKeyPressNotifier.cpp 
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#include <QCoreApplication>

#include <QConsoleKeyPressNotifier.h>

/* ---------------------------------------------------------------------- */
QConsoleKeyPressNotifier::QConsoleKeyPressNotifier( bool autostart ) 
	: QObject(qApp), p_thread(this) {

	qApp->installEventFilter(this);
	if ( autostart ) {
		start();
	}
}

void QConsoleKeyPressNotifier::start() {
	p_thread.start();
	p_running = true;
}

void QConsoleKeyPressNotifier::stop() {
	p_thread.stop();
	p_running = false;
}

void QConsoleKeyPressNotifier::keyPressEvent( QKeyEvent * e ) {
	emit keyPressed( e->key(), e->modifiers() );
	emit keyPressed( e->text() );
}

bool QConsoleKeyPressNotifier::eventFilter( QObject * obj, QEvent * e ) {
	if ( e->type() == QEvent::KeyPress ) {
		QKeyEvent *kevent = static_cast<QKeyEvent *>(e);
		if ( kevent ) {
			keyPressEvent(kevent);
			return true;
		}
	}

	return QObject::eventFilter(obj, e);
}
