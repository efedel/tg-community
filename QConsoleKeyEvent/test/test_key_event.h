/* test_key_event.
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#ifndef TEST_KEY_EVENT_H
#define TEST_KEY_EVENT_H

#include <QCoreApplication>

#include <QConsoleKeyPressNotifier.h>

/* ---------------------------------------------------------------------- */
class KeyEventTestApp : public QCoreApplication {
	Q_OBJECT
public:
	KeyEventTestApp( int & argc, char ** argv ) ;

public slots:
	void keyPress( Qt::Key, Qt::KeyboardModifiers, QString );

private:
	QConsoleKeyPressNotifier p_notifier;
};

#endif
