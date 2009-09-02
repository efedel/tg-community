/* test_key_event.cpp 
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#include <iostream>

#include "test_key_event.h"

/* ---------------------------------------------------------------------- */
KeyEventTestApp::KeyEventTestApp( int & argc, char ** argv ) 
	: QCoreApplication( argc, argv ) {

	connect( &p_notifier, 
		 SIGNAL(keyPressed(Qt::Key, Qt::KeyboardModifiers, QString)), 
		 this, 
		 SLOT(keyPress(Qt::Key, Qt::KeyboardModifiers, QString)) );
}

void KeyEventTestApp::keyPress( Qt::Key key, Qt::KeyboardModifiers mod, 
				QString text ) {
	std::cout << "Key " << (int) key << "(" << (int) mod << ") Pressed: ";
	std::cout << qPrintable(text) << "\n";
}

/* ---------------------------------------------------------------------- */

int main( int argc, char ** argv ) {
	KeyEventTestApp app( argc, argv );

	app.exec();

	return 0;
}
