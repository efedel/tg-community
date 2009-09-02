/* QConsoleKeyPressThread.h
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#ifndef QCONSOLE_KEYPRESS_THREAD_H
#define QCONSOLE_KEYPRESS_THREAD_H

#include <QMutex>
#include <QThread>

class QConsoleKeyPressThread : public QThread {
public:
	QConsoleKeyPressThread( QObject * parent=0 );

	virtual void stop();

protected:
        virtual void run();

private:
	bool p_cont;
	QMutex p_mutex;

	bool cont();
};

#endif
