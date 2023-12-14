#include "../headers/Messages.h"
#include "../headers/ConnectionTCP.h"
#include <fstream>
#include <iostream>
#include <cstring>

/*
template <typename T> Messages<T>::Messages() : pathJSON_{"./data.json"} {
    // Проверить, существует ли файл по указанному пути
    std::ifstream input_file(pathJSON_);
    if(!input_file.good()) {
        // Файл не существует, создать новый
        std::ofstream output_file(pathJSON_);
    }
}
*/

/*
template <typename T> void Messages<T>::set_message(IObserver* sender, const T& message) {
    msg_.insert({sender, message});
}
*/

/*
template <typename T>
nlohmann::json Messages<T>::create_message(const std::string& sender, const std::string& receiver,
                                           const T message) {
    nlohmann::json json;
    json["sender"] = sender;
    json["receiver"] = receiver;
    json["message"] = message;
    return json;
}
*/

/*
template <typename T>
void Messages<T>::save_message(const std::string& sender, const std::string& receiver,
                               const T& message) {
    nlohmann::json json;
    json["sender"] = sender;
    json["receiver"] = receiver;
    json["message"] = message;

    nlohmann::json messagesArray;
    if(is_checkingFile(pathJSON_)) {
        messagesArray = readFile(pathJSON_);
    }
    else {
        // Если файл был пустой или его не существовало, создаем новый массив JSON
        messagesArray = nlohmann::json::array();
    }
    messagesArray.push_back(json);
    writeFile(pathJSON_, messagesArray);
}
*/

/*
template <typename T> void Messages<T>::save_message(const nlohmann::json& json) {
    nlohmann::json messagesArray;
    if(is_checkingFile(pathJSON_)) {
        messagesArray = readFile(pathJSON_);
    } else {
        // Если файл был пустой или его не существовало, создаем новый массив JSON
        messagesArray = nlohmann::json::array();
    }
    messagesArray.push_back(json);
    writeFile(pathJSON_, messagesArray);
}
*/

/*
template <typename T> void Messages<T>::send_message(const nlohmann::json& json) {
    // преобразование JSON в строку
    std::string json_str_message = json.dump();
    // преобразуем строку в байты
    const char* message = json_str_message.c_str();
    // открываем сокет клиента, создаем соединение с сервером
    TCP_Client::processMessage();
    // передача сообщения через сокет
    ssize_t bytes = send(TCP_Client::socket_file_descriptor, message, strlen(message), 0);
    // ssize_t bytes = write(TCP_Client::socket_file_descriptor, TCP_Client::message,
    //                        sizeof(TCP_Client::message));

    // если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0) {
        std::cout << "\nData send to the server successfully!" << std::endl;
        // очищаем буфер обмена клиента
        bzero(TCP_Client::buff, sizeof(TCP_Client::buff));
        // Ждем ответа от сервера
        // read(TCP_Client::socket_file_descriptor, TCP_Client::buff, sizeof(TCP_Client::buff));
        recv(TCP_Client::socket_file_descriptor, TCP_Client::buff, sizeof(TCP_Client::buff), 0);
        std::cout << "Data received from server: " << TCP_Client::buff << std::endl;
    } else {
        std::cout << "Data sending to the server failed!" << std::endl;
    }
    // очищаем буфер обмена клиента
    bzero(TCP_Client::buff, sizeof(TCP_Client::buff));
    //закрываем сокет, завершаем соединение
    close(TCP_Client::socket_file_descriptor);
}
*/

template <typename T> T Messages<T>::get_messages() {
    // accept() - это функция соксета, которая ожидает и принимает входящее соединение от
    // клиента. Функция блокируется (ожидает), пока клиент не попытается подключиться, и когда
    // клиентское подключение обнаружено, она создает новый соксет для общения с этим клиентом.
    ssize_t bytes = -1;
    TCP_Server::connection = accept(TCP_Server::socket_file_descriptor,
                                    (struct sockaddr*)&TCP_Server::client, &TCP_Server::length);
    if(TCP_Server::connection == -1) {
        std::cout << "Server is unable to accept the data from client!" << std::endl;
    } else {
        // очистить буфер!
        bzero( TCP_Server::buff, sizeof(TCP_Server::buff));        
        // получаем сообщение от клиента
        bytes = recv(TCP_Server::connection, TCP_Server::buff, sizeof(TCP_Server::buff), 0);        
    }
    if(bytes < 0) {
        return "Error receiving data from client!";
    } else if(bytes >= 0) {
        mess_from_client_.clear();
        mess_from_client_.append(TCP_Server::buff);
        return mess_from_client_;
    }
}

/*
template <typename T> void Messages<T>::update_JSON(const char* message) {
    // обрабатываем данные из буфера обмена
    if(message != nullptr) {
        nlohmann::json remote_json = nlohmann::json::parse(message);
        if(!remote_json.is_null()) {
            save_message(remote_json);
        }
    }
}
*/

template class Messages<std::string>;