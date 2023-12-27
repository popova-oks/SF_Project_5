#include "../headers/Messages.h"
#include "../headers/ConnectionTCP.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

template <typename T> int Messages<T>::send_message(const T& message) {
    // передача сообщения через сокет
    ssize_t bytes =
        send(TCP_Client::socket_file_descriptor, message.c_str(), strlen(message.c_str()), 0);
    // если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes == -1) {
        std::cout << "Data sending to the server failed!" << std::endl;
    }
    return bytes;
}

template <typename T> T& Messages<T>::recive_message() {
    // очищаем буфер обмена клиента
    bzero(TCP_Client::buff, sizeof(TCP_Client::buff));

    // Ждем ответа от сервера
    ssize_t bytes =
        recv(TCP_Client::socket_file_descriptor, TCP_Client::buff, sizeof(TCP_Client::buff), 0);
    mess_from_server_.clear();
    mess_from_server_.append(TCP_Client::buff);
    // очищаем буфер обмена клиента
    bzero(TCP_Client::buff, sizeof(TCP_Client::buff));
    return mess_from_server_;
}

template class Messages<std::string>;