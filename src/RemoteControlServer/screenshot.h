#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QApplication>
#include <QPixmap>
#include <QScreen>
#include <QBuffer>
#include <QCursor>
#include <QPoint>
#include <QPainter>

class Screenshot
{
public:
    void take_screenshot(const char* screenshot_pathname);  // сделать скриншот
    void save_in_buffer(QBuffer* buffer);                   // сохранить скриншот в буфер

private:
    QScreen* screen;       // для захвата экрана
    QPixmap screenshot;    // переменная для хранения скриншота
};

#endif // SCREENSHOT_H
