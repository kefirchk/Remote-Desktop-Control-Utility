#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QApplication>
#include <QThread>
#include <QString>

#include "sockets_functions.h"
#include "screenshot.h"
#include "client.h"
#include "mouse.h"
#include "keyboard.h"

class ServerThread : public QThread {

    Q_OBJECT

signals:
    void updateCursorSignal(int cursor_type);         // сигнал для обновления рисунка курсора
    void sendClientInfoSignal(QString s, char* ip);   // сигнал для передачи информации на экран
    void signalToTurnOff();                           // сигнал выключить сервер
    void timeIsOverToConnectSignal();                 // сигнал о том, что время ожидания подключения вышло

private:
    struct sockaddr_in client_addr;                   // клиент
    int sockfd_for_listen;                            // прослушивающий сокет
    int sockfd_for_connect;                           // рабочий сокет
    int server_status;                                // статус сервера (вкл/выкл)
    char server_password[MAX_SIZE_STR];               // пароль на сервере

public:
    explicit ServerThread(QObject *parent = nullptr); // конструктор
    void run() override;                              // запуск потока
    void closeThread();                               // закрытие потока
    void closeSockets();                              // закрытие сокетов
    void receiveBasicInfoFromClient();                // получение базовой информации от клиента

public slots:
    void sendScreenshot();                            // отправка скриншота на экран
    void receivePasswordFromUISlot(const char*);      // получение пароля с UI
};



#endif // SERVERTHREAD_H
