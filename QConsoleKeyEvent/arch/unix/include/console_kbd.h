/* console_kbd.h : Platform-specific keyboard routine implementations */

#ifndef CONSOLE_KBD_H
#define CONSOLE_KBD_H

/* kbhit(), basically */
int kbd_input_available();

/* is this a modifier key, i.e. Alt? */
bool kbd_is_modifier( int );

void kbd_keyevent_from_code( KeyEvent *, int code, int mod_code );

#endif
