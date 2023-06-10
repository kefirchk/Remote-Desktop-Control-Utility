#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include "config.h"

class Client
{
public:
    char* get_local_host_name();             // получение локального имени хоста
    void set_local_host_name(const char*);   // установка локального имени хоста
    char* get_password();                    // получение пароля
    void set_password(const char*);          // установка пароля
    char* get_ip();                          // получение IP
    void set_ip(const char* new_ip);         // установка IP
private:
    char local_host_name[MAX_SIZE_STR] = ""; // локальное имя хоста
    char password[MAX_SIZE_STR] = "";        // пароль
    char ip[MAX_SIZE_STR] = "";              // IP
};

#endif // CLIENT_H
