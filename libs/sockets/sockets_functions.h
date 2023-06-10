#ifndef SOCKETS_FUNCTIONS_H
#define SOCKETS_FUNCTIONS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>
#include <string>

#include <QDebug>

#include "config.h"

int Socket(int domain, int type, int protocol);                          // создать новый сокет и вернуть файловый дескриптор
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);   // связать сокет с IP-адресом и портом
void Listen(int sockfd, int backlog);                                    // объявить о желании принимать соединения, слушает порт и ждет когда будет установлено соединение
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);       // принять запрос на установку соединения
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); // установить соединение
void Inet_pton(int af, const char *src, void *dst);                      // преобразование адреса IPv4 и IPv6 из текста в бинарный вид
void Close(int &fd);                                                     // закрыть файловый дескриптор (сокет)
void send_file(int* sock, const char* file_name);                        //	отправить файл по сети
void recv_file(int* sock, int *status);                                  // получить файл из сети

#endif // SOCKETS_FUNCTIONS_H
