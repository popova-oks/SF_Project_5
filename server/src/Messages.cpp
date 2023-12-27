#include "../headers/Messages.h"
#include "../headers/ConnectionTCP.h"
#include <cstring>
#include <fstream>
#include <iostream>

template <typename T> T Messages<T>::get_messages() {
    ssize_t bytes = -1;
    // очистить буфер!
    bzero(TCP_Server::buff, sizeof(TCP_Server::buff));
    // получаем сообщение от клиента
    bytes = recv(TCP_Server::connection, TCP_Server::buff, sizeof(TCP_Server::buff), 0);
    if(bytes < 0) {
        return "Error receiving data from client!";
    } else if(bytes >= 0) {
        mess_from_client_.clear();
        mess_from_client_.append(TCP_Server::buff);
        return mess_from_client_;
    }
}

template <typename T> bool Messages<T>::send_message(T& answ_message) {
    ssize_t bytes = -1;
    bytes = send(TCP_Server::connection, answ_message.c_str(), strlen(answ_message.c_str()), 0);
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0) {
        return true;
    } else {
        std::cout << "Data sending to the client failed!" << std::endl;
        return false;
    }
}

template class Messages<std::string>;