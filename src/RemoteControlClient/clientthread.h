#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QApplication>
#include <QMainWindow>
#include <QThread>
#include <QHostInfo>

#include "dialog.h"
#include "sockets_functions.h"
#include "client.h"
#include "mouse.h"
#include "keyboard.h"

class ClientThread : public QThread
{
    Q_OBJECT

signals:
    void screenshotReady(QImage screenshot);    // сигнал готовности скриншота вывода на экран
    void showPasswordStatusSignal(int status);  // сигнал для показа статуса правильности пароля
    void signalToDisconnect();                  // сигнал для разрыва соединения
    void connectFailedSignal();                 // сигнал о невозможности подключения

private:
    struct sockaddr_in server_addr;             // сервер
    int sockfd_for_connect;                     // рабочий сокет
    int client_status;                          // статус клиента (вкл/выкл)
    DataConnection dataConnection;              // информация для создания соединения
    Mouse mouse;                                // мышь
    Keyboard keyboard;                          // клавиатура

public:
    explicit ClientThread(QObject* parent = nullptr);  // конструктор
    ~ClientThread();                                   // деструктор
    void run() override;                               // запуск потока
    void closeThread();                                // закрытие потока
    void receiveScreenshot();                          // получение скриншота
    void sendClientInfoToServer();                     // отправка клиентской информации серверу

public slots:
    void receiveSettingsFromUISlot(DataConnection data);          // получение введенных настроек с UI
    void getMouseEventFromWindowSlot(int event_pos);              // получение события мыши
    void getKeyEventFromWindowSlot(int is_pressed, int key_code); // получения события клавиатуры
};

#endif // CLIENTTHREAD_H
