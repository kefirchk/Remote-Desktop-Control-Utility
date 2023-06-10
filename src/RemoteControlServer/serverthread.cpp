#include "serverthread.h"

ServerThread::ServerThread(QObject *parent) : QThread(parent)
{
    // Сервер выключен
    server_status = false;

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(PORT);

    // Создаем прослушивающий сокет:
    sockfd_for_listen = Socket(AF_INET, SOCK_STREAM, 0);
    qDebug("Сокет создан");

    // Связываем сокеты:
    Bind(sockfd_for_listen, (struct sockaddr*) &client_addr, sizeof client_addr);
    qDebug("Связь установлена");
}

void ServerThread::closeThread(){
    this->server_status = 0;
}

void ServerThread::closeSockets() {
    Close(sockfd_for_connect);
    Close(sockfd_for_listen);
}

void ServerThread::run()
{
    // Сервер включен
    server_status = 1;

    socklen_t addrlen = sizeof(client_addr);

    // Слушаем:
    Listen(sockfd_for_listen, 1); // backlog = 1
    qDebug("Слушаем...");

    emit updateCursorSignal(1);   // тип курсора: loading

    // Подключаемся:
    sockfd_for_connect = Accept(sockfd_for_listen, (struct sockaddr *) &client_addr, &addrlen);
    if(sockfd_for_connect == 0)
    {
        emit timeIsOverToConnectSignal();
        return;
    }
    qDebug("Клиент успешно подключен\n");

    emit updateCursorSignal(0);   // тип курсора: normal

    // Принимаем информацию от клиента - его localHostName и введенный пароль
    receiveBasicInfoFromClient();

    // Отправляем скриншоты:
    int i = 0;
    char response[2];
    Mouse mouse;
    Keyboard keyboard;
    while(server_status)
    {
        // Отправка очередного скриншота
        sendScreenshot();

        // Получение ответа от клиента
        recv(sockfd_for_connect, response, 2, MSG_WAITALL);
        if(strcmp(response, "") == 0) {
            server_status = 0;
        }
        qDebug("RESPONSE = %s", response);

        // Получение координат мышки
        char message[32], len[16];
        int* pos = (int*)malloc(2 * sizeof(int)); //[0] = x, [1] = y
        memset(message, 0, sizeof(message));
        recv(sockfd_for_connect, len, 16, MSG_WAITALL);
        recv(sockfd_for_connect, message, atoi(len), MSG_WAITALL);
        sscanf(message, "%d %d", &pos[0], &pos[1]);

        // Обработка координат мыши
        mouse.moveMouse(pos);
        free(pos);

        // Получение события мышки
        char mouse_event_str;
        recv(sockfd_for_connect, &mouse_event_str, 1, MSG_WAITALL);
        int mouse_event = mouse_event_str - '0';
        qDebug() << "<<<<<<<<<<<MOUSE EVENT: " << mouse_event;
        mouse.generate_mouse_event(mouse_event);

        // Получение события клавиатуры
        strcpy(message, "");
        recv(sockfd_for_connect, message, 16, MSG_WAITALL);
        qDebug() << "<<<<<<<<<<<KEY CODE: " << message;
        if(strcmp(message, "0") != 0)
        {
            int key_code = atoi(message);
            keyboard.generate_key_event(key_code);
            keyboard.set_event_flag(Keyboard::NOT_PRESSED);
        }

        msleep(1000/FPS);
        qDebug("iterations = %d", i);
        strcpy(response, "");
        i++;
    }

    // Сервер был выключен
    emit signalToTurnOff();
}


void ServerThread::sendScreenshot()
{
    Screenshot screenshot;
    if(server_status)
    {
        screenshot.take_screenshot(FILENAME);
        send_file(&sockfd_for_connect, FILENAME);
        qDebug("Скриншот отправлен\n");
    }
}


void ServerThread::receiveBasicInfoFromClient()
{
    Client client;
    char client_size_str[MAX_SIZE_INT_STR];
    int client_size;

    while(1)
    {
        recv(sockfd_for_connect, client_size_str, MAX_SIZE_INT_STR, MSG_WAITALL);
        client_size = atoi(client_size_str);
        qDebug("client struct size = %d", client_size);

        recv(sockfd_for_connect, &client, client_size, MSG_WAITALL);
        qDebug("client password = %s", client.get_password());
        qDebug("client ip = %s", client.get_ip());
        qDebug("client local host name = %s\n", client.get_local_host_name());

        if(strcmp(client.get_password(), server_password) == 0)
        {
            QString local_host_name(client.get_local_host_name());
            emit sendClientInfoSignal(local_host_name, client.get_ip());
            send(sockfd_for_connect, "1", 1, 0);  //1 - all good;
            break;
        }
        else
            send(sockfd_for_connect, "0", 1, 0);  //0 - all bad;
    }
}


void ServerThread::receivePasswordFromUISlot(const char* password)
{
    qDebug("password from ui = %s", password);
    strncpy(server_password, password, MAX_SIZE_STR - 1);
}
