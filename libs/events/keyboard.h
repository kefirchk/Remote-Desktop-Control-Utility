#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#include <stdlib.h>

class Keyboard
{
public:
    enum KEY_EVENT {
        NOT_PRESSED = 0,
        IS_PRESSED = 1
    };
    void generate_key_event(int key_code);            // генерация нажатия клавиши
    int get_event_flag() const;                       // получение признака нажатия клавиши
    void set_event_flag(int newEvent_flag);           // установка признака нажатия клавиши
    int get_native_key_code() const;                  // получение кода клавиши
    void set_native_key_code(int newNative_key_code); // установка кода клавиши
private:
    int event_flag;        // признак нажатия клавиши
    int native_key_code;   // код клавиши
};

#endif // KEYBOARD_H
