#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include "listener.h"


class KeyListener : Listener
{
    KeyListener();

    void keyboard(int key, int modifier);

};

#endif // KEYLISTENER_H
