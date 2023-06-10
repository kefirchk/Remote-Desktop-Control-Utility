#include "sockets_functions.h"

int Socket(int domain, int type, int protocol) {
    int res_sockfd = socket(domain, type, protocol);
    if (res_sockfd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Установка опции SO_REUSEADDR для повторного использования адреса
    int opt = 1;
    if (setsockopt(res_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        // Ошибка установки опции сокета
        perror("Setsocketopt failed");
        exit(EXIT_FAILURE);
    }

    // Установка тайм-аута в 10 секунд
    struct timeval tv;
    tv.tv_sec = TIMEOUT; // TIMEOUT = 10 sec
    tv.tv_usec = 0;
    if (setsockopt(res_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) < 0)
    {
        // Ошибка установки опции сокета
        perror("Setsocketopt failed");
        exit(EXIT_FAILURE);
    }

    return res_sockfd;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("Listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            // Истек тайм-аут, соединение не установлено
            errno = 0;
            return 0;
        } else {
            // Ошибка принятия входящего соединения
            perror("Accept failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }
    return res;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connect failed");
        Close(sockfd);
        //exit(EXIT_FAILURE);
    }
    return res;
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        perror("Inet_pton failed: src does not contain a character"
               " string representing a valid network address in the specified"
               " address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("Inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

void Close(int& fd)
{
    shutdown(fd, SHUT_RDWR);
    close(fd);
}

void send_file(int* sock, const char* file_name)
{
    std::fstream file;
    file.open(file_name, std::ios_base::in | std::ios_base::binary);

    if(file.is_open())
    {
        int file_size = std::filesystem::file_size(file_name) + 1;
        char* bytes = (char*)malloc(file_size*sizeof(char));

        file.read(bytes, file_size);

        qDebug("size: %d", file_size);
        qDebug("name: %s", file_name);
        qDebug("data: %s", bytes);

        send(*sock, std::to_string(file_size).c_str(), MAX_SIZE_INT_STR, 0);
        send(*sock , file_name, MAX_SIZE_STR, 0);
        send(*sock, bytes, file_size, 0);

        free(bytes);
    }
    else
        perror("Error file open\n");
    file.close();
}

void recv_file(int* sock, int *status)
{
    char file_size_str[MAX_SIZE_INT_STR];
    char file_name[MAX_SIZE_STR];

    recv(*sock, file_size_str, MAX_SIZE_INT_STR, MSG_WAITALL);
    int file_size = atoi(file_size_str);
    char* bytes = (char*)malloc(file_size*sizeof(char));

    recv(*sock, file_name, MAX_SIZE_STR, MSG_WAITALL);

    qDebug("size: %d", file_size);
    qDebug("name: %s", file_name);

    if(file_size == 0)  //сервер был отключен
    {
        *status = 0;
        free(bytes);
        return;
    }

    std::fstream file;
    file.open(file_name, std::ios_base::out | std::ios_base::binary);

    if(file.is_open())
    {
        recv(*sock, bytes, file_size, MSG_WAITALL);
        qDebug("data: %s", bytes);

        file.write(bytes, file_size);
        qDebug("ok, saved");
    } else {
        perror("Error file open\n");
    }

    free(bytes);
    file.close();
}
