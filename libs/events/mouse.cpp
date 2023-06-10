#include "mouse.h"

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

void Mouse::getMousePos(int** pos)
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display");
        exit(EXIT_FAILURE);
    }
    Window root = DefaultRootWindow(display);
    int rootX, rootY, winX, winY;
    unsigned int mask;

    XQueryPointer(display, root, &root, &root, &rootX, &rootY, &winX, &winY, &mask);

    (*pos)[0] = rootX;  // Переменные rootX и rootY будут содержать координаты указателя мыши
    (*pos)[1] = rootY;  // относительно корневого окна экрана (обычно это экранная панель или рабочий стол).
    (*pos)[2] = winX;   // winX и winY - относительно окна, на котором находится указатель
    (*pos)[3] = winY;

    XCloseDisplay(display);
}

void Mouse::moveMouse(int* newPos)
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display");
        exit(EXIT_FAILURE);
    }
    Window root = DefaultRootWindow(display);

    XWarpPointer(display, None, root, 0, 0, 0, 0, newPos[0], newPos[1]);
    XFlush(display); // необходимо вызвать XFlush для того, чтобы изменения применились немедленно
    XCloseDisplay(display);
}

void Mouse::generate_mouse_event(int mouse_event)
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display");
        exit(EXIT_FAILURE);
    }

    switch(mouse_event)
    {
    case Mouse::NONE: break;
    case Mouse::LEFT_PRESS :     // генерация нажатия ЛКМ
        XTestFakeButtonEvent(display, Button1, True, CurrentTime);
        XTestFakeButtonEvent(display, Button1, False, CurrentTime);
        XFlush(display);
        break;
    case Mouse::RIGHT_PRESS:     // генерация нажатия ПКМ
        XTestFakeButtonEvent(display, Button3, True, CurrentTime);
        XTestFakeButtonEvent(display, Button3, False, CurrentTime);
        XFlush(display);
        break;
    case Mouse::RELEASE:         // генерация отпускания ЛКМ
        XTestFakeButtonEvent(display, Button1, False, CurrentTime);
        XFlush(display);
        break;
    case Mouse::DOUBLECLICK:     // генерация двойного клика ЛКМ
        XTestFakeButtonEvent(display, Button1, True, CurrentTime);
        XTestFakeButtonEvent(display, Button1, False, CurrentTime);
        XTestFakeButtonEvent(display, Button1, True, CurrentTime);
        XTestFakeButtonEvent(display, Button1, False, CurrentTime);
        XFlush(display);
        break;
    }

    XCloseDisplay(display);
}

int Mouse::getEvent_flag() const { return event_flag; }

void Mouse::setEvent_flag(int newEvent_flag) { event_flag = newEvent_flag; }
