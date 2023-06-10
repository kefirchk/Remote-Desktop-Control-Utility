#ifndef MOUSE_H
#define MOUSE_H

#include <stdio.h>
#include <stdlib.h>

class Mouse
{
public:
    enum MOUSE_EVENT
    {
        NONE = 0,                // никакая кнопка мыши не нажата
        LEFT_PRESS = 1,          // нажатие ЛКМ
        RIGHT_PRESS = 2,         // нажатие ПКМ
        RELEASE = 3,             // отпускание ЛКМ
        DOUBLECLICK = 4,         // двойной клик ЛКМ
        MOVE = 5                 // движение мышки
    };
    void getMousePos(int** pos);                // получение позиции мышки
    void moveMouse(int* newPos);                // передвинуть мышь
    void generate_mouse_event(int mouse_event); // сгенерировать событие мыши
    int getEvent_flag() const;                  // получение события мыши
    void setEvent_flag(int newEvent_flag);      // установка события мыши
private:
    int event_flag;              // событие мыши
};

#endif // MOUSE_H
