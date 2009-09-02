/* test_key_event.cpp 
 * (c) Copyright 2009 ThoughtGang (www.thoughtgang.org)
 */

#include <iostream>

#include "test_key_event.h"

/* ---------------------------------------------------------------------- */
KeyEventTestApp::KeyEventTestApp( int & argc, char ** argv ) 
	: QCoreApplication( argc, argv ) {

	connect( &p_notifier, SIGNAL(keyPressed(QString)), 
		 this, SLOT(keyPress(QString)) );
}

void KeyEventTestApp::keyPress( QString text ) {
	std::cout << "Key Pressed: " << qPrintable(text) << "\n";
}

/* ---------------------------------------------------------------------- */

int main( int argc, char ** argv ) {
	KeyEventTestApp app( argc, argv );

	app.exec();

	return 0;
}
