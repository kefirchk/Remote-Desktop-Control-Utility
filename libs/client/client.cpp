#include "client.h"

char* Client::get_local_host_name() {
    return local_host_name;
}

void Client::set_local_host_name(const char *new_local_host_name) {
    strncpy(local_host_name, new_local_host_name, MAX_SIZE_STR - 1);
}

char* Client::get_password() {
    return password;
}

void Client::set_password(const char* new_password) {
    strncpy(password, new_password, MAX_SIZE_STR - 1);
}

char* Client::get_ip() {
    return ip;
}

void Client::set_ip(const char* new_ip) {
    strncpy(ip, new_ip, MAX_SIZE_STR - 1);
}
