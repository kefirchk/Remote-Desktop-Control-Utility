#include "keyboard.h"

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

void Keyboard::generate_key_event(int key_code)
{
    Display *display = XOpenDisplay(NULL);         // "привязываемся" к экрану
    if (display == NULL) {
        fprintf(stderr, "Cannot open display");
        exit(EXIT_FAILURE);
    }
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, key_code), True, 0);   // нажимаем клавишу
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, key_code), False, 0);  // отпускаем клавишу

    XCloseDisplay(display);                        // "отвязка" от экрана
}

int Keyboard::get_event_flag() const {
    return event_flag;
}

void Keyboard::set_event_flag(int new_event_flag) {
    event_flag = new_event_flag;
}

int Keyboard::get_native_key_code() const {
    return native_key_code;
}

void Keyboard::set_native_key_code(int new_native_key_code) {
    native_key_code = new_native_key_code;
}
