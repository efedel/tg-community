/* QConsoleKeyPressNotifier.h
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#ifndef QCONSOLE_KEYPRESS_NOTIFIER_H
#define QCONSOLE_KEYPRESS_NOTIFIER_H

#include <QKeyEvent>
#include <QObject>
#include <QConsoleKeyPressThread.h>

/* attaches itself to the running QCoreApplication */
class QConsoleKeyPressNotifier : public QObject {
	Q_OBJECT
public:
	QConsoleKeyPressNotifier( bool autostart=true );

public slots:
	void start();
	void stop();
	bool isRunning() { return p_running; }

signals:
	void keyPressed(Qt::Key, Qt::KeyboardModifiers, QString );

protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void keyPressEvent( QKeyEvent * e );
private:
	bool p_running;
	QConsoleKeyPressThread p_thread;
};

#endif
