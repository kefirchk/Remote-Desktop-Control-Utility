#include "screenshot.h"

void Screenshot::take_screenshot(const char* screenshot_pathname)
{
    // Захват экрана
    screen = QApplication::primaryScreen();
    screenshot = screen->grabWindow(0);

    // Рисуем изображение курсора поверх скриншота
    QPainter painter(&screenshot);
    QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    QPoint mousePos = QCursor::pos();
    int radius = 10;
    painter.drawEllipse(mousePos, radius, radius);
    painter.end();

    // Сохраняем изображение скриншота с курсором в файл
    if(screenshot.save(screenshot_pathname) == false)
    {
        fprintf(stderr, "Error: screenshot is not created");
        exit(EXIT_FAILURE);
    }
}

void Screenshot::save_in_buffer(QBuffer* buffer)
{
    QByteArray bytes;
    buffer->setBuffer(&bytes);
    buffer->open(QIODevice::WriteOnly);
    if(screenshot.save(buffer, "PNG") == false)
        fprintf(stderr, "Error: screenshot is not saved to the buffer");
}
